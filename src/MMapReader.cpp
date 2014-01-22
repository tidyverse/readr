#include <fastread.h>

using namespace Rcpp ;

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>   // for open()
#include <unistd.h>  // for close()

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace fastread{

    MMapReader::MMapReader( const std::string& filename, char sep_, char quote_, char esc_ ) : 
        file_descriptor( open(filename.c_str(), O_RDONLY) ), 
        sep(sep_), quote(quote_), esc(esc_), 
        ncol(0), inputs()
    {
        struct stat file_info;
        if (fstat(file_descriptor,&file_info) == -1) {
            stop( "cannot read file information" ) ;
        }
        filesize = file_info.st_size ;
        inquote = false ;
        
        memory_start = p = (char *)mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
        eof = p + filesize ;
    }
    
    MMapReader::~MMapReader(){
       for( int i=0; i<ncol; i++){
           delete inputs[i] ;    
       }
       munmap(memory_start, filesize);
       close(file_descriptor);
    }
    
    void MMapReader::read(int n_, CharacterVector classes ){
        n = n_ ;
        if( n <= 0 ){ // this includes n == NA
            // TODO: handle header lines, skipping rows
            n = count_lines() ; 
        }
        ncol = classes.size() ;
        for( int i=0; i<ncol; i++){
            String cl = classes[i] ;
            inputs.push_back( make_vector_input(cl, n, *this ) ) ;   
        }
        ncol = inputs.size() ;
        for( int i=0; i<n; i++) for( int j=0; j<ncol; j++){
             inputs[j]->set(i) ;    
        }
    }
    
    List MMapReader::get(){
        // retaining only the inputs of interest
        // TODO: deal with names column
        std::vector<VectorInput*> columns ; columns.reserve(ncol) ;
        int ncolumns = 0 ;   
        VectorInput* row_names = 0 ;
        
        for( int i=0; i<ncol; i++){
            if( inputs[i]->skip() ) continue ;
            if( inputs[i]->is_rownames() ){
                row_names = inputs[i] ; 
                continue ;    
            }
            columns.push_back( inputs[i] ) ; ncolumns++ ;
        }
        
        List out(ncolumns) ;
        // automatic names for now
        // TODO: handle names in header line
        CharacterVector names(ncolumns) ;
        
        for( int i=0; i<ncolumns; i++){
            String V("V") ; V += (i+1) ;
        
            names[i] = V ;
            out[i] = columns[i]->get() ;    
        }
        out.attr( "class" ) = "data.frame" ;
        out.attr( "names" ) = names ;
        if( row_names ){
            out.attr( "row.names" ) = row_names->get() ;   
        } else {
            out.attr( "row.names") = IntegerVector::create( NA_INTEGER, -n) ;
        }
        return out ;
    }
    
    int MMapReader::count_lines() const {
        int count = 0 ;
        char* ptr = memory_start ;
        while( ptr < eof ) if( *ptr++ == '\n' ) count++ ;
        return count ;
    }
    
    CharacterVector MMapReader::read_lines(int n_){
        n = n_ ;
        if( n <= 0 ){ // this includes n == NA
            // TODO: handle header lines, skipping rows
            n = count_lines() ; 
        }
        StringVector out(n) ;
        for( int i=0; i<n; i++){
            char* start = p ;
            int len = move_until_next_line() ;
            out[i] = Rf_mkCharLen(start, len) ;
        }
        return out ;
    }
    
    
    int MMapReader::get_int(){
        int res = get_int_naive() ;
        move_until_next_token_start() ;
        return res ;
    }
    
    double MMapReader::get_double(){
        using boost::spirit::qi::double_;
        using boost::spirit::qi::parse;
        double res = 0.0 ;
        end = p ;
        parse( end, end + move_until_next_token_start(), double_, res ) ;
        return res ;
    }
    
    SEXP MMapReader::get_String(){
        end = p ; // saving the position of first character
        int len = move_until_next_token_start() ;
        return Rf_mkCharLen( end, len ) ;
    }
    
    int MMapReader::move_until_next_line(){
        char next;
        int len = 0 ;
        while( p < eof ){
            next = *(p++) ;
            if( inquote ){
                if( next == esc ){
                    // the next character is an escape character
                    ++p ; len++ ;
                } else if( next == quote ){
                    // ending the quote
                    inquote = false ; 
                } 
            } else {
                if( next == quote ){
                    // entering a quote                                                      
                    inquote = true ;
                } else if( next == '\n' ){
                    // end of line
                    p++ ;
                    break ;
                } else if( next == '\r' && *p == '\n' ){
                    p+=2; break ;    
                }
            }
            len++ ;
        }
        return len ;
    }
    
    int MMapReader::move_until_next_token_start(){
        char next;
        int len = 0 ;
        while( p < eof ){
            next = *(p++) ;
            if( inquote ){
                if( next == esc ){
                    // the next character is an escape character
                    ++p ; len++ ;
                } else if( next == quote ){
                    // ending the quote
                    inquote = false ; 
                } 
            } else {
                if( next == quote ){
                    // entering a quote                                                      
                    inquote = true ;
                } else if( next == sep || next == '\n' ){
                    // end of line
                    break ;
                } else if( next == '\r' && *p == '\n' ){
                    p++; break ;    
                }
            }
            len++ ;
        }
        return len ;
    }
    
    inline bool valid_digit(char c){
        static char before_zero = '0' - 1 ;
        static char after_nine = '9' + 1 ;
        return c > before_zero && c < after_nine ;
    }
    
    int MMapReader::get_int_naive(){
        int sign, value ;
    
        // Skip leading white space, if any.
        while ( *p == ' ' ) {
            ++p ;
        }
    
        // Get sign, if any.
        sign = 1;
        if (*p == '-') {
            sign = -1;
            ++p ;
        } else if (*p == '+') {
            ++p ;
        }
    
        // Get digits before decimal point or exponent, if any.
        for (value = 0; valid_digit(*p); ++p ) {
            value = value * 10 + (*p - '0');
        }
    
        return sign * value ;
    }
    
    
    
}  

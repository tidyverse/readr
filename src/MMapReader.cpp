#include <fastread.h>

using namespace Rcpp ;

namespace fastread{

    MMapReader::MMapReader( const std::string& filename, char sep_, char quote_, char esc_ ) : 
        file_descriptor( open(filename.c_str(), O_RDONLY) ), 
        sep(sep_), quote(quote_), esc(esc_)
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
       munmap(memory_start, filesize);
       close(file_descriptor);
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
        int res = get_int_naive(p) ;
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
            if( next == '\n' ){
                break ;
            } else if( next == '\r' && *p == '\n' ){
                p++; 
                break ;    
            }
            len++ ;
        }
        return len ;
    }
    
    int MMapReader::skip_token(){
        return move_until_next_token_start() ;    
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
    
    
}  

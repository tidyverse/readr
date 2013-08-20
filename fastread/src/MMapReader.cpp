#include "fastread.h"

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
    
    // this was just for benchamrking. will disappear
    void MMapReader::setup(int n_, CharacterVector classes ){
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
    
    Rcpp::String MMapReader::get_String(){
        end = p ; // saving the position of first character
        int len = move_until_next_token_start() ;
        return Rf_mkCharLen( end, len ) ;
    }
    
    int MMapReader::move_until_next_token_start(){
        char next;
        int len = 0 ;
        while( true ){
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
    
    
    // benchmarking reading ints
    IntegerVector MMapReader::parseInt_strtol(int nd){
        IntegerVector out = no_init(nd) ;
        for( int i=0; i<nd; i++){
            out[i] =  strtol( p , &end, 0 ) ;  move_until_next_token_start() ;
        }
        return out ;
    }
    IntegerVector MMapReader::parseInt_naive(int nd){
        IntegerVector out = no_init(nd) ;
        
        for( int i=0; i<nd; i++){
            out[i] = get_int_naive() ; move_until_next_token_start() ;
        }
        
        return out ;
    }
    IntegerVector MMapReader::parseInt_qi(int nd){
        using boost::spirit::qi::int_;
        using boost::spirit::qi::parse;
        
        IntegerVector out = no_init(nd) ;
        for( int i=0; i<nd; i++){
            end = p ;
            parse( end, end + move_until_next_token_start(), int_, out[i] ) ;
        }
        
        return out ;
    }
    
    // --------- 
    // these were used for the benchmarking of the way to read double 
    // release them eventually
    NumericVector MMapReader::parseDouble_strtod(int nd){
        NumericVector out = no_init(nd) ;
        for( int i=0; i<nd; i++){
            out[i] =  strtod( p , &end ) ;  move_until_next_token_start() ;
        }
        return out ;
    }
    
    NumericVector MMapReader::parseDouble_atof(int nd){
        NumericVector out = no_init(nd) ;
        for( int i=0; i<nd; i++){
            out[i] = atof(p) ;  move_until_next_token_start() ;
        }
        return out ;
    }
    
    
    NumericVector MMapReader::parseDouble_qi(int nd){
        using boost::spirit::qi::double_;
        using boost::spirit::qi::parse;
        
        NumericVector out = no_init(nd);
        for( int i=0; i<nd; i++){
            end = p ;
            parse( end, end + move_until_next_token_start(), double_, out[i] ) ;
        }
        
        return out ;
    }
    
    NumericVector MMapReader::parseDouble_fast_atof(int nd){
        NumericVector out = no_init(nd);
        for( int i=0; i<nd; i++){
            out[i] = get_double_fast_atof() ;  move_until_next_token_start() ;
        }
        return out ;
    }
    
    // ------------
    
    #define white_space(c) ((c) == ' ' || (c) == '\t')
    
    #define kBufferSize 100 
    
    inline bool valid_digit(char c){
        static char before_zero = '0' - 1 ;
        static char after_nine = '9' + 1 ;
        return c > before_zero && c < after_nine ;
    }
    
    double MMapReader::get_double_fast_atof(){
        int frac;
        double sign, value, scale;
    
        // Skip leading white space, if any.
    
        while ( *p == ' ' ) {
            ++p ;
        }
    
        // Get sign, if any.
        sign = 1.0;
        if (*p == '-') {
            sign = -1.0;
            ++p ;
        } else if (*p == '+') {
            ++p ;
        }
    
        // Get digits before decimal point or exponent, if any.
        for (value = 0.0; valid_digit(*p); ++p ) {
            value = value * 10.0 + (*p - '0');
        }
    
        // Get digits after decimal point, if any.
        if (*p == '.') {
            double pow10 = 1.0;
            ++p ;
            double decimal = 0.0 ;
            
            while (valid_digit(*p)) {
                decimal = decimal * 10.0 + (*p - '0');
                pow10 *= 10.0;
                ++p;
            }
            value += (decimal / pow10) ;
        }
    
        // Handle exponent, if any.
    
        frac = 0;
        scale = 1.0;
        if ((*p == 'e') || (*p == 'E')) {
            unsigned int expon;
    
            // Get sign of exponent, if any.
    
            ++p ;
            if (*p == '-') {
                frac = 1;
                ++p ;
            } else if (*p == '+') {
                ++p ;
            }
    
            // Get digits of exponent, if any.
    
            for (expon = 0; valid_digit(*p); ++p) {
                expon = expon * 10 + (*p - '0');
            }
            if (expon > 308) expon = 308;
    
            // Calculate scaling factor.
    
            while (expon >= 50) { scale *= 1E50; expon -= 50; }
            while (expon >=  8) { scale *= 1E8;  expon -=  8; }
            while (expon >   0) { scale *= 10.0; expon -=  1; }
        }
    
        // Return signed and scaled floating point result.
    
        return sign * (frac ? (value / scale) : (value * scale));
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

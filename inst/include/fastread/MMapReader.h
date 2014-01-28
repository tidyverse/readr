#ifndef FASTREAD_MMapReader_H
#define FASTREAD_MMapReader_H

namespace fastread {
    
    class MMapReader {
       public:
           
           MMapReader( const std::string& filename, char sep_ = ',', char quote_ = '"', char esc_ = '\\' ) ;
           ~MMapReader() ;
           
           int skip_token() ;
           
           int move_until_next_line() ;
           
           int get_int() ;
           int get_int_naive() ;
           
           double get_double() ;
           SEXP get_String() ;
           
           int count_lines() const ; 
           Rcpp::CharacterVector read_lines(int n) ;
           
       private:
           
           int move_until_next_token_start() ;
           
           int file_descriptor ;
           char sep, quote, esc ;
           
           char* memory_start ;
           char* p ;
           char* end ;
           char* eof ;
           size_t filesize ;
           bool inquote ;
           
           int n ;
           
    } ;
    
}     

#endif

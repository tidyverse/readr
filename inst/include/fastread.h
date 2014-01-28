#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>
using namespace Rcpp; 

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/unordered_map.hpp>

#include <fastread/Connection.h>

#include <fastread/VectorInput.h>

namespace fastread {
    
    class MMapReader {
       public:
           typedef VectorInput<MMapReader> Input ;
           
           MMapReader( const std::string& filename, char sep_ = ',', char quote_ = '"', char esc_ = '\\' ) ;
           ~MMapReader() ;
           
           void read(int n_, Rcpp::CharacterVector classes ) ;
           void setup(int n_, Rcpp::CharacterVector classes ) ;
           
           Rcpp::List get() ;
           
           inline char* get_pointer() const { return p; }
           inline void  set_pointer(char* p_) { p = p_ ; }
           
           int move_until_next_token_start() ;
           int move_until_next_line() ;
           
           int get_int() ;
           int get_int_naive() ;
           
           double get_double() ;
           SEXP get_String() ;
           
           int count_lines() const ; 
           Rcpp::CharacterVector read_lines(int n) ;
           
       private:
           
           int file_descriptor ;
           char sep, quote, esc ;
           
           char* memory_start ;
           char* p ;
           char* end ;
           char* eof ;
           size_t filesize ;
           bool inquote ;
           
           int n, ncol ;
           
           std::vector<Input*> inputs ;
    } ;
    
}     

#endif

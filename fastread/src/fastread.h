#ifndef FASTREAD_FASTREAD_H
#define FASTREAD_FASTREAD_H

#include <Rcpp.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace fastread {
    class FileReader{
       public:
            FileReader( const std::string& filename, char sep_ = ',', char quote_ = '"' , char esc_ = '\\') ;
            ~FileReader() ;
            
            const std::string& get_token() ;
            void skip_token() ;
            
            inline bool is_finished() const { return finished ; }
            inline int line_numer() const { return i_line; }
           
       private:
            inline char get_next(){ return fgetc(file) ; }
            
            FILE* file ;
            std::string token ;
            char sep, quote, esc ;
            
            bool inquote ;
            int i_line ;
            bool finished ;
    } ;
}     

#endif

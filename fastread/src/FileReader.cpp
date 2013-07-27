#include "fastread.h"

using namespace Rcpp ;

namespace fastread{
    
    FileReader::FileReader( const std::string& filename, char sep_, char quote_, char esc_ ) 
        : sep(sep_), quote(quote_), esc(esc_), inquote(false), i_line(0), finished(false)
    {
        file = fopen( filename.c_str(), "r" ) ;
    }
       
    FileReader::~FileReader(){
        fclose(file) ;
    }
     
    const std::string& FileReader::get_token(){
        token.clear() ;
        char next ; 
        while( true ){
            next = get_next() ;
            
            if( inquote ){
                if( next == esc ){
                    // the next character is an escape character
                    token += esc ;
                    token += get_next() ;
                } else if( next == quote ){
                    // ending the quote
                    token += quote ;
                    inquote = false ; 
                } else {
                    token += next ;    
                }
                
            } else {
                if( next == quote ){
                    // entering a quote
                    inquote = true ;
                    token += quote ;
                } else if( next == sep || next == '\n' ){
                    // end of line
                    i_line++ ;
                    break ;
                } else if( next == EOF ){
                    finished = true ;
                    break ;
                } else {
                    token += next ;    
                }
            }
        }
        return token ;
    }
    
    // similar to get_token, but it just skips the token instead ot returning it
    void FileReader::skip_token(){
        char next; 
        while( true ){
            next = get_next() ;
            
            if( inquote ){
                if( next == esc ){
                    // the next character is an escape character
                    get_next() ;
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
                    i_line++ ;
                    break ;
                } else if( next == EOF ){
                    finished = true ;
                    break ;
                } 
            }
        }
    }

}  

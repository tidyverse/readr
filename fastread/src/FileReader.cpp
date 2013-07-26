#include <Rcpp.h>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Rcpp ;

/**
 * attempt at a simple file tokenizer
 */

class FileReader {
    public:
        FileReader( const std::string& filename, char sep_ = ',', char quote_ = '"', char esc_ = '\\' ) 
            : sep(sep_), quote(quote_), esc(esc_), inquote(false), i_line(0), finished(false)
        {
            file = fopen( filename.c_str(), "r" ) ;
        }
       
        ~FileReader(){
            fclose(file) ;
        }
       
        const std::string& get_token(){
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
        
        inline bool is_finished() const { return finished ; }
        
   private:
       
       char get_next(){
            return fgetc(file) ;    
        }
        
       FILE* file ;
       std::string token ;
       char sep, quote, esc ;
       
       bool inquote ;
       int i_line ;
       bool finished ;
} ;

// [[Rcpp::export]]
CharacterVector scan_( std::string filename, int n ){
    CharacterVector out(n) ;
    FileReader reader(filename) ;
    for( int i=0; i<n; i++){
        if( reader.is_finished() ) break ;
        out[i] = reader.get_token() ;
    }
    return out ;
}


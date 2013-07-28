#include "fastread.h"

using namespace Rcpp ;

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>   // for open()
#include <unistd.h>  // for close()

namespace fastread{

    MMapReader::MMapReader( const std::string& filename, char sep_, char quote_, char esc_ ) : 
        file_descriptor( open(filename.c_str(), O_RDONLY) ), 
        sep(sep_), quote(quote_), esc(esc_), 
        inputs()
    {
        struct stat file_info;
        if (fstat(file_descriptor,&file_info) == -1) {
            stop( "cannot read file information" ) ;
        }
        filesize = file_info.st_size ;
        inquote = false ;
        
        memory_start = p = (char *)mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
    }
    
    void MMapReader::read(int n, CharacterVector classes ){
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
        List out(ncol) ;
        for( int i=0; i<ncol; i++){
            out[i] = inputs[i]->get() ;    
        }
        return out ;
    }
    
    MMapReader::~MMapReader(){
       for( int i=0; i<ncol; i++){
           delete inputs[i] ;    
       }
       munmap(memory_start, filesize);
       close(file_descriptor);
    }
    
    void MMapReader::move_until_next_token_start(){
        char next;
        while( true ){
            next = *(p++) ; 
            if( inquote ){
                if( next == esc ){
                    // the next character is an escape character
                    ++p ;
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
                }
            }
        }    
    }
    
}  

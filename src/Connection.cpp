#include <fastread.h>

namespace fastread {

    CharacterVector ReadConnection::read_lines(int n){
        if(n<=0){
            return read_all_lines() ;    
        }
        CharacterVector out(n) ;
        for( int i=0; i<n; i++){
            int n = readline() ;
            out[i] = Rf_mkCharLen(data, n) ;
        }
        return out ;
    }
        
    CharacterVector ReadConnection::read_all_lines(){
        std::vector<SEXP> tmp ;
        for( int i=0; ; i++){
            int n = readline() ;
            if( n < 0 ) break ;
            
            tmp.push_back( Rf_mkCharLen(data, n ) ) ;
        }
        int n = tmp.size() ;
        CharacterVector out(n);
        std::copy(tmp.begin(), tmp.end(), out.begin());
        return out ;
    }
    
    int ReadConnection::get_int(){
        int res = get_int_naive(p) ;
        move_until_next_token_start() ;
        return res ;
    }
    
    double ReadConnection::get_double(){
        using boost::spirit::qi::double_;
        using boost::spirit::qi::parse;
        double res = 0.0 ;
        char* q = p ;
        parse( q, q + move_until_next_token_start(), double_, res ) ;
        return res ;
    }
    
    SEXP ReadConnection::get_String(){
        char* q = p ; // saving the position of first character
        int len = move_until_next_token_start() ;
        
        SEXP res = Rf_mkCharLen( q, len ) ;
        return res ;
    }
    
    void ReadConnection::ensure_full_line(){
        char* q = p ;
        if(p==data_end){
            int read = con->read( data, 1, chunk_size, con) ;
            p = data ; 
            data_end = p + read ;
        } else {
            while( q < data_end && *q != '\n' ) ++q ;
            int pos = q-p ;
            
            // move the rest of the data to the beginning of the buffer 
            // and read some more from the connection
            if( q == data_end ){
                std::memmove( data, p, q-p ) ;
                con->read( data + pos, 1, chunk_size - pos, con) ;
                p = data ;
            }
            
        }
    }
    
    int ReadConnection::skip_token(){
        return move_until_next_token_start() ;    
    }
    
    int ReadConnection::move_until_next_token_start(){
        char next;
        int len = 0 ;
        while(true){
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



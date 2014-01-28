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
    
}



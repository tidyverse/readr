#ifndef FASTREAD_CharacterVectorSource_H
#define FASTREAD_CharacterVectorSource_H

namespace fastread {
        
    class CharacterVectorSource : public Source<CharacterVectorSource>{
    public:
        typedef Source<CharacterVectorSource> Base ;
        
        CharacterVectorSource( CharacterVector data_, char sep = ',', char quote = '"', char esc = '\\' ) :
            Base(sep,quote,esc), data(data_), n(data.size()), i(0)
        {
            more() ;
        }
        
        inline bool more(){
            char* s = const_cast<char*>( CHAR(data[i])) ;
            Base::set(s, s + strlen(s)) ;
            return i < n;
        }
        
        // no-op as we always have the full data mmapped
        inline bool ensure_full_line(){
            return i < n ;
        }
        
    private: 
        CharacterVector data ;
        int n ;
        int i ;
         
    } ;
}

#endif

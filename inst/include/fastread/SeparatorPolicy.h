#ifndef FASTREAD_SeparatorPolicy_H
#define FASTREAD_SeparatorPolicy_H

namespace fastread {
    
    class SingleCharacterSeparator {
    public:
        SingleCharacterSeparator( char sep_ = ',' ) : sep(sep_){}
        
        inline bool is_sep(char c){
            return c == sep ;
        }
        
    private:
        char sep ;
    };
    
    class WhiteSpaceSeparator {
    public:
        inline bool is_sep(char c){
            return c == ' ' || c == '\t' ;    
        }
    } ;
}

#endif

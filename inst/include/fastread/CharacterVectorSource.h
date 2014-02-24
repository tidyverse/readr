#ifndef FASTREAD_CharacterVectorSource_H
#define FASTREAD_CharacterVectorSource_H

namespace fastread {
        
    template <
        typename LinePolicy = KeepAllLines,
        typename SeparatorPolicy = SingleCharacterSeparator
    >
    class CharacterVectorSource : public Source< CharacterVectorSource<LinePolicy,SeparatorPolicy>, LinePolicy, SeparatorPolicy>{
    public:
        typedef Source< CharacterVectorSource<LinePolicy, SeparatorPolicy>, LinePolicy, SeparatorPolicy> Base ;
        
        CharacterVectorSource( CharacterVector data_, LinePolicy line_policy_ = LinePolicy(), SeparatorPolicy sep_policy_ = SeparatorPolicy() ) :
            Base(line_policy_, sep_policy_), data(data_), n(data.size()), i(0)
        {
            more() ;
        }
        
        inline bool more(){
            char* s = const_cast<char*>( CHAR(data[i])) ;
            Base::set(s, s + strlen(s)) ;
            return i < n;
        }
        
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

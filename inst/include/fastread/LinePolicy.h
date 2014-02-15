#ifndef FASTREAD_LinePolicy_H
#define FASTREAD_LinePolicy_H

namespace fastread {
    
    template <typename Source>
    class KeepAllLines{
    public:
        bool keep_line(Source& ){
            return true ;    
        }
    };
    
    template <typename Source>
    class FilterRecylerLines {
    public:
        FilterRecylerLines( LogicalVector pattern_ ) : 
            pattern(pattern_), i(0), n(pattern.size()){}
        
        bool keep_line(Source& ){
            bool res = pattern[i++] ;
            if( i == n) i = 0 ;
            return res ;
        }
        
    private:
        LogicalVector pattern ;
        int i ;
        int n ;
    };
    
}

#endif

#ifndef FASTREAD_LinePolicy_H
#define FASTREAD_LinePolicy_H

namespace fastread {

class KeepAllLines{
public:
  inline bool keep_line(char* p){
    return true ;
  }

  inline void reset(){}
};

class FilterRecylerLines {
public:
  FilterRecylerLines( Rcpp::LogicalVector pattern_ ) :
  pattern(pattern_), i(0), n(pattern.size()){}

  bool keep_line(char* p){
    bool res = pattern[i++] ;
    if( i == n) i = 0 ;
    return res ;
  }

  inline void reset(){ i = 0 ; }

private:
  Rcpp::LogicalVector pattern ;
  int i ;
  int n ;
};

}

#endif

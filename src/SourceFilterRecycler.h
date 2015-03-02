#ifndef FASTREAD_SourceFilterRecycler_H
#define FASTREAD_SourceFilterRecycler_H

namespace fastread {

template <typename Source>
class SourceFilterRecycler {
public:

  SourceFilterRecycler(Source& source_, LogicalVector pattern_) :
  source(source_), pattern(pattern_){}

private:
  Source& source ;
  LogicalVector pattern ;

} ;
}

#endif

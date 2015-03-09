#ifndef FASTREAD_COLLECTORSKIP_H_
#define FASTREAD_COLLECTORSKIP_H_

#include <cstring>
#include <Rcpp.h>
#include "Collector.h"

class CollectorSkip : public Collector {
public:
  CollectorSkip() : Collector(R_NilValue) {
  }

  void setValue(int i, const Token& t) {
  }

  static bool canParse(std::string x) {
    return TRUE;
  }

};

#endif

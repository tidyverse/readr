#ifndef FASTREAD_COLLECTORSKIP_H_
#define FASTREAD_COLLECTORSKIP_H_

#include <Rcpp.h>
#include <cstring>
#include "Collector.h"

class CollectorSkip : public Collector {
public:
  CollectorSkip() : Collector(R_NilValue) {
  }

  void setValue(int i, const Token& t) {
  }

  virtual bool skip() {
    return true;
  }
};

#endif

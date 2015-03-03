#ifndef FASTREAD_HCOLLECTOR_H
#define FASTREAD_HCOLLECTOR_H

#include "HToken.h"
#include <Rcpp.h>

class Collector {

public:
  virtual void setValue(int i, const Token& t) =0;
  virtual void resize(int n) =0;
  virtual SEXP vector() =0;
};

#endif

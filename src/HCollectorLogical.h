#ifndef FASTREAD_COLLECTORLOGICAL_H
#define FASTREAD_COLLECTORLOGICAL_H

#include "HCollector.h"
#include <cstring>
#include <Rcpp.h>

class CollectorLogical : public Collector {
  Rcpp::LogicalVector column_;

public:
  CollectorLogical(): column_(0) {
  }

  void resize(int n) {
    column_ = Rf_lengthgets(column_, n);
  }

  void setValue(int i, const Token& t) {
    column_[i] = parse(t);
  }

  int parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_POINTER: {
      int size = t.end() - t.begin();
      return (size == 1 && *t.begin() == 'T') ||
        (size == 4 && strncmp(t.begin(), "TRUE", 4));
    };
    case TOKEN_INLINE:
      return t.text() == "T" || t.text() == "TRUE";
      break;
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_LOGICAL;
      break;
    case TOKEN_EOL:
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return false;
  }

  SEXP vector() {
    return column_;
  }

};

#endif

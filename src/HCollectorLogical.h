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
    case TOKEN_STRING: {
      std::string buffer;
      StreamIterators string = t.getString(&buffer);
      int size = string.second - string.first;
      return (size == 1 && *string.first == 'T') ||
        (size == 4 && strncmp(string.first, "TRUE", 4));
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_LOGICAL;
      break;
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

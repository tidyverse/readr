#ifndef FASTREAD_COLLECTORCHARACTER_H
#define FASTREAD_COLLECTORCHARACTER_H

#include "HCollector.h"
#include <Rcpp.h>

class CollectorCharacter : public Collector {
  Rcpp::CharacterVector column_;
  cetype_t encoding_;

public:

  CollectorCharacter(): column_(0), encoding_(CE_NATIVE) {
  }

  void resize(int n) {
    column_ = Rf_lengthgets(column_, n);
  }

  void setValue(int i, const Token& t) {
    column_[i] = parse(t);
  }

  SEXP parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_POINTER:
      return Rf_mkCharLenCE(t.begin(), t.end() - t.begin(), encoding_);
    case TOKEN_INLINE:
      return Rf_mkCharCE(t.text().c_str(), encoding_);
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_STRING;
    case TOKEN_EOL:
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
    return NA_STRING;
  }

  SEXP vector() {
    return column_;
  }

};

#endif

#ifndef FASTREAD_COLLECTORCHARACTER_H
#define FASTREAD_COLLECTORCHARACTER_H

#include "Collector.h"
#include <Rcpp.h>

class CollectorCharacter : public Collector {
  cetype_t encoding_;

public:
  CollectorCharacter(): Collector(CharacterVector()), encoding_(CE_NATIVE) {
  }

  void setValue(int i, const Token& t) {
    SET_STRING_ELT(column_, i, parse(t));
  }

  SEXP parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      StreamIterators string = t.getString(&buffer);
      return Rf_mkCharLenCE(string.first, string.second - string.first, encoding_);
    };
    case TOKEN_MISSING:
      return NA_STRING;
    case TOKEN_EMPTY:
      return Rf_mkChar("");
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
    return NA_STRING;
  }
};

#endif

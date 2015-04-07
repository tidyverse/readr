#ifndef FASTREAD_COLLECTORCHARACTER_H_
#define FASTREAD_COLLECTORCHARACTER_H_

#include <Rcpp.h>
#include "Collector.h"

class CollectorCharacter : public Collector {
  cetype_t encoding_;

public:
  CollectorCharacter(): Collector(Rcpp::CharacterVector()), encoding_(CE_NATIVE) {
  }

  void setValue(int i, const Token& t) {
    Rcpp::RObject charsxp;
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);
      charsxp = Rf_mkCharLenCE(string.first, string.second - string.first, encoding_);
      break;
    };
    case TOKEN_MISSING:
      charsxp = NA_STRING;
      break;
    case TOKEN_EMPTY:
      charsxp = Rf_mkChar("");
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    SET_STRING_ELT(column_, i, charsxp);
  }

};

#endif

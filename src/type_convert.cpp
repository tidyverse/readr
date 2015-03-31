#include <Rcpp.h>
using namespace Rcpp;

#include "Collector.h"
#include "Token.h"

// [[Rcpp::export]]
RObject type_convert_col(CharacterVector x, List spec, int col) {
  CollectorPtr collector = Collector::create(spec);
  collector->resize(x.size());

  for (int i = 0; i < x.size(); ++i) {
    SEXP string = x[i];
    Token t;

    if (string == NA_STRING) {
      t = Token(TOKEN_MISSING, i - 1, col - 1);
    } else {
      const char* begin = CHAR(string);
      t = Token(begin, begin + Rf_length(string), i - 1, col - 1);
    }

    collector->setValue(i, t);
  }

  return collector->vector();
}

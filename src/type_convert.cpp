#include <Rcpp.h>
using namespace Rcpp;

#include "Collector.h"
#include "LocaleInfo.h"
#include "Token.h"

// [[Rcpp::export]]
RObject type_convert_col(CharacterVector x, List spec, List locale_, int col,
                         const std::vector<std::string>& na, bool trim_ws) {
  LocaleInfo locale(locale_);

  CollectorPtr collector = Collector::create(spec, locale);
  collector->resize(x.size());

  for (int i = 0; i < x.size(); ++i) {
    SEXP string = x[i];
    Token t;

    if (string == NA_STRING) {
      t = Token(TOKEN_MISSING, i - 1, col - 1);
    } else {
      const char* begin = CHAR(string);
      t = Token(begin, begin + Rf_length(string), i - 1, col - 1);
      if (trim_ws)
        t.trim();
      t.flagNA(na);
    }

    collector->setValue(i, t);
  }

  return collector->vector();
}

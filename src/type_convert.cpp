#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include "cpp11/strings.hpp"

#include "Collector.h"
#include "LocaleInfo.h"
#include "Token.h"

[[cpp11::register]] cpp11::sexp type_convert_col(
    const cpp11::strings& x,
    const cpp11::list& spec,
    const cpp11::list& locale_,
    int col,
    const std::vector<std::string>& na,
    bool trim_ws) {
  LocaleInfo locale(locale_);

  CollectorPtr collector = Collector::create(spec, &locale);
  collector->resize(x.size());

  for (int i = 0; i < x.size(); ++i) {
    SEXP string = x[i];
    Token t;

    if (string == NA_STRING) {
      t = Token(TOKEN_MISSING, i - 1, col - 1);
    } else {
      const char* begin = CHAR(string);
      t = Token(begin, begin + Rf_length(string), i - 1, col - 1, false);
      if (trim_ws) {
        t.trim();
      }
      t.flagNA(na);
    }

    collector->setValue(i, t);
  }

  return static_cast<SEXP>(collector->vector());
}

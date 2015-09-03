#include <Rcpp.h>
#include "DateTimeLocale.h"

using namespace Rcpp;

CharacterVector utf8Vector(const std::vector<std::string>& x) {
  CharacterVector out(x.size());
  for (size_t i = 0; i < x.size(); ++i)
    out[i] = Rf_mkCharCE(x[i].c_str(), CE_UTF8);

  return out;
}

// [[Rcpp::export]]
List date_time_locale() {
  DateTimeLocale current;
  return List::create(
    _["month"] = utf8Vector(current.month()),
    _["month_abbrev"] = utf8Vector(current.monthAbbrev()),
    _["day"] = utf8Vector(current.day()),
    _["day_abbrev"] = utf8Vector(current.dayAbbrev()),
    _["period"] = utf8Vector(current.period())
  );
}

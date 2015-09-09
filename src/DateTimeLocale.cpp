#include <Rcpp.h>
#include "DateTimeLocale.h"
#include <locale.h>

using namespace Rcpp;

CharacterVector utf8Vector(const std::vector<std::string>& x) {
  CharacterVector out(x.size());
  for (size_t i = 0; i < x.size(); ++i)
    out[i] = Rf_mkCharCE(x[i].c_str(), CE_UTF8);

  return out;
}

// [[Rcpp::export]]
List date_time_locale(std::string locale = "C") {
  char* old = setlocale(LC_TIME, locale.c_str());
  if (old == NULL)
    stop("Failed to set locale to %s", locale);

  DateTimeLocale loc;
  List out = List::create(
    _["month"] = utf8Vector(loc.month()),
    _["month_abbrev"] = utf8Vector(loc.monthAbbrev()),
    _["day"] = utf8Vector(loc.day()),
    _["day_abbrev"] = utf8Vector(loc.dayAbbrev()),
    _["period"] = utf8Vector(loc.period())
  );

  setlocale(LC_TIME, old);

  return out;
}

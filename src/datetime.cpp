#include <Rcpp.h>
using namespace Rcpp;

#include "DateTime.h"

// [[Rcpp::export]]
NumericVector utctime(IntegerVector year, IntegerVector month, IntegerVector day,
  IntegerVector hour, IntegerVector min, IntegerVector sec,
  NumericVector psec, bool repair = false) {
  int n = year.size();
  if (month.size() != n || day.size() != n || hour.size() != n ||
    min.size() != n || sec.size() != n || psec.size() != n) {
    Rcpp::stop("All inputs must be same length");
  }

  NumericVector out = NumericVector(n);
  TzManager tzMan;

  for (int i = 0; i < n; ++i) {
    DateTime dt(year[i], month[i] - 1, day[i] - 1, hour[i], min[i],
      sec[i], psec[i], "UTC");
    if (repair)
      dt.repair();
    out[i] = dt.time(&tzMan);
  }

  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";

  return out;
}

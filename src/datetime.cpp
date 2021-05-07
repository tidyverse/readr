#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/protect.hpp"

#include "DateTime.h"

[[cpp11::register]] cpp11::writable::doubles utctime_(
    const cpp11::integers& year,
    const cpp11::integers& month,
    const cpp11::integers& day,
    const cpp11::integers& hour,
    const cpp11::integers& min,
    const cpp11::integers& sec,
    const cpp11::doubles& psec) {
  int n = year.size();
  if (month.size() != n || day.size() != n || hour.size() != n ||
      min.size() != n || sec.size() != n || psec.size() != n) {
    cpp11::stop("All inputs must be same length");
  }

  cpp11::writable::doubles out(n);

  for (int i = 0; i < n; ++i) {
    DateTime dt(
        year[i], month[i], day[i], hour[i], min[i], sec[i], psec[i], "UTC");
    out[i] = dt.datetime();
  }

  out.attr("class") = {"POSIXct", "POSIXt"};
  out.attr("tzone") = "UTC";

  return out;
}

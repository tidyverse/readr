#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/protect.hpp"

#include "DateTime.h"

[[cpp11::register]] cpp11::writable::doubles utctime_(
    cpp11::integers year,
    cpp11::integers month,
    cpp11::integers day,
    cpp11::integers hour,
    cpp11::integers min,
    cpp11::integers sec,
    cpp11::doubles psec) {
  int n = year.size();
  if (month.size() != n || day.size() != n || hour.size() != n ||
      min.size() != n || sec.size() != n || psec.size() != n) {
    cpp11::stop("All inputs must be same length");
  }

  cpp11::writable::doubles out(n);

  for (int i = 0; i < n; ++i) {
    DateTime dt(
        year[i],
        month[i] - 1,
        day[i] - 1,
        hour[i],
        min[i],
        sec[i],
        psec[i],
        "UTC");
    out[i] = dt.datetime();
  }

  out.attr("class") = {"POSIXct", "POSIXt"};
  out.attr("tzone") = "UTC";

  return out;
}

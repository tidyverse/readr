// Adapted from mktime00 in src/main/datetime.c
// Author: The R Core Team.
// License: GPL >= 2

#include <Rcpp.h>
using namespace Rcpp;
#include <ctime>

static const int first_day_of_month[12] =
  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

// Leap days occur in a 400 year cycle: this records the cumulative number
// of leap days in per cycle. Generated with:
// is_leap <- function(y) (y %% 4) == 0 & ((y %% 100) != 0 | (y %% 400) == 0)
// cumsum(is_leap(0:399))
static const int leap_days[400] =
  {0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7,
   7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12,
   12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17,
   17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22,
   22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25,
   26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30,
   30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35,
   35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40,
   40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 44,
   45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49,
   49, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53,
   53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 58,
   58, 58, 58, 59, 59, 59, 59, 60, 60, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62,
   63, 63, 63, 63, 64, 64, 64, 64, 65, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67,
   67, 68, 68, 68, 68, 69, 69, 69, 69, 70, 70, 70, 70, 71, 71, 71, 71, 72, 72,
   72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76,
   76, 76, 76, 77, 77, 77, 77, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 80, 80,
   81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 84, 84, 84, 84, 85, 85, 85,
   85, 86, 86, 86, 86, 87, 87, 87, 87, 88, 88, 88, 88, 89, 89, 89, 89, 90, 90,
   90, 90, 91, 91, 91, 91, 92, 92, 92, 92, 93, 93, 93, 93, 94, 94, 94, 94, 95,
   95, 95, 95, 96, 96, 96, 96, 97, 97, 97};

static const int cycle_days = 400 * 365 + 97;

inline int is_leap(unsigned y) {
  return (y % 4) == 0 && ((y % 100) != 0 || (y % 400) == 0);
}

class DateTime {
  int year_, mon_, day_, hour_, min_, sec_;
  double psec_;

public:
  DateTime(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0,
    double psec = 0):
  year_(year), mon_(mon), day_(day), hour_(hour), min_(min), sec_(sec),
  psec_(psec) {
  }

  // Convert a tm struct into number of seconds since 1970-01-01T0000Z.
  // Compared to usual implementations this returns a double, and supports
  // a wider range of dates. Input is not validated; invalid dates have
  // undefined behaviour.
  double utctime() {
    // Number of days since start of year
    int day = first_day_of_month[mon_] + day_;
    if (mon_ > 1 && is_leap(year_))
      day++;

    // Number of days since 0000-01-01
    // Leap years come in 400 year cycles so determine which cycle we're
    // in, and what position we're in within that cycle.
    int ly_cycle = year_ / 400;
    int ly_offset = year_ - (ly_cycle * 400);
    if (ly_offset < 0) {
      ly_offset += 400;
      ly_cycle--;
    }
    day += ly_cycle * cycle_days + ly_offset * 365 + leap_days[ly_offset];

    // Convert to number of days since 1970-01-01
    day -= 719528;

    return psec_ + sec_ + (min_ * 60) + (hour_ * 3600) + (day * 86400.0);
  }
};

// [[Rcpp::export]]
NumericVector utctime(IntegerVector year, IntegerVector month, IntegerVector day,
                      IntegerVector hour, IntegerVector min, IntegerVector sec,
                      NumericVector psec) {
  int n = year.size();
  if (month.size() != n || day.size() != n || hour.size() != n ||
      min.size() != n || sec.size() != n || psec.size() != n) {
    Rcpp::stop("All inputs must be same length");
  }

  NumericVector out = NumericVector(n);

  for (int i = 0; i < n; ++i) {
    out[i] = DateTime(year[i], month[i] - 1, day[i] - 1, hour[i], min[i],
      sec[i], psec[i]).utctime();
  }

  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";

  return out;
}

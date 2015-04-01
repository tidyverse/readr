// Adapted from mktime00 in src/main/datetime.c
// Author: The R Core Team.
// License: GPL >= 2

#include <Rcpp.h>
using namespace Rcpp;
#include <ctime>

static const int first_day_of_month[12] =
  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

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
    // Count number of days since start of year
    int day = first_day_of_month[mon_] + day_;
    if (mon_ > 1 && is_leap(year_))
      day++;

    // Add number of days between start of year and 1970-01-01. Before 0 and
    // after 3000, only estimate the number of days in a year, assuming an
    // average of 365 + 1/4 - 1/100 + 1/400 days per year. This is an
    // approximation, but resonable given that the Gregorian calendar wasn't
    // defined until in 1582 (the last European country to adopt it was Greece,
    // in 1923), and has an error of ~1 day / 3300 years.
    double excess = 0;
    if (year_ < 0 || year_ > 3000) {
      excess = (year_ / 2000) - 1;
    }
    int year0 = year_ - (excess * 2000);

    if (year0 > 1970) {
      for (int year = 1970; year < year0; year++)
        day += 365 + is_leap(year);
    } else if (year0 < 1970) {
      for (int year = 1969; year >= year0; year--)
        day -= (365 + is_leap(year));
    }
    day += excess * 730485; // 2000 * (365 + 1/4 - 1/100 + 1/400);

    return psec_ + sec_ + (min_ * 60) + (hour_ * 3600) + (day * 86400.0);
  }
};

// [[Rcpp::export]]
NumericVector utctime(int year, int month, int day, int hour = 0, int min = 0,
  int sec = 0, double psec = 0) {

  double dt = DateTime(year, month - 1, day - 1, hour, min, sec, psec).utctime();

  NumericVector out = NumericVector::create(dt + psec);
  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";

  return out;
}

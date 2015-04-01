// Adapted from mktime00 in src/main/datetime.c
// Author: The R Core Team.
// License: GPL >= 2

#include <Rcpp.h>
using namespace Rcpp;
#include <ctime>

static const int days_in_month[12] =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)
#define days_in_year(year) (isleap(year) ? 366 : 365)

// Convert a tm struct into number of seconds since 1970-01-01T0000Z.
// Compared to usual implementations this returns a double, and supports
// a wider range of dates. Input is not validated; invalid dates have
// undefined behaviour.
double utctime(struct tm* tm) {
  int day = tm->tm_mday - 1;
  int year0 = 1900 + tm->tm_year;

  // Before 0 and after 3000, only estimate the number of days in a year,
  // assuming an average of 365 + 1/4 - 1/100 + 1/400 days per year. This is
  // an approximation, but resonable given that the Gregorian calendar wasn't
  // defined until in 1582 (the last European country to adopt it was Greece,
  // in 1923), and has an error of ~1 day / 3300 years.
  double excess = 0;
  if (year0 < 0 || year0 > 3000) {
    excess = (int) (year0 / 2000) - 1;
  }
  year0 -= (int) (excess * 2000);
  excess *= 730485; // 2000 * (365 + 1/4 - 1/100 + 1/400);

  for(int i = 0; i < tm->tm_mon; i++)
    day += days_in_month[i];
  if (tm->tm_mon > 1 && isleap(year0))
    day++;

  if (year0 > 1970) {
    for (int year = 1970; year < year0; year++)
      day += days_in_year(year);
  } else if (year0 < 1970) {
    for (int year = 1969; year >= year0; year--)
      day -= days_in_year(year);
  }

  return
    tm->tm_sec +
    (tm->tm_min * 60) +
    (tm->tm_hour * 3600) +
    (day + excess) * 86400.0;
}

// [[Rcpp::export]]
NumericVector utctime(int year, int month, int day, int hour = 0, int min = 0,
                      int sec = 0, double psec = 0) {
  struct tm tm;
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  tm.tm_hour = hour;
  tm.tm_min = min;
  tm.tm_sec = sec;

  NumericVector out = NumericVector::create(utctime(&tm) + psec);
  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";

  return out;
}



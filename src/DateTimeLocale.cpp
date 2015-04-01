#include <Rcpp.h>
using namespace Rcpp;
#include <ctime>

std::string formatDate(struct tm& tm, const char* format) {
  char buff[100];

  size_t res = strftime(buff, 100, format, &tm);
  if (res == 0)
    Rcpp::stop("Failed to format date");

  return std::string(buff);
}

class LocaleStrings {
  std::vector<std::string> month_, monthAbbrev_, day_, dayAbbrev_, period_;

public:

  LocaleStrings() {
    month_.reserve(12);
    monthAbbrev_.reserve(12);
    day_.reserve(7);
    dayAbbrev_.reserve(7);
    period_.reserve(2);

    struct tm tm;
    tm.tm_sec = 0;
    tm.tm_min = 0;
    tm.tm_hour = 0;
    tm.tm_mday = 0;
    tm.tm_mon = 0;
    tm.tm_isdst = 0;
    tm.tm_year = 30;

    for(int i = 0; i < 12; i++) {
      tm.tm_mon = i;

      month_.push_back(formatDate(tm, "%B"));
      monthAbbrev_.push_back(formatDate(tm, "%b"));
    }
    tm.tm_mon = 0;

    for(int i = 0; i < 7; i++) {
      tm.tm_mday = tm.tm_yday = i+1; /* 2000-01-02 was a Sunday */
      tm.tm_wday = i;

      day_.push_back(formatDate(tm, "%A"));
      dayAbbrev_.push_back(formatDate(tm, "%a"));
    }

    tm.tm_hour = 1;
    period_.push_back(formatDate(tm, "%p"));

    tm.tm_hour = 13;
    period_.push_back(formatDate(tm, "%p"));
  }

  const std::vector<std::string>& month() {
    return month_;
  }
  const std::vector<std::string>& monthAbbrev() {
    return monthAbbrev_;
  }
  const std::vector<std::string>& day() {
    return day_;
  }
  const std::vector<std::string>& dayAbbrev() {
    return dayAbbrev_;
  }
  const std::vector<std::string>& period() {
    return period_;
  }

};

// [[Rcpp::export]]
List localeStrings() {
  LocaleStrings current;
  return List::create(
    _["month"] = wrap(current.month()),
    _["month_abbrev"] = wrap(current.monthAbbrev()),
    _["day"] = wrap(current.day()),
    _["day_abbrev"] = wrap(current.dayAbbrev()),
    _["period"] = wrap(current.period())
  );
}

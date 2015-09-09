#ifndef READR_DATE_TIME_LOCALE_H_
#define READR_DATE_TIME_LOCALE_H_

#include <ctime>
#include "Iconv.h"
#include <boost/noncopyable.hpp>

class DateTimeLocale : boost::noncopyable {
  std::vector<std::string> month_, monthAbbrev_, day_, dayAbbrev_, period_;
  Iconv encoder_;
  char buff_[100];

public:

  DateTimeLocale(): encoder_("UTF-8") {

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
      tm.tm_mday = tm.tm_yday = i + 1; /* 2000-01-02 was a Sunday */
      tm.tm_wday = i;

      day_.push_back(formatDate(tm, "%A"));
      dayAbbrev_.push_back(formatDate(tm, "%a"));
    }

    tm.tm_hour = 1;
    period_.push_back(formatDate(tm, "%p"));

    tm.tm_hour = 13;
    period_.push_back(formatDate(tm, "%p"));
  }

  const std::vector<std::string>& month() const {
    return month_;
  }
  const std::vector<std::string>& monthAbbrev() const {
    return monthAbbrev_;
  }
  const std::vector<std::string>& day() const {
    return day_;
  }
  const std::vector<std::string>& dayAbbrev() const {
    return dayAbbrev_;
  }
  const std::vector<std::string>& period() const {
    return period_;
  }

private:
  inline std::string formatDate(struct tm& tm, const char* format) {
    size_t res = strftime(buff_, 100, format, &tm);
    return std::string((res == 0) ? "" : buff_);
  }

};

#endif

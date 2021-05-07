#include "cpp11/as.hpp"
#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"
#include <string>
#include <vector>

#include "LocaleInfo.h"

LocaleInfo::LocaleInfo(const cpp11::list& x)
    : encoding_(cpp11::as_cpp<std::string>(x["encoding"])),
      encoder_(Iconv(encoding_)) {
  std::string klass = cpp11::as_cpp<std::string>(x.attr("class"));
  if (klass != "locale") {
    cpp11::stop("Invalid input: must be of class locale");
  }

  cpp11::list date_names(x["date_names"]);
  mon_ = cpp11::as_cpp<std::vector<std::string>>(date_names["mon"]);
  monAb_ = cpp11::as_cpp<std::vector<std::string>>(date_names["mon_ab"]);
  day_ = cpp11::as_cpp<std::vector<std::string>>(date_names["day"]);
  dayAb_ = cpp11::as_cpp<std::vector<std::string>>(date_names["day_ab"]);
  amPm_ = cpp11::as_cpp<std::vector<std::string>>(date_names["am_pm"]);

  decimalMark_ = cpp11::as_cpp<char>(x["decimal_mark"]);
  groupingMark_ = cpp11::as_cpp<char>(x["grouping_mark"]);

  dateFormat_ = cpp11::as_cpp<std::string>(x["date_format"]);
  timeFormat_ = cpp11::as_cpp<std::string>(x["time_format"]);

  tz_ = cpp11::as_cpp<std::string>(x["tz"]);
}

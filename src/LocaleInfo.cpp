#include <Rcpp.h>

#include "LocaleInfo.h"

using namespace Rcpp;

LocaleInfo::LocaleInfo(List x)
    : encoding_(as<std::string>(x["encoding"])), encoder_(Iconv(encoding_)) {
  std::string klass = x.attr("class");
  if (klass != "locale")
    stop("Invalid input: must be of class locale");

  List date_names = as<List>(x["date_names"]);
  mon_ = as<std::vector<std::string> >(date_names["mon"]);
  monAb_ = as<std::vector<std::string> >(date_names["mon_ab"]);
  day_ = as<std::vector<std::string> >(date_names["day"]);
  dayAb_ = as<std::vector<std::string> >(date_names["day_ab"]);
  amPm_ = as<std::vector<std::string> >(date_names["am_pm"]);

  decimalMark_ = as<char>(x["decimal_mark"]);
  groupingMark_ = as<char>(x["grouping_mark"]);

  dateFormat_ = as<std::string>(x["date_format"]);
  timeFormat_ = as<std::string>(x["time_format"]);

  tz_ = as<std::string>(x["tz"]);
}

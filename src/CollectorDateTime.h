#ifndef FASTREAD_COLLECTORDATETIME_H_
#define FASTREAD_COLLECTORDATETIME_H_

#include <Rcpp.h>
#include "Collector.h"
#include "DateTime.h"
#include "DateTimeParser.h"
#include "DateTimeLocale.h"

std::string formatStandard(const std::string& format) {
  std::string out;
  out.resize(100);

  // Standard time used by go: http://golang.org/pkg/time/
  struct tm tm;
  tm.tm_year = 2006 - 1900;
  tm.tm_mon = 1 - 1;
  tm.tm_mday = 2;
  tm.tm_hour = 15;
  tm.tm_min = 4;
  tm.tm_sec = 5;

  size_t len = strftime(&out[0], 100, format.c_str(), &tm);
  if (len == 0)
    return "???";

  out.resize(len);
  return out;
}


class CollectorDateTime : public Collector {
  std::string format_, tz_;
  DateTimeLocale locale_;
  DateTimeParser parser_;
  TzManager tzMan_;

public:
  CollectorDateTime(const std::string& format, const std::string& tz):
      Collector(Rcpp::NumericVector()),
      format_(format),
      tz_(tz),
      parser_(locale_, tz),
      tzMan_(tz)
  {
  }

  void setValue(int i, const Token& t) {
    REAL(column_)[i] = parse(t);
  }

  double parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);
      std::string std_string(string.first, string.second);

      parser_.setDate(std_string.c_str());
      bool res = (format_ == "") ? parser_.parse() : parser_.parse(format_);

      if (!res) {
        warn(t.row(), t.col(), "date like " +  format_, std_string);
        return NA_REAL;
      }

      DateTime dt = parser_.makeDateTime();
      if (!dt.isValid()) {
        warn(t.row(), t.col(), "valid date", std_string);
        return NA_REAL;
      }
      return dt.time(&tzMan_);
    }
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_REAL;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return 0;
  }

  Rcpp::RObject vector() {
    column_.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
    column_.attr("tzone") = tz_;
    return column_;
  };

  static bool canParse(const std::string& x) {
    DateTimeLocale loc;
    DateTimeParser parser(loc, "UTC");

    parser.setDate(x.c_str());
    return parser.parse(false);
  }

};

#endif

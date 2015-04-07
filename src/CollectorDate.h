#ifndef FASTREAD_COLLECTORDATE_H_
#define FASTREAD_COLLECTORDATE_H_

#include <Rcpp.h>
#include "Collector.h"
#include "DateTime.h"
#include "DateTimeParser.h"

class CollectorDate : public Collector {
  std::string format_;
  DateTimeParser parser_;
  DateTimeLocale locale_;

public:
  CollectorDate(const std::string& format):
      Collector(Rcpp::IntegerVector()),
      format_(format),
      parser_(locale_, "UTC")
  {
  }

  void setValue(int i, const Token& t) {
    INTEGER(column_)[i] = parse(t);
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

      DateTime dt = parser_.makeDate();
      if (!dt.isValid()) {
        warn(t.row(), t.col(), "valid date", std_string);
        return NA_REAL;
      }
      return dt.date();
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
    column_.attr("class") = "Date";
    return column_;
  };

  static bool canParse(const std::string& x) {
    DateTimeLocale loc;
    DateTimeParser parser(loc, "UTC");

    parser.setDate(x.c_str());
    return parser.parse("%Y-%m-%d");
  }

};

#endif

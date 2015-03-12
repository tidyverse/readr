#ifndef FASTREAD_COLLECTORDATETIME_H_
#define FASTREAD_COLLECTORDATETIME_H_

#include <Rcpp.h>
#include <ctime>
#include <time.h>
#include "Collector.h"

time_t timegm(struct tm *tm);

std::string formatStandard(std::string format) {
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
  std::string format_;

public:
  CollectorDateTime(std::string format):
    Collector(Rcpp::NumericVector()),
    format_(format)
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

      struct tm tm;
      memset(&tm, 0, sizeof(tm));

      char* res = strptime(std_string.c_str(), format_.c_str(), &tm);

      if (res == NULL || res != &std_string[std_string.size()]) {
        Rcpp::warning("At [%i, %i]: expected date like '%s', got '%s'",
          t.row() + 1, t.col() + 1, formatStandard(format_), std_string);
        return NA_REAL;
      }

      return timegm(&tm);
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
    column_.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
    column_.attr("tzone") = "UTC";
    return column_;
  };


  static bool canParse(std::string x) {
    // Because it needs non-static info
    return false;
  }

};

#endif

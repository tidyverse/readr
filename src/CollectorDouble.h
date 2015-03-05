#ifndef FASTREAD_COLLECTORDOUBLE_H_
#define FASTREAD_COLLECTORDOUBLE_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;

#include "Collector.h"

class CollectorDouble : public Collector {

public:
  CollectorDouble(): Collector(Rcpp::NumericVector()) {
  }

  void setValue(int i, const Token& t) {
    REAL(column_)[i] = parse(t);
  }

  double parse(const Token& t) {
    double res = 0.0;

    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      bool ok = qi::parse(string.first, string.second, qi::double_, res);
      if (!ok || string.first != string.second) {
        Collector::warn(t);
        res = NA_REAL;
      }

      break;
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      res = NA_REAL;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return res;
  }

  static bool canParse(std::string x) {
    const char* start = x.c_str();
    char* end;

    errno = 0;
    strtod(start, &end);
    // parsed to end of string and no errors
    return (end == start + x.size()) && (errno == 0);
  }

};

#endif

#ifndef FASTREAD_COLLECTORDOUBLE_H_
#define FASTREAD_COLLECTORDOUBLE_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;

#include "Collector.h"

class CollectorDouble : public Collector {
  boost::container::string buffer_;

public:
  CollectorDouble(): Collector(Rcpp::NumericVector()) {
  }

  virtual void resize(int n) {
    Collector::resize(n);
  }

  void setValue(int i, const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      SourceIterators str = t.getString(&buffer_);

      bool ok = qi::parse(str.first, str.second, qi::double_, REAL(column_)[i]);
      if (!ok) {
        REAL(column_)[i] = NA_REAL;
        warn(t.row(), t.col(), "a double", str);
        return;
      }

      if (str.first != str.second) {
        REAL(column_)[i] = NA_REAL;
        warn(t.row(), t.col(), "no trailing characters", str);
        return;
      }

      return;
    }
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      REAL(column_)[i] = NA_REAL;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
  }
  static bool canParse(const std::string& x) {
    double res = 0;
    std::string::const_iterator begin = x.begin(), end = x.end();
    return qi::parse(begin, end, qi::double_, res) && begin == end;
  }
};

#endif

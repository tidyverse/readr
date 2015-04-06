#ifndef FASTREAD_COLLECTORINTEGER_H_
#define FASTREAD_COLLECTORINTEGER_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;

#include "Collector.h"

class CollectorInteger : public Collector {

public:
  boost::container::string buffer_;

  CollectorInteger(): Collector(Rcpp::IntegerVector()) {
  }

  virtual void resize(int n) {
    Collector::resize(n);
  }

  void setValue(int i, const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      SourceIterators str = t.getString(&buffer_);

      bool ok = qi::parse(str.first, str.second, qi::int_, INTEGER(column_)[i]);
      if (!ok) {
        INTEGER(column_)[i] = NA_INTEGER;
        warn(t.row(), t.col(), "an integer", str);
        return;
      }

      if (str.first != str.second)
        warn(t.row(), t.col(), "no trailing characters", str);

      return;
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      INTEGER(column_)[i] = NA_INTEGER;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
  }

  static bool canParse(const std::string& x) {
    int res = 0;
    std::string::const_iterator begin = x.begin(), end = x.end();
    return qi::parse(begin, end, qi::int_, res) && begin == end;
  }
};

#endif

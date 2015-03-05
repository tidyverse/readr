#ifndef FASTREAD_COLLECTORINTEGER_H_
#define FASTREAD_COLLECTORINTEGER_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include "Collector.h"

class CollectorInteger : public Collector {
public:

  CollectorInteger(): Collector(IntegerVector()) {
  }

  void setValue(int i, const Token& t) {
    INTEGER(column_)[i] = parse(t);
  }

  int parse(const Token& t) {
    int res = 0;

    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      StreamIterators string = t.getString(&buffer);
      boost::spirit::qi::parse(string.first, string.second,
        boost::spirit::qi::int_, res);
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

};

#endif

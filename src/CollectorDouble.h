#ifndef FASTREAD_COLLECTORDOUBLE_H_
#define FASTREAD_COLLECTORDOUBLE_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

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
      boost::spirit::qi::parse(string.first, string.second,
        boost::spirit::qi::double_, res);
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

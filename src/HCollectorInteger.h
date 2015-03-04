#ifndef FASTREAD_COLLECTORINTEGER_H
#define FASTREAD_COLLECTORINTEGER_H

#include "HCollector.h"
#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

class CollectorInteger : public Collector {
  Rcpp::IntegerVector column_;

public:

  CollectorInteger(): column_(0) {
  }

  void resize(int n) {
    column_ = Rf_lengthgets(column_, n);
  }

  void setValue(int i, const Token& t) {
    column_[i] = parse(t);
  }

  int parse(const Token& t) {
    int res = 0;

    switch(t.type()) {
    case TOKEN_POINTER:
      boost::spirit::qi::parse(t.begin(), t.end(),
        boost::spirit::qi::int_, res);
      break;
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      res = NA_REAL;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return res;
  }

  SEXP vector() {
    return column_;
  }

};

#endif

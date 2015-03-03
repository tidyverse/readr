#ifndef FASTREAD_HCOLLECTOR_H
#define FASTREAD_HCOLLECTOR_H

#include "HToken.h"
#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

class Collector {

public:
  virtual void setValue(int i, const Token& t) =0;
  virtual void resize(int n) =0;
  virtual SEXP vector() =0;
};

class CharacterCollector : Collector {
  Rcpp::CharacterVector column_;
  cetype_t encoding_;

public:

  CharacterCollector(): column_(0), encoding_(CE_NATIVE) {
  }

  void resize(int n) {
    Rf_lengthgets(column_, n);
  }

  void setValue(int i, const Token& t) {
    column_[i] = parse(t);
  }

  SEXP parse(const Token& t) {
    switch(t.type()) {
      case TOKEN_POINTER:
        return Rf_mkCharLenCE(t.begin(), t.end() - t.begin(), encoding_);
      case TOKEN_INLINE:
        return Rf_mkCharCE(t.text().c_str(), encoding_);
      case TOKEN_MISSING:
      case TOKEN_EMPTY:
        return NA_STRING;
      case TOKEN_EOL:
      case TOKEN_EOF:
        Rcpp::stop("Invalid token");
    }
    return NA_STRING;
  }

  SEXP vector() {
    return column_;
  }

};

class DoubleCollector : Collector {
  Rcpp::NumericVector column_;

public:

  DoubleCollector(): column_(0) {
  }

  void resize(int n) {
    column_ = Rf_lengthgets(column_, n);
  }

  void setValue(int i, const Token& t) {
    column_[i] = parse(t);
  }

  double parse(const Token& t) {
    double res = 0.0;

    switch(t.type()) {
    case TOKEN_POINTER:
      boost::spirit::qi::parse(t.begin(), t.end(),
        boost::spirit::qi::double_, res);
      break;
    case TOKEN_INLINE:
      boost::spirit::qi::parse(t.text().begin(), t.text().end(),
        boost::spirit::qi::double_, res);
      break;
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      res = NA_REAL;
      break;
    case TOKEN_EOL:
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

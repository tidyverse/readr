#ifndef FASTREAD_COLLECTORDOUBLE_H_
#define FASTREAD_COLLECTORDOUBLE_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;

#include "Collector.h"

class CollectorDouble : public Collector {
  double* data_;

public:
  CollectorDouble(): Collector(Rcpp::NumericVector()) {
  }

  virtual void resize(int n) {
    Collector::resize(n);
    data_ = REAL(column_);
  }

  void setValue(int i, const Token& t) {
    data_[i] = parse(t);
  }

  double parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      std::pair<bool,double> parsed =
        CollectorDouble::parse(string.first, string.second);

      if (!parsed.first)
        Collector::warn(t, string);
      return parsed.second;
    }
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_REAL;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return 0;
  }

  static bool canParse(std::string x) {
    return CollectorDouble::parse(x.begin(), x.end()).first;
  }

private:

  template <class Iter>
  static std::pair<bool,double> parse(Iter begin, Iter end) {
    double res = 0;

    bool ok = qi::parse(begin, end, qi::double_, res) && begin == end;
    return std::make_pair(ok, ok ? res : NA_REAL);
  }

};

#endif

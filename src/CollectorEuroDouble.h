#ifndef FASTREAD_COLLECTOREURODOUBLE_H_
#define FASTREAD_COLLECTOREURODOUBLE_H_

#include <Rcpp.h>

#include "DoubleEuroPolicy.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;
#include "Collector.h"
#include "CollectorDouble.h"

class CollectorEuroDouble : public Collector {

public:
  CollectorEuroDouble(): Collector(Rcpp::NumericVector()) {
  }

  void setValue(int i, const Token& t) {
    REAL(column_)[i] = parse(t);
  }

  double parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      std::pair<bool,double> parsed = parse(string.first, string.second);

      if (!parsed.first)
        warn(t.row(), t.col(), "a double", string);
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

  static bool canParse(const std::string& x) {
    return parse(x.begin(), x.end()).first;
  }

private:

  template <class Iter>
  static std::pair<bool,double> parse(Iter begin, Iter end) {
    double res = 0;

    bool ok = qi::parse(begin, end, qi::real_parser<double, DoubleEuroPolicy>(), res) && begin == end;
    return std::make_pair(ok, ok ? res : NA_REAL);
  }

};

#endif

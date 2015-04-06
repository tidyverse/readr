#ifndef FASTREAD_COLLECTORINTEGER_H_
#define FASTREAD_COLLECTORINTEGER_H_

#include <Rcpp.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;

#include "Collector.h"

class CollectorInteger : public Collector {
  int* data_;

public:

  CollectorInteger(): Collector(IntegerVector()) {
  }

  virtual void resize(int n) {
    Collector::resize(n);
    data_ = INTEGER(column_);
  }

  void setValue(int i, const Token& t) {
    data_[i] = parse(t);
  }

  int parse(const Token& t) {
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      std::pair<bool,double> parsed = parse(string.first, string.second);
      if (!parsed.first)
        warn(t.row(), t.col(), "an integer", string);

      return parsed.second;
    };
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      return NA_INTEGER;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }

    return 0;
  }

  static bool canParse(const std::string& x) {
    return CollectorInteger::parse(x.begin(), x.end()).first;
  }

private:

  template <class Iter>
  static std::pair<bool,double> parse(Iter begin, Iter end) {
    int res = 0;

    bool ok = qi::parse(begin, end, qi::int_, res) && begin == end;
    return std::make_pair(ok, ok ? res : NA_INTEGER);
  }
};

#endif

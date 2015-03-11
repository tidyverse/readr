#ifndef FASTREAD_COLLECTORNUMERIC_H_
#define FASTREAD_COLLECTORNUMERIC_H_

#include <Rcpp.h>
#include "Collector.h"
#include "CollectorDouble.h"

class CollectorNumeric : public Collector {

public:
  CollectorNumeric(): Collector(Rcpp::NumericVector())
  {
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
      if (!parsed.first) {
        Rcpp::warning("At [%i, %i]: expected a numeric, got '%s'",
          t.row() + 1, t.col() + 1, std::string(string.first, string.second));
      }
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

private:

  template <class Iter>
  static std::pair<bool,double> parse(Iter begin, Iter end) {
    std::string clean;
    for (Iter cur = begin; cur != end; ++cur) {
      if (*cur == '-' || *cur == '.' || (*cur >= '0' && *cur <= '9'))
        clean.push_back(*cur);
    }

    return CollectorDouble::parse(clean.begin(), clean.end());
  }

};

#endif

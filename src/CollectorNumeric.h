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
    switch(t.type()) {
    case TOKEN_STRING: {
      boost::container::string buffer;
      SourceIterators string = t.getString(&buffer);

      if (!parse(string.first, string.second, &REAL(column_)[i])) {
        warn(t.row(), t.col(), "a number", string);
        REAL(column_)[i] = NA_REAL;
      }
      break;
    }
    case TOKEN_MISSING:
    case TOKEN_EMPTY:
      REAL(column_)[i] = NA_REAL;
      break;
    case TOKEN_EOF:
      Rcpp::stop("Invalid token");
    }
  }

private:

  template <class Iter>
  static bool parse(Iter begin, Iter end, double* pEnd) {
    std::string clean;
    for (Iter cur = begin; cur != end; ++cur) {
      if (*cur == '-' || *cur == '.' || (*cur >= '0' && *cur <= '9'))
        clean.push_back(*cur);
    }

    std::string::const_iterator cbegin = clean.begin(), cend = clean.end();
    return qi::parse(cbegin, cend, qi::double_, *pEnd) && cbegin == cend;
  }

};

#endif

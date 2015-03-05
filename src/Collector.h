#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "Token.h"

class Collector {
protected:
  Rcpp::RObject column_;
  int n_;

public:
  Collector(SEXP column): column_(column), n_(0) {}
  virtual ~Collector() {};

  virtual void setValue(int i, const Token& t) =0;

  virtual void resize(int n) {
    n_ = n;
    column_ = Rf_lengthgets(column_, n);
  }
  virtual Rcpp::RObject vector() {
    return column_;
  };

  int size() {
    return n_;
  }

  static void warn(Token t) {
    boost::container::string buffer;
    SourceIterators string = t.getString(&buffer);

    Rcpp::warning("At [%i, %i]: expected a double, got '%s'",
      t.row() + 1, t.col() + 1, std::string(string.first, string.second));
  }

};

// Create an collector from an R list specification
boost::shared_ptr<Collector> collectorCreate(Rcpp::List spec);

#endif

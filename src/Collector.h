#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include "Token.h"
#include <Rcpp.h>
#include <boost/shared_ptr.hpp>

class Collector {
protected:
  Rcpp::RObject column_;

public:
  Collector(SEXP column): column_(column) {}
  virtual ~Collector() {};

  virtual void setValue(int i, const Token& t) =0;

  virtual void resize(int n) {
    column_ = Rf_lengthgets(column_, n);
  }
  virtual Rcpp::RObject vector() {
    return column_;
  };

};

// Create an collector from an R list specification
boost::shared_ptr<Collector> collectorCreate(Rcpp::List spec);

#endif

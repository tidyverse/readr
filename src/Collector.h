#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "Token.h"

class Collector;
typedef boost::shared_ptr<Collector> CollectorPtr;

class Collector {
protected:
  Rcpp::RObject column_;
  int n_;

public:
  Collector(SEXP column): column_(column), n_(0) {}
  virtual ~Collector() {};

  virtual void setValue(int i, const Token& t) =0;

  virtual void resize(int n) {
    if (n == n_)
      return;

    n_ = n;
    column_ = Rf_lengthgets(column_, n);
  }
  virtual Rcpp::RObject vector() {
    return column_;
  };

  virtual bool skip() {
    return false;
  }

  int size() {
    return n_;
  }

  static CollectorPtr create(Rcpp::List spec);

};

std::vector<CollectorPtr> collectorsCreate(Rcpp::ListOf<Rcpp::List> specs);
void collectorsResize(std::vector<CollectorPtr>& collectors, int n);
std::string collectorGuess(Rcpp::CharacterVector input);

#endif

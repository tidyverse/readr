#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "Token.h"
#include "Warnings.h"

class Collector;
typedef boost::shared_ptr<Collector> CollectorPtr;

class Collector {
protected:
  Rcpp::RObject column_;
  Warnings* pWarnings_;

  int n_;

public:
  Collector(SEXP column, Warnings* pWarnings = NULL):
      column_(column), pWarnings_(pWarnings), n_(0)
  {
  }

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

  void setWarnings(Warnings* pWarnings) {
    pWarnings_ = pWarnings;
  }

  inline void warn(int row, int col, std::string expected, std::string actual) {
    if (pWarnings_ == NULL) {
      Rcpp::warning(
        "[%i, %i]: expected %s, but got '%s'",
        row + 1, col + 1, expected, actual);
      return;
    }

    pWarnings_->addWarning(row, col, expected, actual);
  }
  inline void warn(int row, int col, std::string expected,
                   SourceIterators actual) {
    warn(row, col, expected, std::string(actual.first, actual.second));
  }

  static CollectorPtr create(Rcpp::List spec);

};

std::vector<CollectorPtr> collectorsCreate(Rcpp::ListOf<Rcpp::List> specs, Warnings* pWarning);
void collectorsResize(std::vector<CollectorPtr>& collectors, int n);
std::string collectorGuess(Rcpp::CharacterVector input);

#endif

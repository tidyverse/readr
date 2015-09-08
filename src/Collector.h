#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "Token.h"
#include "Warnings.h"
#include "DateTime.h"
#include "DateTimeParser.h"

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

  virtual Rcpp::RObject vector() {
    return column_;
  };

  virtual bool skip() {
    return false;
  }

  int size() {
    return n_;
  }

  void resize(int n) {
    if (n == n_)
      return;

    n_ = n;
    column_ = Rf_lengthgets(column_, n);
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

// Character -------------------------------------------------------------------

class CollectorCharacter : public Collector {
  cetype_t encoding_;

public:
  CollectorCharacter(): Collector(Rcpp::CharacterVector()), encoding_(CE_NATIVE) {}
  void setValue(int i, const Token& t);
};

// Date ------------------------------------------------------------------------

class CollectorDate : public Collector {
  std::string format_;
  DateTimeParser parser_;
  DateTimeLocale locale_;

public:
  CollectorDate(const std::string& format):
    Collector(Rcpp::IntegerVector()),
    format_(format),
    parser_(locale_, "UTC")
  {
  }

  void setValue(int i, const Token& t);

  Rcpp::RObject vector() {
    column_.attr("class") = "Date";
    return column_;
  };

};

// Date time -------------------------------------------------------------------

class CollectorDateTime : public Collector {
  std::string format_, tz_;
  DateTimeLocale locale_;
  DateTimeParser parser_;
  TzManager tzMan_;

public:
  CollectorDateTime(const std::string& format, const std::string& tz):
    Collector(Rcpp::NumericVector()),
    format_(format),
    tz_(tz),
    parser_(locale_, tz),
    tzMan_(tz)
  {
  }

  void setValue(int i, const Token& t);

  Rcpp::RObject vector() {
    column_.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
    column_.attr("tzone") = tz_;
    return column_;
  };

};

class CollectorDouble : public Collector {

public:
  CollectorDouble(): Collector(Rcpp::NumericVector()) {}
  void setValue(int i, const Token& t);
};

class CollectorEuroDouble : public Collector {

public:
  CollectorEuroDouble(): Collector(Rcpp::NumericVector()) {}
  void setValue(int i, const Token& t);
};

class CollectorFactor : public Collector {
  Rcpp::CharacterVector levels_;
  std::map<std::string,int> levelset_;
  bool ordered_;
  boost::container::string buffer_;

public:
  CollectorFactor(Rcpp::CharacterVector levels, bool ordered):
      Collector(Rcpp::IntegerVector()), levels_(levels), ordered_(ordered)
  {
    int n = levels.size();

    for (int i = 0; i < n; ++i) {
      const char* level = Rf_translateCharUTF8(STRING_ELT(levels, i));
      std::string std_level(level);
      levelset_.insert(std::make_pair(std_level, i));
    }
  }
  void setValue(int i, const Token& t);

  Rcpp::RObject vector() {
    if (ordered_) {
      column_.attr("class") = Rcpp::CharacterVector::create("ordered", "factor");
    } else {
      column_.attr("class") = "factor";
    }

    column_.attr("levels") = levels_;
    return column_;
  };
};

class CollectorInteger : public Collector {
public:
  CollectorInteger(): Collector(Rcpp::IntegerVector()) {}
  void setValue(int i, const Token& t);
};

class CollectorLogical : public Collector {
public:
  CollectorLogical(): Collector(Rcpp::LogicalVector()) {}
  void setValue(int i, const Token& t);
};

class CollectorNumeric : public Collector {
public:
  CollectorNumeric(): Collector(Rcpp::NumericVector()) {}
  void setValue(int i, const Token& t);
};

class CollectorSkip : public Collector {
public:
  CollectorSkip() : Collector(R_NilValue) {}
  void setValue(int i, const Token& t) {}
  bool skip() {
    return true;
  }
};


// Helpers ---------------------------------------------------------------------

std::vector<CollectorPtr> collectorsCreate(Rcpp::ListOf<Rcpp::List> specs, Warnings* pWarning);
void collectorsResize(std::vector<CollectorPtr>& collectors, int n);
std::string collectorGuess(Rcpp::CharacterVector input, Rcpp::List locale_);

#endif

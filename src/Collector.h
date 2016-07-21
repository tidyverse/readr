#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_

#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "Iconv.h"
#include "LocaleInfo.h"
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

  static CollectorPtr create(Rcpp::List spec, LocaleInfo* pLocale);

};

// Character -------------------------------------------------------------------

class CollectorCharacter : public Collector {
  Iconv* pEncoder_;

public:
  CollectorCharacter(Iconv* pEncoder):
    Collector(Rcpp::CharacterVector()),
    pEncoder_(pEncoder) {}
  void setValue(int i, const Token& t);
  void setValue(int i, const std::string& s);
};

// Date ------------------------------------------------------------------------

class CollectorDate : public Collector {
  std::string format_;
  DateTimeParser parser_;

public:
  CollectorDate(LocaleInfo* pLocale, const std::string& format):
    Collector(Rcpp::NumericVector()),
    format_(format),
    parser_(pLocale)
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
  std::string format_;
  DateTimeParser parser_;
  std::string tz_;

public:
  CollectorDateTime(LocaleInfo* pLocale, const std::string& format):
    Collector(Rcpp::NumericVector()),
    format_(format),
    parser_(pLocale),
    tz_(pLocale->tz_)
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
  char decimalMark_;
public:
  CollectorDouble(char decimalMark): Collector(Rcpp::NumericVector()),
      decimalMark_(decimalMark) {}
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
  char decimalMark_, groupingMark_;

public:
  CollectorNumeric(char decimalMark, char groupingMark):
    Collector(Rcpp::NumericVector()),
    decimalMark_(decimalMark),
    groupingMark_(groupingMark) {}
  void setValue(int i, const Token& t);
  bool isNum(char c);
};

// Time ---------------------------------------------------------------------


class CollectorTime : public Collector {
  std::string format_;
  DateTimeParser parser_;

public:
  CollectorTime(LocaleInfo* pLocale, const std::string& format):
    Collector(Rcpp::NumericVector()),
    format_(format),
    parser_(pLocale)
  {
  }

  void setValue(int i, const Token& t);

  Rcpp::RObject vector() {
    column_.attr("class") = Rcpp::CharacterVector::create("hms", "difftime");
    column_.attr("units") = "secs";
    return column_;
  };

};

// Skip ---------------------------------------------------------------------

class CollectorSkip : public Collector {
public:
  CollectorSkip() : Collector(R_NilValue) {}
  void setValue(int i, const Token& t) {}
  bool skip() {
    return true;
  }
};

// Raw -------------------------------------------------------------------------
class CollectorRaw : public Collector {
public:
  CollectorRaw() : Collector(Rcpp::List()) {}
  void setValue(int i, const Token& t);
};



// Helpers ---------------------------------------------------------------------

std::vector<CollectorPtr> collectorsCreate(Rcpp::ListOf<Rcpp::List> specs, LocaleInfo* pLocale);
void collectorsResize(std::vector<CollectorPtr>& collectors, int n);
std::string collectorGuess(Rcpp::CharacterVector input, Rcpp::List locale_);

#endif

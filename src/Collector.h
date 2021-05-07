#ifndef FASTREAD_COLLECTOR_H_
#define FASTREAD_COLLECTOR_H_
#include "cpp11/doubles.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/logicals.hpp"
#include "cpp11/strings.hpp"

#include "DateTime.h"
#include "DateTimeParser.h"
#include "Iconv.h"
#include "LocaleInfo.h"
#include "Token.h"
#include "Warnings.h"
#include <map>
#include <memory>

class Collector;
typedef std::shared_ptr<Collector> CollectorPtr;

class Collector {
protected:
  cpp11::sexp column_;
  Warnings* pWarnings_;

  int n_;

public:
  Collector(SEXP column, Warnings* pWarnings = NULL)
      : column_(column), pWarnings_(pWarnings), n_(0) {}

  virtual ~Collector(){};

  virtual void setValue(int i, const Token& t) = 0;
  virtual void setValue(int i, const std::string& s){}; // nocov
  virtual void setValue(int i, size_t st){};            // nocov

  virtual cpp11::sexp vector() { return column_; };

  virtual bool skip() { return false; }

  int size() { return n_; }

  void resize(int n) {
    if (n == n_)
      return;

    if (column_ == R_NilValue)
      return;

#if R_VERSION >= R_Version(3, 4, 0)
    if (n > 0 && n < n_) {
      SET_TRUELENGTH(column_, n_);
      SETLENGTH(column_, n);
      SET_GROWABLE_BIT(column_);
    } else {
      column_ = Rf_lengthgets(column_, n);
    }
#else
    column_ = Rf_lengthgets(column_, n);
#endif

    n_ = n;
  }

  void clear() { resize(0); }

  void setWarnings(Warnings* pWarnings) { pWarnings_ = pWarnings; }

  inline void warn(int row, int col, std::string expected, std::string actual) {
    if (pWarnings_ == NULL) {
      cpp11::warning(
          "[%i, %i]: expected %s, but got '%s'",
          row + 1,
          col + 1,
          expected.c_str(),
          actual.c_str());
      return;
    }

    pWarnings_->addWarning(row, col, expected, actual);
  }
  inline void
  warn(int row, int col, std::string expected, SourceIterators actual) {
    warn(row, col, expected, std::string(actual.first, actual.second));
  }

  static CollectorPtr create(const cpp11::list& spec, LocaleInfo* pLocale);
};

// Character -------------------------------------------------------------------

class CollectorCharacter : public Collector {
  Iconv* pEncoder_;

public:
  CollectorCharacter(Iconv* pEncoder)
      : Collector(cpp11::writable::strings(R_xlen_t(0))), pEncoder_(pEncoder) {}
  void setValue(int i, const Token& t);
  void setValue(int i, const std::string& s);
};

// Date ------------------------------------------------------------------------

class CollectorDate : public Collector {
  std::string format_;
  DateTimeParser parser_;

public:
  CollectorDate(LocaleInfo* pLocale, const std::string& format)
      : Collector(cpp11::writable::doubles(R_xlen_t(0))),
        format_(format),
        parser_(pLocale) {}

  void setValue(int i, const Token& t);

  cpp11::sexp vector() {
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
  CollectorDateTime(LocaleInfo* pLocale, const std::string& format)
      : Collector(cpp11::writable::doubles(R_xlen_t(0))),
        format_(format),
        parser_(pLocale),
        tz_(pLocale->tz_) {}

  void setValue(int i, const Token& t);

  cpp11::sexp vector() {
    column_.attr("class") = {"POSIXct", "POSIXt"};
    column_.attr("tzone") = tz_;
    return column_;
  };
};

class CollectorDouble : public Collector {
  char decimalMark_;

public:
  CollectorDouble(char decimalMark)
      : Collector(cpp11::writable::doubles(R_xlen_t(0))),
        decimalMark_(decimalMark) {}
  void setValue(int i, const Token& t);
  void setValue(int i, size_t st);
};

class CollectorFactor : public Collector {
  Iconv* pEncoder_;
  std::vector<cpp11::r_string> levels_;
  std::map<cpp11::r_string, int> levelset_;
  bool ordered_, implicitLevels_, includeNa_;
  std::string buffer_;

  void insert(int i, const cpp11::r_string& str, const Token& t);

public:
  CollectorFactor(
      Iconv* pEncoder, cpp11::sexp levels, bool ordered, bool includeNa)
      : Collector(cpp11::writable::integers(R_xlen_t(0))),
        pEncoder_(pEncoder),
        ordered_(ordered),
        includeNa_(includeNa) {
    implicitLevels_ = levels == R_NilValue;
    if (!implicitLevels_) {
      cpp11::strings lvls(levels);
      int n = lvls.size();

      for (int i = 0; i < n; ++i) {
        cpp11::r_string std_level;
        if (STRING_ELT(lvls, i) != NA_STRING) {
          const char* level = Rf_translateCharUTF8(STRING_ELT(lvls, i));
          std_level = level;
        } else {
          std_level = NA_STRING;
        }
        levels_.push_back(std_level);
        levelset_.insert(std::make_pair(std_level, i));
      }
    }
  }
  void setValue(int i, const Token& t);

  cpp11::sexp vector() {
    if (ordered_) {
      column_.attr("class") = {"ordered", "factor"};
    } else {
      column_.attr("class") = "factor";
    }

    int n = levels_.size();
    cpp11::writable::strings levels(n);
    for (int i = 0; i < n; ++i) {
      levels[i] = levels_[i];
    }

    column_.attr("levels") = levels;
    return column_;
  };
};

class CollectorInteger : public Collector {
public:
  CollectorInteger() : Collector(cpp11::writable::integers(R_xlen_t(0))) {}
  void setValue(int i, const Token& t);
};

class CollectorLogical : public Collector {
public:
  CollectorLogical() : Collector(cpp11::writable::logicals(R_xlen_t(0))) {}
  void setValue(int i, const Token& t);
};

class CollectorNumeric : public Collector {
  char decimalMark_, groupingMark_;

public:
  CollectorNumeric(char decimalMark, char groupingMark)
      : Collector(cpp11::writable::doubles(R_xlen_t(0))),
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
  CollectorTime(LocaleInfo* pLocale, const std::string& format)
      : Collector(cpp11::writable::doubles(R_xlen_t(0))),
        format_(format),
        parser_(pLocale) {}

  void setValue(int i, const Token& t);

  cpp11::sexp vector() {
    column_.attr("class") = {"hms", "difftime"};
    column_.attr("units") = "secs";
    return column_;
  };
};

// Skip ---------------------------------------------------------------------

class CollectorSkip : public Collector {
public:
  CollectorSkip() : Collector(R_NilValue) {}
  void setValue(int i, const Token& t) {}
  bool skip() { return true; }
};

// Raw -------------------------------------------------------------------------
class CollectorRaw : public Collector {
public:
  CollectorRaw() : Collector(cpp11::writable::list(static_cast<R_xlen_t>(0))) {}
  void setValue(int i, const Token& t);
};

// Helpers ---------------------------------------------------------------------

std::vector<CollectorPtr>
collectorsCreate(const cpp11::list& specs, LocaleInfo* pLocale);
void collectorsResize(std::vector<CollectorPtr>& collectors, int n);
void collectorsClear(std::vector<CollectorPtr>& collectors);
std::string collectorGuess(
    const cpp11::strings& input,
    const cpp11::list& locale_,
    bool guessInteger = false);

#endif

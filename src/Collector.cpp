#include "cpp11/list.hpp"

#include "Collector.h"
#include "LocaleInfo.h"
#include "QiParsers.h"
#include "utils.h"

CollectorPtr Collector::create(const cpp11::list& spec, LocaleInfo* pLocale) {
  std::string subclass(cpp11::as_cpp<cpp11::strings>(spec.attr("class"))[0]);

  if (subclass == "collector_skip") {
    return CollectorPtr(new CollectorSkip());
  }
  if (subclass == "collector_logical") {
    return CollectorPtr(new CollectorLogical());
  }
  if (subclass == "collector_integer") {
    return CollectorPtr(new CollectorInteger());
  }
  if (subclass == "collector_double") {
    return CollectorPtr(new CollectorDouble(pLocale->decimalMark_));
  }
  if (subclass == "collector_number") {
    return CollectorPtr(
        new CollectorNumeric(pLocale->decimalMark_, pLocale->groupingMark_));
  }
  if (subclass == "collector_character") {
    return CollectorPtr(new CollectorCharacter(&pLocale->encoder_));
  }
  if (subclass == "collector_date") {
    SEXP format_ = spec["format"];
    std::string format = (Rf_isNull(format_)) != 0U
                             ? pLocale->dateFormat_
                             : cpp11::as_cpp<std::string>(format_);
    return CollectorPtr(new CollectorDate(pLocale, format));
  }
  if (subclass == "collector_datetime") {
    std::string format = cpp11::as_cpp<std::string>(spec["format"]);
    return CollectorPtr(new CollectorDateTime(pLocale, format));
  }
  if (subclass == "collector_time") {
    std::string format = cpp11::as_cpp<std::string>(spec["format"]);
    return CollectorPtr(new CollectorTime(pLocale, format));
  }
  if (subclass == "collector_factor") {
    cpp11::sexp levels(spec["levels"]);
    bool ordered = cpp11::as_cpp<bool>(spec["ordered"]);
    bool includeNa = cpp11::as_cpp<bool>(spec["include_na"]);
    return CollectorPtr(
        new CollectorFactor(&pLocale->encoder_, levels, ordered, includeNa));
  }

  cpp11::stop("Unsupported column type");
  return CollectorPtr(new CollectorSkip());
}

std::vector<CollectorPtr>
collectorsCreate(const cpp11::list& specs, LocaleInfo* pLocale) {
  std::vector<CollectorPtr> collectors;
  for (auto spec : specs) {
    CollectorPtr col(Collector::create(SEXP(spec), pLocale));
    collectors.push_back(col);
  }

  return collectors;
}

// Implementations ------------------------------------------------------------

void CollectorCharacter::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);

    if (t.hasNull()) {
      warn(t.row(), t.col(), "", "embedded null");
    }

    SET_STRING_ELT(
        column_,
        i,
        pEncoder_->makeSEXP(string.first, string.second, t.hasNull()));
    break;
  };
  case TOKEN_MISSING:
    SET_STRING_ELT(column_, i, NA_STRING);
    break;
  case TOKEN_EMPTY:
    SET_STRING_ELT(column_, i, Rf_mkCharCE("", CE_UTF8));
    break;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorCharacter::setValue(int i, const std::string& s) {
  SET_STRING_ELT(column_, i, Rf_mkCharCE(s.c_str(), CE_UTF8));
}

void CollectorDate::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);
    std::string std_string(string.first, string.second);

    parser_.setDate(std_string.c_str());
    bool res =
        (format_.empty()) ? parser_.parseLocaleDate() : parser_.parse(format_);

    if (!res) {
      warn(t.row(), t.col(), "date like " + format_, std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }

    DateTime dt = parser_.makeDate();
    if (!dt.validDate()) {
      warn(t.row(), t.col(), "valid date", std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }
    REAL(column_)[i] = dt.date();
    return;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    REAL(column_)[i] = NA_REAL;
    return;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorDateTime::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);
    std::string std_string(string.first, string.second);

    parser_.setDate(std_string.c_str());
    bool res =
        (format_.empty()) ? parser_.parseISO8601() : parser_.parse(format_);

    if (!res) {
      warn(t.row(), t.col(), "date like " + format_, std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }

    DateTime dt = parser_.makeDateTime();
    if (!dt.validDateTime()) {
      warn(t.row(), t.col(), "valid date", std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }

    REAL(column_)[i] = dt.datetime();
    return;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    REAL(column_)[i] = NA_REAL;
    return;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorDouble::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators str = t.getString(&buffer);

    const char* end = str.second;
    bool ok =
        parseDouble(decimalMark_, str.first, str.second, REAL(column_)[i]);
    if (!ok) {
      REAL(column_)[i] = NA_REAL;
      SourceIterators org_str = t.getString(&buffer);
      warn(t.row(), t.col(), "a double", org_str);
      return;
    }

    if (str.second != end) {
      REAL(column_)[i] = NA_REAL;
      SourceIterators org_str = t.getString(&buffer);
      warn(t.row(), t.col(), "no trailing characters", org_str);
      return;
    }

    return;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    REAL(column_)[i] = NA_REAL;
    break;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorDouble::setValue(int i, size_t st) { REAL(column_)[i] = st; }

void CollectorFactor::insert(
    int i, const cpp11::r_string& str, const Token& t) {
  auto it = levelset_.find(str);
  if (it == levelset_.end()) {
    if (implicitLevels_ || (includeNa_ && str == NA_STRING)) {
      int n = levelset_.size();
      levelset_.insert(std::make_pair(str, n));
      levels_.push_back(str);
      INTEGER(column_)[i] = n + 1;
    } else {
      warn(t.row(), t.col(), "value in level set", str);
      INTEGER(column_)[i] = NA_INTEGER;
    }
  } else {
    INTEGER(column_)[i] = it->second + 1;
  }
}

void CollectorFactor::setValue(int i, const Token& t) {

  switch (t.type()) {
  case TOKEN_EMPTY:
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);

    cpp11::r_string std_string(
        pEncoder_->makeSEXP(string.first, string.second, t.hasNull()));
    insert(i, std_string, t);
    return;
  };
  case TOKEN_MISSING:
    if (includeNa_) {
      insert(i, NA_STRING, t);
    } else {
      INTEGER(column_)[i] = NA_INTEGER;
    }
    return;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorInteger::setValue(int i, const Token& t) {

  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators str = t.getString(&buffer);

    bool ok = parseInt(str.first, str.second, INTEGER(column_)[i]);
    if (!ok) {
      INTEGER(column_)[i] = NA_INTEGER;
      SourceIterators org_str = t.getString(&buffer);
      warn(t.row(), t.col(), "an integer", org_str);
      return;
    }

    if (str.first != str.second) {
      SourceIterators org_str = t.getString(&buffer);
      warn(t.row(), t.col(), "no trailing characters", org_str);
      INTEGER(column_)[i] = NA_INTEGER;
      return;
    }

    return;
  };
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    INTEGER(column_)[i] = NA_INTEGER;
    break;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorLogical::setValue(int i, const Token& t) {

  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);
    std::string str(string.first, string.second);
    size_t len = string.second - string.first;

    if (isTrue(string.first, string.second) ||
        (len == 1 && *string.first == '1')) {
      LOGICAL(column_)[i] = 1;
      return;
    }
    if (isFalse(string.first, string.second) ||
        (len == 1 && *string.first == '0')) {
      LOGICAL(column_)[i] = 0;
      return;
    }

    warn(t.row(), t.col(), "1/0/T/F/TRUE/FALSE", string);
    LOGICAL(column_)[i] = NA_LOGICAL;
    return;
  };
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    LOGICAL(column_)[i] = NA_LOGICAL;
    return;
    break;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorNumeric::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators str = t.getString(&buffer);

    bool ok = parseNumber(
        decimalMark_, groupingMark_, str.first, str.second, REAL(column_)[i]);

    if (!ok) {
      SourceIterators org_str = t.getString(&buffer);
      REAL(column_)[i] = NA_REAL;
      warn(t.row(), t.col(), "a number", org_str);
      return;
    }

    break;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    REAL(column_)[i] = NA_REAL;
    break;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorTime::setValue(int i, const Token& t) {
  switch (t.type()) {
  case TOKEN_STRING: {
    std::string buffer;
    SourceIterators string = t.getString(&buffer);
    std::string std_string(string.first, string.second);

    parser_.setDate(std_string.c_str());
    bool res =
        (format_.empty()) ? parser_.parseLocaleTime() : parser_.parse(format_);

    if (!res) {
      warn(t.row(), t.col(), "time like " + format_, std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }

    DateTime dt = parser_.makeTime();
    if (!dt.validDuration()) {
      warn(t.row(), t.col(), "valid duration", std_string);
      REAL(column_)[i] = NA_REAL;
      return;
    }
    REAL(column_)[i] = dt.time();
    return;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    REAL(column_)[i] = NA_REAL;
    return;
  case TOKEN_EOF:
    cpp11::stop("Invalid token");
  }
}

void CollectorRaw::setValue(int i, const Token& t) {
  if (t.type() == TOKEN_EOF) {
    cpp11::stop("Invalid token");
  }
  SET_VECTOR_ELT(column_, i, t.asRaw());
}

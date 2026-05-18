#include "cpp11/R.hpp"
#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"

#include "DateTime.h"
#include "DateTimeParser.h"
#include "LocaleInfo.h"
#include "QiParsers.h"
#include "utils.h"

typedef bool (*canParseFun)(const std::string&, LocaleInfo* pLocale);

bool canParse(
    const cpp11::strings& x, const canParseFun& canParse, LocaleInfo* pLocale) {
  for (const auto & i : x) {
    if (i == NA_STRING) {
      continue;
    }

    if (i.size() == 0) {
      continue;
    }

    if (!canParse(std::string(i), pLocale)) {
      return false;
    }
  }
  return true;
}

bool allMissing(const cpp11::strings& x) {
  for (const auto & i : x) {
    if (i != NA_STRING && i.size() > 0) {
      return false;
    }
  }
  return true;
}

bool isLogical(const std::string& x, LocaleInfo* /*unused*/) {
  const char* const str = x.data();
  bool res = isLogical(str, str + x.size());
  return res;
}

bool isNumber(const std::string& x, LocaleInfo* pLocale) {
  // Leading zero not followed by decimal mark
  if (x[0] == '0' && x.size() > 1 && x[1] != pLocale->decimalMark_) {
    return false;
  }

  double res = 0;
  std::string::const_iterator begin = x.begin();

  std::string::const_iterator end = x.end();

  bool ok = parseNumber(
      pLocale->decimalMark_, pLocale->groupingMark_, begin, end, res);
  return ok && begin == x.begin() && end == x.end();
}

bool isInteger(const std::string& x, LocaleInfo* /*unused*/) {
  // Leading zero
  if (x[0] == '0' && x.size() > 1) {
    return false;
  }

  double res = 0;
  std::string::const_iterator begin = x.begin();

  std::string::const_iterator end = x.end();

  return parseInt(begin, end, res) && begin == end;
}

bool isDouble(const std::string& x, LocaleInfo* pLocale) {
  // Leading zero not followed by decimal mark
  if (x[0] == '0' && x.size() > 1 && x[1] != pLocale->decimalMark_) {
    return false;
  }

  double res = 0;
  const char* begin = x.c_str();
  const char* end = begin + x.size();

  return parseDouble(pLocale->decimalMark_, begin, end, res) &&
         end == begin + x.size();
}

bool isTime(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  return parser.parseLocaleTime();
}

bool isDate(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);
  parser.setDate(x.c_str());

  // Explicit date-only order (no '_' suffix means date-only, e.g. "mdy", "dmy")
  if (!pLocale->dateOrder_.empty() &&
      pLocale->dateOrder_.find('_') == std::string::npos) {
    return parser.parseDateOrder(pLocale->dateOrder_);
  }

  // If a datetime order is explicitly set, don't match as date-only
  if (!pLocale->dateOrder_.empty()) {
    return false;
  }

  // Auto-detection: locale date format first (handles YMD/%AD), then year-last heuristic
  if (parser.parseLocaleDate()) return true;

  parser.setDate(x.c_str());
  return parser.parseYearLastHeuristic();
}

static bool isDateTime(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);
  parser.setDate(x.c_str());

  // Explicit datetime order (has '_' suffix, e.g. "mdy_hms", "dmy_hm")
  if (!pLocale->dateOrder_.empty() &&
      pLocale->dateOrder_.find('_') != std::string::npos) {
    if (!parser.parseDateOrder(pLocale->dateOrder_)) return false;
    return parser.makeDateTime().validDateTime();
  }

  // If a date-only order is explicitly set, don't match as datetime
  if (!pLocale->dateOrder_.empty()) {
    return false;
  }

  // Auto-detection: ISO8601 only (YMD, existing behavior — no change)
  bool ok = parser.parseISO8601();
  if (!ok) return false;

  if (!parser.compactDate()) return true;
  return parser.year() > 999;
}

[[cpp11::register]] std::string collectorGuess(
    const cpp11::strings& input,
    const cpp11::list& locale_,
    bool guessInteger) {
  LocaleInfo locale(static_cast<SEXP>(locale_));

  if (input.size() == 0) {
    return "character";
  }

  if (allMissing(input)) {
    return "logical";
  }

  // Work from strictest to most flexible
  if (canParse(input, isLogical, &locale)) {
    return "logical";
  }
  if (guessInteger && canParse(input, isInteger, &locale)) {
    return "integer";
  }
  if (canParse(input, isDouble, &locale)) {
    return "double";
  }
  if (canParse(input, isNumber, &locale)) {
    return "number";
  }
  if (canParse(input, isTime, &locale)) {
    return "time";
  }
  if (canParse(input, isDate, &locale)) {
    return "date";
  }
  if (canParse(input, isDateTime, &locale)) {
    return "datetime";
  }

  // Otherwise can always parse as a character
  return "character";
}

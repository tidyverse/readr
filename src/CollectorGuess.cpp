#include <Rcpp.h>
using namespace Rcpp;

#include "DateTime.h"
#include "DateTimeParser.h"
#include "LocaleInfo.h"
#include "QiParsers.h"

typedef bool (*canParseFun)(const std::string&, LocaleInfo* pLocale);

bool canParse(CharacterVector x, const canParseFun& canParse,
              LocaleInfo* pLocale) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] == NA_STRING)
      continue;

    if (x[i].size() == 0)
      continue;

    if (!canParse(std::string(x[i]), pLocale))
      return false;
  }
  return true;
}

bool allMissing(CharacterVector x) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] != NA_STRING && x[i].size() > 0)
      return false;
  }
  return true;
}

bool isLogical(const std::string& x, LocaleInfo* pLocale) {
  return x == "T" || x == "F" || x == "TRUE" || x == "FALSE";
}

bool isInteger(const std::string& x, LocaleInfo* pLocale) {
  if (x[0] == '0' && x.size() > 1)
    return false;

  int res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  return parseInt(begin, end, res) && begin == end;
}

bool isNumber(const std::string& x, LocaleInfo* pLocale) {
  // Leading zero not followed by decimal mark
  if (x[0] == '0' && x.size() > 1 && x[1] != pLocale->decimalMark_)
    return false;

  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  bool ok = parseNumber(pLocale->decimalMark_, pLocale->groupingMark_,
    begin, end, res);
  return ok && begin == x.begin() && end == x.end();
}

bool isDouble(const std::string& x, LocaleInfo* pLocale) {
  // Leading zero not followed by decimal mark
  if (x[0] == '0' && x.size() > 1 && x[1] != pLocale->decimalMark_)
    return false;

  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  return parseDouble(pLocale->decimalMark_, begin, end, res) && begin == end;
}

bool isTime(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  return parser.parseTime();
}

bool isDate(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  return parser.parse(pLocale->dateFormat_);
}

static bool isDateTime(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  bool ok = parser.parseISO8601();

  if (!ok)
    return false;

  if (!parser.compactDate())
    return true;

  // Values like 00014567 are unlikely to be dates, so don't guess
  return parser.year() > 999;
}

// [[Rcpp::export]]
std::string collectorGuess(CharacterVector input, List locale_) {
  LocaleInfo locale(locale_);

  if (input.size() == 0 || allMissing(input))
    return "character";

  // Work from strictest to most flexible
  if (canParse(input, isLogical, &locale))
    return "logical";
  if (canParse(input, isInteger, &locale))
    return "integer";
  if (canParse(input, isDouble, &locale))
    return "double";
  if (canParse(input, isNumber, &locale))
    return "number";
  if (canParse(input, isTime, &locale))
    return "time";
  if (canParse(input, isDate, &locale))
    return "date";
  if (canParse(input, isDateTime, &locale))
    return "datetime";

  // Otherwise can always parse as a character
  return "character";
}

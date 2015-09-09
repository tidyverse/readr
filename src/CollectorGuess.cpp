#include <Rcpp.h>
using namespace Rcpp;

#include "DateTime.h"
#include "DateTimeParser.h"
#include "LocaleInfo.h"
#include "QiParsers.h"

typedef bool (*canParseFun)(const std::string&, const LocaleInfo& locale);

bool canParse(CharacterVector x, const canParseFun& canParse,
              const LocaleInfo& locale) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] == NA_STRING)
      continue;

    if (x[i].size() == 0)
      continue;

    if (!canParse(std::string(x[i]), locale))
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

bool isLogical(const std::string& x, const LocaleInfo& locale) {
  return x == "T" || x == "F" || x == "TRUE" || x == "FALSE";
}

bool isInteger(const std::string& x, const LocaleInfo& locale) {
  int res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  return parseInt(begin, end, res) && begin == end;
}

bool isDouble(const std::string& x, const LocaleInfo& locale) {
  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  return parseDouble(locale.decimalMark_, begin, end, res) && begin == end;
}

bool isDate(const std::string& x, const LocaleInfo& locale) {
  DateTimeLocale loc;
  DateTimeParser parser(loc, "UTC"); // TZ doesn't actually matter here

  parser.setDate(x.c_str());
  return parser.parse(locale.dateFormat_);
}

static bool isDateTime(const std::string& x, const LocaleInfo& locale) {
  DateTimeLocale loc;
  DateTimeParser parser(loc, locale.tz_);

  parser.setDate(x.c_str());
  return parser.parseISO8601();
}


// [[Rcpp::export]]
std::string collectorGuess(CharacterVector input, List locale_) {
  LocaleInfo locale(locale_);

  if (allMissing(input))
    return "character";

  // Work from strictest to most flexible
  if (canParse(input, isLogical, locale))
    return "logical";
  if (canParse(input, isInteger, locale))
    return "integer";
  if (canParse(input, isDouble, locale))
    return "double";
  if (canParse(input, isDate, locale))
    return "date";
  if (canParse(input, isDateTime, locale))
    return "datetime";

  // Otherwise can always parse as a character
  return "character";
}

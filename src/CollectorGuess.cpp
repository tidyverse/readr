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
  int res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();
  if (x[0] == '0' && x.size() > 1)
    return false;

  return parseInt(begin, end, res) && begin == end;
}

bool canParseNumber(CharacterVector x, LocaleInfo* pLocale) {
  double tmp = 0;
  int prefix = -1, suffix = -1;

  for (int i = 0; i < x.size(); ++i) {
    if (x[i] == NA_STRING)
      continue;

    if (x[i].size() == 0)
      return false;

    std::string xstr = std::string(x[i]);
    std::string::const_iterator begin = xstr.begin(), end = xstr.end();

    // Leading zero not followed by decimal mark
    if (xstr[0] == '0' && xstr.size() > 1 && xstr[1] != pLocale->decimalMark_)
      return false;

    bool ok = parseNumber(pLocale->decimalMark_, pLocale->groupingMark_,
      begin, end, tmp);
    if (!ok)
      return false;

    // Make sure no more than 6 characters in prefix/suffix
    int curPrefix = begin - xstr.begin(), curSuffix = xstr.end() - end;
    if (curPrefix + curSuffix > 6)
      return false;

    // Make sure every value has same prefix and suffix length
    if (prefix == -1)
      prefix = curPrefix;
    if (suffix == -1)
      suffix = curSuffix;

    if (suffix != curSuffix || prefix != curPrefix)
      return false;

    // Make sure suffix/prefix don't contain any numbers
    for(std::string::const_iterator cur = xstr.begin(); cur < begin; ++cur) {
      if (*cur >= '0' && *cur <= '9')
        return false;
    }
    for(std::string::const_iterator cur = end; cur < xstr.end(); ++cur) {
      if (*cur >= '0' && *cur <= '9')
        return false;
    }
  }
  return true;
}

bool isDouble(const std::string& x, LocaleInfo* pLocale) {
  // Leading zero not followed by decimal mark
  if (x[0] == '0' && x.size() > 1 && x[1] != pLocale->decimalMark_)
    return false;

  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();

  return parseDouble(pLocale->decimalMark_, begin, end, res) && begin == end;
}

bool isDate(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  return parser.parse(pLocale->dateFormat_);
}

static bool isDateTime(const std::string& x, LocaleInfo* pLocale) {
  DateTimeParser parser(pLocale);

  parser.setDate(x.c_str());
  return parser.parseISO8601();
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
  if (canParseNumber(input, &locale))
    return "number";
  if (canParse(input, isDate, &locale))
    return "date";
  if (canParse(input, isDateTime, &locale))
    return "datetime";

  // Otherwise can always parse as a character
  return "character";
}

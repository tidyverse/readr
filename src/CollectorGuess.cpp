#include <Rcpp.h>
using namespace Rcpp;

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include "DoubleEuroPolicy.h"
#include "DateTime.h"
#include "DateTimeParser.h"
namespace qi = boost::spirit::qi;

typedef bool (*canParseFun)(const std::string&);

bool canParse(CharacterVector x, const canParseFun& canParse) {
  for (int i = 0; i < x.size(); ++i) {
    if (x[i] == NA_STRING)
      continue;

    if (x[i].size() == 0)
      continue;

    if (!canParse(std::string(x[i])))
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

bool isLogical(const std::string& x) {
  return x == "T" || x == "F" || x == "TRUE" || x == "FALSE";
}

bool isInteger(const std::string& x) {
  int res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();
  return qi::parse(begin, end, qi::int_, res) && begin == end;
}

bool isDouble(const std::string& x) {
  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();
  return qi::parse(begin, end, qi::double_, res) && begin == end;
}

bool isEuroDouble(const std::string& x) {
  double res = 0;
  std::string::const_iterator begin = x.begin(), end = x.end();
  return qi::parse(begin, end, qi::real_parser<double, DoubleEuroPolicy>(), res) && begin == end;
}

bool isDate(const std::string& x) {
  DateTimeLocale loc;
  DateTimeParser parser(loc, "UTC");

  parser.setDate(x.c_str());
  return parser.parse(std::string("%Y%.%m%.%d"));
}

static bool isDateTime(const std::string& x) {
  DateTimeLocale loc;
  DateTimeParser parser(loc, "UTC");

  parser.setDate(x.c_str());
  return parser.parseISO8601();
}


// [[Rcpp::export]]
std::string collectorGuess(CharacterVector input) {
  if (allMissing(input))
    return "character";

  // Work from strictest to most flexible
  if (canParse(input, isLogical))
    return "logical";
  if (canParse(input, isInteger))
    return "integer";
  if (canParse(input, isDouble))
    return "double";
  if (canParse(input, isEuroDouble))
    return "euro_double";
  if (canParse(input, isDate))
    return "date";
  if (canParse(input, isDateTime))
    return "datetime";

  // Otherwise can always parse as a character
  return "character";
}

#include <Rcpp.h>
#include <ctime>
#include "DateTime.h"
#include "DateTimeLocale.h"
#include <boost/algorithm/string/predicate.hpp>

// Parsing ---------------------------------------------------------------------

// First element is position, second element is length
std::pair<int, int> findMatch(const char* needle, const std::vector<std::string>& haystack) {
  for(size_t i = 0; i < haystack.size(); ++i)
    if (boost::starts_with(needle, haystack[i]))
      return std::make_pair(i, haystack[i].size());

  return std::make_pair(-1, 0);
}

int matchMonth(const char** pDate, const DateTimeLocale& loc) {
  std::pair<int,int> full_match = findMatch(*pDate, loc.month());
  if (full_match.first != -1) {
    *pDate += full_match.second;
    return full_match.first;
  }

  std::pair<int,int> abbr_match = findMatch(*pDate, loc.monthAbbrev());
  if (abbr_match.first != 0) {
    *pDate += abbr_match.second;
    return abbr_match.first;
  }

  return false;
}

int matchDay(const char** pDate, const DateTimeLocale& loc) {
  std::pair<int,int> full_match = findMatch(*pDate, loc.day());
  if (full_match.first != -1) {
    *pDate += full_match.second;
    return full_match.first;
  }

  std::pair<int,int> abbr_match = findMatch(*pDate, loc.monthAbbrev());
  if (abbr_match.first != 0) {
    *pDate += abbr_match.second;
    return abbr_match.first;
  }

  return false;
}


// [[Rcpp::export]]
int findMonth(std::string month) {
  DateTimeLocale loc;

  const char* string = month.c_str();
  return matchMonth(&string, loc);
}

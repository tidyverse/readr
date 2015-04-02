#include <Rcpp.h>
#include <ctime>
#include "DateTime.h"
#include "DateTimeLocale.h"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
namespace qi = boost::spirit::qi;
using namespace Rcpp;

// Parsing ---------------------------------------------------------------------

class DateTimeParser {
  int year_, mon_, day_, hour_, min_, sec_;
  double psec_;
  const DateTimeLocale& locale_;

  const char* dateItr_;
  const char* dateEnd_;

public:
  DateTimeParser(const DateTimeLocale& locale): locale_(locale)
  {
    reset();
  }

  // Parse ISO8601 date time. In benchmarks this only seems ~30% faster than
  // parsing with a format string so it doesn't seem necessary to add individual
  // parsers for other common formats.
  bool parse() {
    // Date: 2015-04-01
    if (consumeInteger1(4, &year_))
      return false;
    if (!consumeThisChar('-'))
      return false;
    if (consumeInteger1(2, &mon_))
      return false;
    if (consumeThisChar('-'))
      return false;
    if (consumeInteger(2, &day_))
      return false;

    if (isComplete())
      return true;

    // Technically, spec requires T, but very common to use
    char next;
    if (!consumeChar(&next))
      return false;
    if (next != 'T' && next != ' ')
      return false;

    // Time: 08:41:51
    if (consumeInteger(2, &hour_))
      return false;
    if (!consumeThisChar(':'))
      return false;
    if (consumeInteger(2, &min_))
      return false;
    if (!consumeThisChar(':'))
      return false;
    if (consumeSeconds(&sec_, &psec_))
      return false;

    if (isComplete())
      return true;

    // Time zone:
    Rcpp::stop("Time zones not supported yet");

    return true;
  }

  bool isComplete() {
    return dateItr_ == dateEnd_;
  }

  void setDate(const char* date) {
    init(date);
  }

  bool parse(const std::string& format) {
    consumeWhiteSpace(); // always consume leading whitespace

    std::string::const_iterator formatItr, formatEnd = format.end();
    for (formatItr = format.begin(); formatItr != formatEnd; ++formatItr) {
      // Whitespace in format matches 0 or more whitespace in date
      if (std::isspace(*formatItr)) {
        consumeWhiteSpace();
        continue;
      }

      // Any other characters much much exactly.
      if (*formatItr != '%') {
        if (!consumeThisChar(*formatItr))
          return false;
        continue;
      }

      if (formatItr + 1 == formatEnd)
        Rcpp::stop("Invalid format: trailing %");
      formatItr++;

      switch(*formatItr) {
      case 'Y': // year with century
        if (!consumeInteger(4, &year_))
          return false;
        break;
      case 'y': // year without century
        if (!consumeInteger(2, &year_))
          return false;
        year_ += (year_ < 69) ? 2000 : 1900;
        break;
      case 'm': // month
        if (!consumeInteger1(2, &mon_))
          return false;
        break;
      case 'd': // day
        if (!consumeInteger1(2, &day_))
          return false;
        break;
      case 'e': // day with optional leading space
        if (!consumeInteger1WithSpace(2, &day_))
          return false;
        break;
      case 'H': // hour
        if (!consumeInteger(2, &hour_))
          return false;
        break;
      case 'M': // minute
        if (!consumeInteger(2, &min_))
          return false;
        break;
      case 'S': // seconds (integer)
        if (!consumeSeconds(&sec_, NULL))
          return false;
        break;
      case 'O': // seconds (double)
        if (formatItr + 1 == formatEnd || *(formatItr + 1) != 'S')
          Rcpp::stop("Invalid format: %%O must be followed by %%S");
        formatItr++;
        if (!consumeSeconds(&sec_, &psec_))
          return false;
        break;

      // Compound formats
      case 'D':
        parse("%m/%d/%y");
        break;
      case 'F':
        parse("%Y-%m-%d");
        break;
      case 'R':
        parse("%H:%M");
        break;
      case 'X':
      case 'T':
        parse("%H:%M:%S");
        break;
      case 'x':
        parse("%y/%m/%d");
        break;

      default:
        Rcpp::stop("Unsupported format %%%s", *formatItr);
      }
    }
    consumeWhiteSpace(); // always consume trailing whitespace

    return isValid();
  }

  DateTime makeDate() {
    DateTime dt(year_, mon_, day_, hour_, min_, sec_, psec_);
    return dt;
  }

private:
  bool isValid() {
    // Must have year, month and day
    if (year_ == -1 || mon_ == -1 || day_ == -1)
      return false;

    return true;
  }

  inline bool consumeSeconds(int* pSec, double* pPartialSec) {
    double sec;
    if (!consumeDouble(&sec))
      return false;

    *pSec = (int) sec;
    if (pPartialSec != NULL)
      *pPartialSec = sec - *pSec;
    return true;
  }

  inline bool consumeInteger(int n, int* pOut) {
    return qi::parse(dateItr_, std::min(dateItr_ + n, dateEnd_), qi::int_, *pOut);
  }


  // Integer indexed from 1 (i.e. month and date)
  inline bool consumeInteger1(int n, int* pOut) {
    if (!consumeInteger(n, pOut))
      return false;

    (*pOut)--;
    return true;
  }

  // Integer indexed from 1 with optional space
  inline bool consumeInteger1WithSpace(int n, int* pOut) {
    if (consumeThisChar(' '))
      n--;

    return consumeInteger1(n, pOut);
  }

  inline bool consumeDouble(double* pOut) {
    return qi::parse(dateItr_, dateEnd_, qi::double_, *pOut);
  }

  inline bool consumeWhiteSpace() {
    while (dateItr_ != dateEnd_ && std::isspace(*dateItr_))
      dateItr_++;

    return true;
  }

  inline bool consumeChar(char* pOut) {
    *pOut = *dateItr_++;
    return true;
  }

  inline bool consumeThisChar(char needed) {
    if (*dateItr_ != needed)
      return false;

    dateItr_++;
    return true;
  }

  void init(const char* date) {
    reset();
    dateItr_ = date;

    // find terminating null character
    dateEnd_ = date;
    while (*dateEnd_)
      dateEnd_++;
  }

  void reset() {
    year_ = -1;
    mon_ = -1;
    day_ = -1;
    hour_ = 0;
    min_ = 0;
    sec_ = 0;
    psec_ = 0;
  }
};

// [[Rcpp::export]]
NumericVector date_parse(CharacterVector dates, std::string format = "", bool strict = true) {
  int n = dates.size();

  DateTimeLocale loc;
  DateTimeParser parser(loc);

  NumericVector out = NumericVector(n);
  for (int i = 0; i < n; ++i) {
    const char* string = CHAR(STRING_ELT(dates, i));
    parser.setDate(string);
    bool res = (format == "") ? parser.parse() : parser.parse(format);

    if (!res) {
      out[i] = NA_REAL;
    } else {
      DateTime dt = parser.makeDate();
      if (!strict)
        dt.repair();
      out[i] = dt.utctime();
    }
  }

  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";

  return out;
}

// // First element is position, second element is length
// std::pair<int, int> findMatch(const char* needle, const std::vector<std::string>& haystack) {
//   for(size_t i = 0; i < haystack.size(); ++i)
//     if (boost::starts_with(needle, haystack[i]))
//       return std::make_pair(i, haystack[i].size());
//
//   return std::make_pair(-1, 0);
// }
//
// int matchMonth(const char** pDate, const DateTimeLocale& loc) {
//   std::pair<int,int> full_match = findMatch(*pDate, loc.month());
//   if (full_match.first != -1) {
//     *pDate += full_match.second;
//     return full_match.first;
//   }
//
//   std::pair<int,int> abbr_match = findMatch(*pDate, loc.monthAbbrev());
//   if (abbr_match.first != 0) {
//     *pDate += abbr_match.second;
//     return abbr_match.first;
//   }
//
//   return -1;
// }
//
// int matchDay(const char** pDate, const DateTimeLocale& loc) {
//   std::pair<int,int> full_match = findMatch(*pDate, loc.day());
//   if (full_match.first != -1) {
//     *pDate += full_match.second;
//     return full_match.first;
//   }
//
//   std::pair<int,int> abbr_match = findMatch(*pDate, loc.monthAbbrev());
//   if (abbr_match.first != 0) {
//     *pDate += abbr_match.second;
//     return abbr_match.first;
//   }
//
//   return -1;
// }
//
// int matchPeriod(const char** pDate, const DateTimeLocale& loc) {
//   std::pair<int,int> full_match = findMatch(*pDate, loc.period());
//   if (full_match.first != -1) {
//     *pDate += full_match.second;
//     return full_match.first;
//   }
//
//   return -1;
// }

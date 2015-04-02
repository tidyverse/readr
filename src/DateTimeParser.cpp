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

  bool parseISO8601(const char* date) {
    init(date);

    // Date: 2015-04-01
    if ((year_ = consumeInteger(4)) == -1)
      return false;
    if (consumeChar() != '-')
      return false;
    if ((mon_ = consumeInteger(2) - 1) == -1)
      return false;
    if (consumeChar() != '-')
      return false;
    if ((day_ = consumeInteger(2) - 1) == -1)
      return false;

    if (isComplete())
      return true;

    // Technically, spec requires T, but very common to use
    char next = consumeChar();
    if (next != 'T' && next != ' ')
      return false;

    // Time: 08:41:51
    if ((hour_ = consumeInteger(2)) == -1)
      return false;
    if (consumeChar() != ':')
      return false;
    if ((min_ = consumeInteger(2)) == -1)
      return false;
    if (consumeChar() != ':')
      return false;
    if (!parseSeconds())
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

  bool parseDate(const char* date, const std::string& format) {
    init(date);

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
        if (*formatItr != consumeChar())
          return false;
        continue;
      }

      if (formatItr + 1 == formatEnd)
        Rcpp::stop("Invalid format: trailing %");
      formatItr++;

      switch(*formatItr) {
      case 'Y': // year with century
        if ((year_ = consumeInteger(4)) == -1)
          return false;
        break;
      case 'y': // year without century
        if ((year_ = consumeInteger(2)) == -1)
          return false;
        year_ += (year_ < 69) ? 2000 : 1900;
        break;
      case 'm': // month
        if ((mon_ = consumeInteger(2)) == -1)
          return false;
        mon_--;
        break;
      case 'd': // day
        if ((day_ = consumeInteger(2)) == -1)
          return false;
        day_--;
        break;
      case 'H': // hour
        if ((hour_ = consumeInteger(2)) == -1)
          return false;
        break;
      case 'M': // minute
        if ((min_ = consumeInteger(2)) == -1)
          return false;
        break;
      case 'S': // seconds (integer)
        if ((sec_ = consumeInteger(2)) == -1)
          return false;
        break;
      case 'O': // seconds (double)
        if (formatItr + 1 == formatEnd || *(formatItr + 1) != 'S')
          Rcpp::stop("Invalid format: %%O must be followed by %%S");
        formatItr++;
        if (!parseSeconds())
          return false;

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

  inline bool parseSeconds() {
    psec_ = consumeDouble();
    if (psec_ == -1)
      return false;

    sec_ = (int) psec_;
    psec_ -= sec_;
    return true;
  }

  inline int consumeInteger(int n) {
    int res = 0;
    bool ok = qi::parse(dateItr_, std::min(dateItr_ + n, dateEnd_), qi::int_, res);

    return ok ? res : -1;
  }

  inline double consumeDouble() {
    double res = 0;

    bool ok = qi::parse(dateItr_, dateEnd_, qi::double_, res);
    return ok ? res : -1;
  }

  inline void consumeWhiteSpace() {
    while (dateItr_ != dateEnd_ && std::isspace(*dateItr_))
      dateItr_++;
  }

  char consumeChar() {
    char out = *dateItr_;
    dateItr_++;
    return out;
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
    bool res;
    if (format == "") {
      res = parser.parseISO8601(string);
    } else {
      res = parser.parseDate(string, format);
    }

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

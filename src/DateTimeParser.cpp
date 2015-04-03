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

  int tzOffsetHours_, tzOffsetMinutes_;
  std::string tz_;

  const DateTimeLocale& locale_;
  std::string tzDefault_;

  const char* dateItr_;
  const char* dateEnd_;

public:
  DateTimeParser(const DateTimeLocale& locale, const std::string& tzDefault = ""):
    locale_(locale), tzDefault_(tzDefault)
  {
  }

  // Parse ISO8601 date time. In benchmarks this only seems ~30% faster than
  // parsing with a format string so it doesn't seem necessary to add individual
  // parsers for other common formats.
  bool parse() {
    // Date: YYYY-MM-DD, YYYYMMDD
    if (!consumeInteger(4, &year_))
      return false;
    consumeThisChar('-');
    if (!consumeInteger1(2, &mon_))
      return false;
    consumeThisChar('-');
    if (!consumeInteger1(2, &day_))
      return false;

    if (isComplete())
      return true;

    // Technically, spec requires T, but very common to use
    char next;
    if (!consumeChar(&next))
      return false;
    if (next != 'T' && next != ' ')
      return false;

    // hh:mm:ss.sss, hh:mm:ss, hh:mm, hh
    // hhmmss.sss, hhmmss, hhmm
    if (!consumeInteger(2, &hour_))
      return false;
    consumeThisChar(':');
    consumeInteger(2, &min_);
    consumeThisChar(':');
    consumeSeconds(&sec_, &psec_);

    if (isComplete())
      return true;

    // Has a timezone
    tz_ = "UTC";
    if (!consumeTzOffset(&tzOffsetHours_, &tzOffsetMinutes_))
      return false;

    return isComplete() && isValid();
  }

  bool isComplete() {
    return dateItr_ == dateEnd_;
  }

  void setDate(const char* date) {
    init(date);
    reset();
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

      case 'z': // time zone specification
        tz_ = "UTC";
        if (!consumeTzOffset(&tzOffsetHours_, &tzOffsetMinutes_))
          return false;
        break;
      case 'Z': // time zone name
        if (!consumeTzName(&tz_))
          return false;
        break;

      // Extensions
      case '.':
        consumeNonDigit();
        break;

      case '*':
        consumeNonDigits();
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

    return isComplete() && isValid();
  }

  DateTime makeDate(TzManager& tzMan) {
    DateTime dt(tzMan, year_, mon_, day_, hour_, min_, sec_, psec_, tz_);
    if (tz_ == "UTC")
      dt.offset(tzOffsetHours_, tzOffsetMinutes_);

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
    if (dateItr_ == dateEnd_ || *dateItr_ == '-' || *dateItr_ == '+')
      return false;

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
    if (dateItr_ == dateEnd_ || *dateItr_ == '-' || *dateItr_ == '+')
      return false;
    return qi::parse(dateItr_, dateEnd_, qi::double_, *pOut);
  }

  inline bool consumeWhiteSpace() {
    while (dateItr_ != dateEnd_ && std::isspace(*dateItr_))
      dateItr_++;

    return true;
  }

  inline bool consumeNonDigit() {
    if (dateItr_ == dateEnd_ || std::isdigit(*dateItr_))
      return false;

    dateItr_++;
    return true;
  }

  inline bool consumeNonDigits() {
    while (dateItr_ != dateEnd_ && !std::isdigit(*dateItr_))
      dateItr_++;

    return true;
  }

  inline bool consumeChar(char* pOut) {
    if (dateItr_ == dateEnd_)
      return false;

    *pOut = *dateItr_++;
    return true;
  }

  inline bool consumeThisChar(char needed) {
    if (dateItr_ == dateEnd_ || *dateItr_ != needed)
      return false;

    dateItr_++;
    return true;
  }

  // ISO8601 style
  // Z
  // ±hh:mm
  // ±hhmm
  // ±hh
  inline bool consumeTzOffset(int* pHours, int* pMinutes) {
    if (consumeThisChar('Z'))
      return true;

    // Optional +/- (required for ISO8601 but we'll let it slide)
    int mult = 1;
    if (*dateItr_ == '+' || *dateItr_ == '-') {
      mult = (*dateItr_ == '-') ? -1 : 1;
      dateItr_++;
    }

    // Required hours
    if (!consumeInteger(2, pHours))
      return false;

    // Optional colon and minutes
    consumeThisChar(':');
    consumeInteger(2, pMinutes);

    *pHours *= mult;
    *pMinutes *= mult;

    return true;
  }

  inline bool consumeTzName(std::string* pOut) {
    const char* tzStart = dateItr_;
    while (dateItr_ != dateEnd_ && !std::isspace(*dateItr_))
      dateItr_++;

    pOut->assign(tzStart, dateItr_);
    return tzStart != dateItr_;
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

    tzOffsetHours_ = 0;
    tzOffsetMinutes_ = 0;
    tz_ = tzDefault_;
  }
};

//' Parse a character vector of dates.
//'
//' @section Format specification:
//' \code{readr} uses a format specification similiar to \code{\link{strptime}}.
//' There are three types of element:
//'
//' \enumerate{
//'   \item Date components are specified with "\%" followed by a letter.
//'     For example "\%Y" matches a 4 digit year, "\%m", matches a 2 digit
//'     month and "\%d" matches a 2 digit day.
//'   \item Whitespace is any sequence of zero or more whitespace characters.
//'   \item Any other character is matched exactly.
//' }
//'
//' \code{parse_date} recognises the following format specifications:
//' \itemize{
//'   \item Year: "\%Y" (4 digits). "\%y" (2 digits); 00-69 -> 2000-2069,
//'     70-99 -> 1970-1999.
//'   \item Month: "\%m" (2 digits).
//'   \item Day: "\%d" (2 digits), "\%e" (optional leading space)
//'   \item Hour: "\%H"
//'   \item Minutes: "\%M"
//'   \item Seconds: "\%S" (integer seconds), "\%OS" (partial seconds)
//'   \item Time zone: "\%Z" (as name, e.g. "America/Chicago"), "\%z" (as
//'     offset from UTC, e.g. "+0800")
//'   \item Non-digits: "\%." skips one non-digit charcter, "\%*" skips any
//'     number of non-digits characters.
//'   \item Shortcuts: "\%D" = "\%m/\%d/\%y",  "\%F" = "\%Y-\%m-\%d",
//'       "\%R" = "\%H:\%M", "\%T" = "\%H:\%M:\%S",  "\%x" = "\%y/\%m/\%d".
//' }
//'
//' @param dates A character vector of dates to parse.
//' @param format A format specification, as described below. If omitted,
//'   parses dates according to the ISO8601 specification.
//'
//'   Unlike \code{\link{strptime}}, the format specification must match
//'   the complete string.
//' @param tz Default tz. This is used both for input (if the time zone isn't
//'   present in individual strings), and for output (to control the default
//'   display). The default is to use "UTC", a time zone that does not use
//'   daylight savings time (DST) and hence is typically most useful for data.
//'   The absense of time zones makes it approximately 50x faster to generate
//'   UTC times than any other time zone.
//'
//'   Use \code{""} to use the system default time zone, but beware that this
//'   will not be reproducible across systems.
//'
//'   For a complete list of possible time zones, see \code{\link{OlsonNames}()}.
//'   Americans, note that "EST" is a Canadian time zone that does not have
//'   DST. It is \emph{not} Eastern Standard Time. It's better to use
//'   "US/Eastern", "US/Central" etc.
//' @param repair If \code{TRUE}, will attempt to repair invalid dates
//'   like "2000-02-31". Repair works from smallest to largest, first ensuring
//'   seconds lies between 0 and 59, then minutes between 0-59 etc.
//' @return A \code{\link{POSIXct}} vector with \code{tzone} attribute set to
//'   \code{tz}. Elements that could not be parsed (or did not generate valid
//'   dates) will bes set to \code{NA}, and a warning message will inform
//'   you of the total number of failures.
//' @export
//' @examples
//' # Format strings --------------------------------------------------------
//' parse_date("01/02/2010", "%d/%m/%Y")
//' parse_date("01/02/2010", "%m/%d/%Y")
//' # Handle any separator
//' parse_date("01/02/2010", "%m%.%d%.%Y")
//'
//' # You can parse timezones from strings (as listed in OlsonNames())
//' parse_date("2010/01/01 12:00 US/Central", "%Y/%m/%d %H:%M %Z")
//' # Or from offsets
//' parse_date("2010/01/01 12:00 -0600", "%Y/%m/%d %H:%M %z")
//'
//' # Use the tz parameter to control the default time zone
//' # (but note UTC is considerably faster than other options)
//' parse_date("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Central")
//' parse_date("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Eastern")
//'
//' # Unlike strptime, the format specification must match the complete
//' # string (ignoring leading and trailing whitespace). This avoids common
//' # errors:
//' strptime("01/02/2010", "%d/%m/%y")
//' parse_date("01/02/2010", "%d/%m/%y")
//'
//' # ISO8601 --------------------------------------------------------------
//' # With separators
//' parse_date("1979-10-14")
//' parse_date("1979-10-14T10")
//' parse_date("1979-10-14T10:11")
//' parse_date("1979-10-14T10:11:12")
//' parse_date("1979-10-14T10:11:12.12345")
//'
//' # Without separators
//' parse_date("19791014")
//' parse_date("19791014T101112")
//'
//' # Time zones
//' parse_date("1979-10-14T1010", tz = "US/Central")
//' parse_date("1979-10-14T1010-0500", tz = "US/Central")
//' parse_date("1979-10-14T1010Z", tz = "US/Central")
// [[Rcpp::export]]
NumericVector parse_date(CharacterVector dates, std::string format = "",
                         std::string tz = "UTC", bool repair = false) {
  int n = dates.size(), fails = 0;

  DateTimeLocale loc;
  DateTimeParser parser(loc, tz);
  TzManager tzMan(tz);

  NumericVector out = NumericVector(n);
  for (int i = 0; i < n; ++i) {
    const char* string = CHAR(STRING_ELT(dates, i));
    parser.setDate(string);
    bool res = (format == "") ? parser.parse() : parser.parse(format);

    if (!res) {
      fails++;
      out[i] = NA_REAL;
    } else {
      DateTime dt = parser.makeDate(tzMan);
      if (!dt.isValid()) {
        fails++;
        if (repair)
          dt.repair();
      }
      out[i] = dt.time();
    }
  }

  if (fails > 0)
    warning("%i dates failed to parse", fails);

  out.attr("class") = CharacterVector::create("POSIXct", "POSIXt");
  // Always _display_ ISO8601 dates in utc
  out.attr("tzone") = (format == "") ? "UTC" : tz;

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

#include <Rcpp.h>
#include "DateTime.h"
#include "DateTimeLocale.h"
#include "DateTimeParser.h"

using namespace Rcpp;

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
//' \code{parse_datetime} recognises the following format specifications:
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
//' parse_datetime("01/02/2010", "%d/%m/%Y")
//' parse_datetime("01/02/2010", "%m/%d/%Y")
//' # Handle any separator
//' parse_datetime("01/02/2010", "%m%.%d%.%Y")
//'
//' # You can parse timezones from strings (as listed in OlsonNames())
//' parse_datetime("2010/01/01 12:00 US/Central", "%Y/%m/%d %H:%M %Z")
//' # Or from offsets
//' parse_datetime("2010/01/01 12:00 -0600", "%Y/%m/%d %H:%M %z")
//'
//' # Use the tz parameter to control the default time zone
//' # (but note UTC is considerably faster than other options)
//' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Central")
//' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Eastern")
//'
//' # Unlike strptime, the format specification must match the complete
//' # string (ignoring leading and trailing whitespace). This avoids common
//' # errors:
//' strptime("01/02/2010", "%d/%m/%y")
//' parse_datetime("01/02/2010", "%d/%m/%y")
//'
//' # ISO8601 --------------------------------------------------------------
//' # With separators
//' parse_datetime("1979-10-14")
//' parse_datetime("1979-10-14T10")
//' parse_datetime("1979-10-14T10:11")
//' parse_datetime("1979-10-14T10:11:12")
//' parse_datetime("1979-10-14T10:11:12.12345")
//'
//' # Without separators
//' parse_datetime("19791014")
//' parse_datetime("19791014T101112")
//'
//' # Time zones
//' parse_datetime("1979-10-14T1010", tz = "US/Central")
//' parse_datetime("1979-10-14T1010-0500", tz = "US/Central")
//' parse_datetime("1979-10-14T1010Z", tz = "US/Central")
// [[Rcpp::export]]
NumericVector parse_datetime(CharacterVector dates, std::string format = "",
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

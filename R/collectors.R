collector <- function(type, ...) {
  structure(list(...), class = c(paste0("collector_", type), "collector"))
}

#' @export
print.collector <- function(x, ...) {
  cat("<", class(x)[1], ">\n", sep = "")
}

collector_find <- function(name) {
  get(paste0("col_", name), envir = asNamespace("readr"))()
}

#' Parse a character vector.
#'
#' @param x Character vector of elements to parse.
#' @param collector Column specification.
#' @keywords internal
#' @export
#' @examples
#' x <- c("1", "2", "3", NA)
#' parse_vector(x, col_integer())
#' parse_vector(x, col_double())
#' parse_vector(x, col_character())
#' parse_vector(x, col_skip())
#'
#' # Invalid values are replaced with missing values with a warning.
#' x <- c("1", "2", "3", "-")
#' parse_vector(x, col_double())
parse_vector <- function(x, collector) {
  warn_problems(parse_vector_(x, collector))
}

#' Parse character vectors into typed columns.
#'
#' Use \code{parse_} if you have a character vector you want to parse. Use
#' \code{col_} in conjunction with a \code{read_} function to parse the
#' values as they're read in.
#'
#' @name collector
#' @param x Character vector of values to parse.
#' @seealso \code{\link{parse_datetime}}, \code{\link{type_convert}} to
#'   automatically re-parse all character columns in a data frame.
#' @examples
#' parse_integer(c("1", "2", "3"))
#' parse_double(c("1", "2", "3.123"))
#' parse_euro_double(c("1", "2", "3,123"))
#' parse_factor(c("a", "b"), letters)
#' parse_numeric("$1,123,456.000")
#'
#' # If there are parsing problems, you'll get a warning message saying
#' # how many. Use problems() to access a data frame giving more details.
#' x <- parse_integer(c("1X", "blah", "3"))
#' problems(x)
NULL

#' @rdname collector
#' @export
col_character <- function() {
  collector("character")
}

#' @rdname collector
#' @export
parse_character <- function(x) {
  parse_vector(x, col_character())
}

#' @rdname collector
#' @export
col_integer <- function() {
  collector("integer")
}

#' @rdname collector
#' @export
parse_integer <- function(x) {
  parse_vector(x, col_integer())
}

#' @rdname collector
#' @export
col_double <- function() {
  collector("double")
}

#' @rdname collector
#' @export
parse_double <- function(x) {
  parse_vector(x, col_double())
}

#' @rdname collector
#' @export
col_euro_double <- function() {
  collector("euro_double")
}

#' @rdname collector
#' @export
parse_euro_double <- function(x) {
  parse_vector(x, col_euro_double())
}


#' @rdname collector
#' @export
col_numeric <- function() {
  collector("numeric")
}

#' @rdname collector
#' @export
parse_numeric <- function(x) {
  parse_vector(x, col_numeric())
}

#' @rdname collector
#' @export
col_logical <- function() {
  collector("logical")
}

#' @rdname collector
#' @export
parse_logical <- function(x) {
  parse_vector(x, col_logical())
}

#' @param levels Character vector providing set of allowed levels.
#' @param ordered Is it an ordered factor?
#' @rdname collector
#' @export
col_factor <- function(levels, ordered = FALSE) {
  collector("factor", levels = levels, ordered = ordered)
}

#' @rdname collector
#' @export
parse_factor <- function(x, levels, ordered = FALSE) {
  parse_vector(x, col_factor(levels, ordered))
}

#' @rdname collector
#' @export
col_skip <- function() {
  collector("skip")
}

# More complex ------------------------------------------------------------

#' Parse a character vector of dates or date times.
#'
#' @section Format specification:
#' \code{readr} uses a format specification similiar to \code{\link{strptime}}.
#' There are three types of element:
#'
#' \enumerate{
#'   \item Date components are specified with "\%" followed by a letter.
#'     For example "\%Y" matches a 4 digit year, "\%m", matches a 2 digit
#'     month and "\%d" matches a 2 digit day.
#'   \item Whitespace is any sequence of zero or more whitespace characters.
#'   \item Any other character is matched exactly.
#' }
#'
#' \code{parse_datetime} recognises the following format specifications:
#' \itemize{
#'   \item Year: "\%Y" (4 digits). "\%y" (2 digits); 00-69 -> 2000-2069,
#'     70-99 -> 1970-1999.
#'   \item Month: "\%m" (2 digits), "\%b" (abbreviated name in current
#'     locale), "\%B" (full name in current locale).
#'   \item Day: "\%d" (2 digits), "\%e" (optional leading space)
#'   \item Hour: "\%H"
#'   \item Minutes: "\%M"
#'   \item Seconds: "\%S" (integer seconds), "\%OS" (partial seconds)
#'   \item Time zone: "\%Z" (as name, e.g. "America/Chicago"), "\%z" (as
#'     offset from UTC, e.g. "+0800")
#'   \item AM/PM indicator: "\%p".
#'   \item Non-digits: "\%." skips one non-digit charcter, "\%*" skips any
#'     number of non-digits characters.
#'   \item Shortcuts: "\%D" = "\%m/\%d/\%y",  "\%F" = "\%Y-\%m-\%d",
#'       "\%R" = "\%H:\%M", "\%T" = "\%H:\%M:\%S",  "\%x" = "\%y/\%m/\%d".
#' }
#'
#' @section ISO8601 support:
#'
#' Currently, readr does not support all of ISO8601. Missing features:
#'
#' \itemize{
#' \item Week & weekday specifications, e.g. "2013-W05", "2013-W05-10"
#' \item Ordinal dates, e.g. "2013-095".
#' \item Using commas instead of a period for decimal separator
#' }
#'
#' The parser is also a little laxer than ISO8601:
#'
#' \itemize{
#' \item Dates and times can be separated with a space, not just T.
#' \item Mostly correct specifications like "2009-05-19 14:" and  "200912-01" work.
#' }
#'
#' @param x A character vector of dates to parse.
#' @param format A format specification, as described below. If omitted,
#'   parses dates according to the ISO8601 specification (with caveats,
#'   as described below).
#'
#'   Unlike \code{\link{strptime}}, the format specification must match
#'   the complete string.
#' @param tz Default tz. This is used both for input (if the time zone isn't
#'   present in individual strings), and for output (to control the default
#'   display). The default is to use "UTC", a time zone that does not use
#'   daylight savings time (DST) and hence is typically most useful for data.
#'   The absense of time zones makes it approximately 50x faster to generate
#'   UTC times than any other time zone.
#'
#'   Use \code{""} to use the system default time zone, but beware that this
#'   will not be reproducible across systems.
#'
#'   For a complete list of possible time zones, see \code{\link{OlsonNames}()}.
#'   Americans, note that "EST" is a Canadian time zone that does not have
#'   DST. It is \emph{not} Eastern Standard Time. It's better to use
#'   "US/Eastern", "US/Central" etc.
#' @return A \code{\link{POSIXct}} vector with \code{tzone} attribute set to
#'   \code{tz}. Elements that could not be parsed (or did not generate valid
#'   dates) will bes set to \code{NA}, and a warning message will inform
#'   you of the total number of failures.
#' @export
#' @examples
#' # Format strings --------------------------------------------------------
#' parse_datetime("01/02/2010", "%d/%m/%Y")
#' parse_datetime("01/02/2010", "%m/%d/%Y")
#' # Handle any separator
#' parse_datetime("01/02/2010", "%m%.%d%.%Y")
#'
#' # Dates look the same, but internally they use the number of days since
#' # 1970-01-01 instead of the number of seconds. This avoids a whole lot
#' # of troubles related to time zones, so use if you can.
#' parse_date("01/02/2010", "%d/%m/%Y")
#' parse_date("01/02/2010", "%m/%d/%Y")
#'
#' # You can parse timezones from strings (as listed in OlsonNames())
#' parse_datetime("2010/01/01 12:00 US/Central", "%Y/%m/%d %H:%M %Z")
#' # Or from offsets
#' parse_datetime("2010/01/01 12:00 -0600", "%Y/%m/%d %H:%M %z")
#'
#' # Use the tz parameter to control the default time zone
#' # (but note UTC is considerably faster than other options)
#' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Central")
#' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M", tz = "US/Eastern")
#'
#' # Unlike strptime, the format specification must match the complete
#' # string (ignoring leading and trailing whitespace). This avoids common
#' # errors:
#' strptime("01/02/2010", "%d/%m/%y")
#' parse_datetime("01/02/2010", "%d/%m/%y")
#'
#' # Failures -------------------------------------------------------------
#' parse_datetime("01/01/2010", "%d/%m/%Y")
#' x <- parse_datetime(c("01/ab/2010", "32/01/2010"), "%d/%m/%Y")
#' problems(x)
#'
#' # ISO8601 --------------------------------------------------------------
#' # With separators
#' parse_datetime("1979-10-14")
#' parse_datetime("1979-10-14T10")
#' parse_datetime("1979-10-14T10:11")
#' parse_datetime("1979-10-14T10:11:12")
#' parse_datetime("1979-10-14T10:11:12.12345")
#'
#' # Without separators
#' parse_datetime("19791014")
#' parse_datetime("19791014T101112")
#'
#' # Time zones
#' parse_datetime("1979-10-14T1010", tz = "US/Central")
#' parse_datetime("1979-10-14T1010-0500", tz = "US/Central")
#' parse_datetime("1979-10-14T1010Z", tz = "US/Central")
parse_datetime <- function(x, format = "", tz = "UTC") {
  parse_vector(x, col_datetime(format, tz))
}

#' @rdname parse_datetime
#' @export
col_datetime <- function(format = "", tz = "UTC") {
  collector("datetime", format = format, tz = tz)
}

#' @rdname parse_datetime
#' @export
parse_date <- function(x, format = "%Y-%m-%d") {
  parse_vector(x, col_date(format))
}

#' @rdname parse_datetime
#' @export
col_date <- function(format = "%Y-%m-%d") {
  collector("date", format = format)
}

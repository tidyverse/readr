collector <- function(type, ...) {
  structure(list(...), class = c(paste0("collector_", type), "collector"))
}

is.collector <- function(x) inherits(x, "collector")

collector_guess <- function(x, locale = default_locale()) {
  collectorGuess(x, locale)
}

#' @export
print.collector <- function(x, ...) {
  cat("<", class(x)[1], ">\n", sep = "")
}

collector_find <- function(name) {
  if (is.na(name)) {
    return(col_character())
  }

  get(paste0("col_", name), envir = asNamespace("readr"))()
}

#' Parse a character vector.
#'
#' @param x Character vector of elements to parse.
#' @param collector Column specification.
#' @inheritParams read_delim
#' @keywords internal
#' @export
#' @examples
#' x <- c("1", "2", "3", "NA")
#' parse_vector(x, col_integer())
#' parse_vector(x, col_double())
parse_vector <- function(x, collector, na = c("", "NA"), locale = default_locale()) {
  if (is.character(collector)) {
    collector <- collector_find(collector)
  }

  warn_problems(parse_vector_(x, collector, na = na, locale_ = locale))
}

#' Parse character vectors into typed columns.
#'
#' Use \code{parse_} if you have a character vector you want to parse. Use
#' \code{col_} in conjunction with a \code{read_} function to parse the
#' values as they're read in.
#'
#' @name collector
#' @param x Character vector of values to parse.
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @seealso \code{\link{parse_datetime}}, \code{\link{type_convert}} to
#'   automatically re-parse all character columns in a data frame.
#' @examples
#' parse_integer(c("1", "2", "3"))
#' parse_double(c("1", "2", "3.123"))
#' parse_factor(c("a", "b"), letters)
#' parse_number("$1,123,456.00")
#'
#' # Use locale to override default decimal and grouping marks
#' es_MX <- locale("es", decimal_mark = ",")
#' parse_number("$1.123.456,00", locale = es_MX)
#'
#' # Invalid values are replaced with missing values with a warning.
#' x <- c("1", "2", "3", "-")
#' parse_double(x)
#' # Or flag values as missing
#' parse_double(x, na = "-")
NULL

#' @rdname collector
#' @export
parse_guess <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, collector_guess(x, locale), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_character <- function() {
  collector("character")
}

#' @rdname collector
#' @export
parse_character <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, col_character(), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_integer <- function() {
  collector("integer")
}

#' @rdname collector
#' @export
parse_integer <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, col_integer(), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_double <- function() {
  collector("double")
}

#' @rdname collector
#' @export
parse_double <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, col_double(), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_euro_double <- function() {
  warning("Deprecated: please set locale")
  collector("double")
}

#' @rdname collector
#' @export
parse_euro_double <- function(x, na = c("", "NA")) {
  warning("Deprecated: please set locale")
  parse_vector(x, col_double(), na = na)
}


#' @rdname collector
#' @usage NULL
#' @export
col_numeric <- function() {
  warning("Deprecated: please use `col_number()`")
  collector("number")
}

#' @rdname collector
#' @usage NULL
#' @export
parse_numeric <- function(x, na = c("", "NA"), locale = default_locale()) {
  warning("Deprecated: please use `parse_number()`")
  parse_vector(x, col_number(), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_number <- function() {
  collector("number")
}

#' @rdname collector
#' @export
parse_number <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, col_number(), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_logical <- function() {
  collector("logical")
}

#' @rdname collector
#' @export
parse_logical <- function(x, na = c("", "NA"), locale = default_locale()) {
  parse_vector(x, col_logical(), na = na, locale = locale)
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
parse_factor <- function(x, levels, ordered = FALSE, na = c("", "NA"),
                         locale = default_locale()) {
  parse_vector(x, col_factor(levels, ordered), na = na, locale = locale)
}

#' @rdname collector
#' @export
col_skip <- function() {
  collector("skip")
}

#' @rdname collector
#' @export
col_guess <- function() {
  collector("guess")
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
#'   \item Non-digits: "\%." skips one non-digit character,
#'     "\%+" skips one or more non-digit characters,
#'     "\%*" skips any number of non-digits characters.
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
#'   as described below). Times are parsed like ISO8601 times, but also
#'   accept an optional am/pm specification.
#'
#'   Unlike \code{\link{strptime}}, the format specification must match
#'   the complete string.
#' @inheritParams read_delim
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
#' # Use the locale parameter to control the default time zone
#' # (but note UTC is considerably faster than other options)
#' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M",
#'   locale = locale(tz = "US/Central"))
#' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M",
#'   locale = locale(tz = "US/Eastern"))
#'
#' # Unlike strptime, the format specification must match the complete
#' # string (ignoring leading and trailing whitespace). This avoids common
#' # errors:
#' strptime("01/02/2010", "%d/%m/%y")
#' parse_datetime("01/02/2010", "%d/%m/%y")
#'
#' # Failures -------------------------------------------------------------
#' parse_datetime("01/01/2010", "%d/%m/%Y")
#' parse_datetime(c("01/ab/2010", "32/01/2010"), "%d/%m/%Y")
#'
#' # Locales --------------------------------------------------------------
#' # By default, readr expects English date/times, but that's easy to change'
#' parse_datetime("1 janvier 2015", "%d %B %Y", locale = locale("fr"))
#' parse_datetime("1 enero 2015", "%d %B %Y", locale = locale("es"))
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
#' us_central <- locale(tz = "US/Central")
#' parse_datetime("1979-10-14T1010", locale = us_central)
#' parse_datetime("1979-10-14T1010-0500", locale = us_central)
#' parse_datetime("1979-10-14T1010Z", locale = us_central)
#' # Your current time zone
#' parse_datetime("1979-10-14T1010", locale = locale(tz = ""))
parse_datetime <- function(x, format = "", locale = default_locale()) {
  parse_vector(x, col_datetime(format), locale = locale)
}

#' @rdname parse_datetime
#' @export
col_datetime <- function(format = "") {
  collector("datetime", format = format)
}

#' @rdname parse_datetime
#' @export
parse_date <- function(x, format = "%Y-%m-%d", locale = default_locale()) {
  parse_vector(x, col_date(format), locale = locale)
}

#' @rdname parse_datetime
#' @export
col_date <- function(format = NULL) {
  collector("date", format = format)
}

#' @rdname parse_datetime
#' @export
parse_time <- function(x, format = "", locale = default_locale()) {
  parse_vector(x, col_time(format), locale = locale)
}

#' @rdname parse_datetime
#' @export
col_time <- function(format = "") {
  collector("time", format = format)
}

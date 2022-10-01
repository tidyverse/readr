collector <- function(type, ...) {
  structure(list(...), class = c(paste0("collector_", type), "collector"))
}

is.collector <- function(x) inherits(x, "collector")

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
#' @family parsers
#' @param x Character vector of elements to parse.
#' @param collector Column specification.
#' @inheritParams read_delim
#' @inheritParams tokenizer_delim
#' @keywords internal
#' @export
#' @examples
#' x <- c("1", "2", "3", "NA")
#' parse_vector(x, col_integer())
#' parse_vector(x, col_double())
parse_vector <- function(x, collector, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  stopifnot(is.character(x))
  if (is.character(collector)) {
    collector <- collector_find(collector)
  }

  warn_problems(parse_vector_(x, collector, na = na, locale_ = locale, trim_ws = trim_ws))
}

#' Parse logicals, integers, and reals
#'
#' Use `parse_*()` if you have a character vector you want to parse. Use
#' `col_*()` in conjunction with a `read_*()` function to parse the
#' values as they're read in.
#'
#' @name parse_atomic
#' @aliases NULL
#' @param x Character vector of values to parse.
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @family parsers
#' @examples
#' parse_integer(c("1", "2", "3"))
#' parse_double(c("1", "2", "3.123"))
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

#' @rdname parse_atomic
#' @export
parse_logical <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_logical(), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_atomic
#' @export
parse_integer <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_integer(), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_atomic
#' @export
parse_double <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_double(), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_atomic
#' @export
parse_character <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_character(), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_atomic
#' @export
col_logical <- function() {
  collector("logical")
}

#' @rdname parse_atomic
#' @export
col_integer <- function() {
  collector("integer")
}

#' @rdname parse_atomic
#' @export
col_double <- function() {
  collector("double")
}

#' @rdname parse_atomic
#' @export
col_character <- function() {
  collector("character")
}

#' Skip a column
#'
#' Use this function to ignore a column when reading in a file.
#' To skip all columns not otherwise specified, use [cols_only()].
#'
#' @family parsers
#' @export
col_skip <- function() {
  collector("skip")
}

#' Parse numbers, flexibly
#'
#' This parses the first number it finds, dropping any non-numeric characters
#' before the first number and all characters after the first number. The
#' grouping mark specified by the locale is ignored inside the number.
#'
#' @inheritParams parse_atomic
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @return A numeric vector (double) of parsed numbers.
#' @family parsers
#' @export
#' @examples
#' ## These all return 1000
#' parse_number("$1,000") ## leading `$` and grouping character `,` ignored
#' parse_number("euro1,000") ## leading non-numeric euro ignored
#' parse_number("t1000t1000") ## only parses first number found
#'
#' parse_number("1,234.56")
#' ## explicit locale specifying European grouping and decimal marks
#' parse_number("1.234,56", locale = locale(decimal_mark = ",", grouping_mark = "."))
#' ## SI/ISO 31-0 standard spaces for number grouping
#' parse_number("1 234.56", locale = locale(decimal_mark = ".", grouping_mark = " "))
#'
#' ## Specifying strings for NAs
#' parse_number(c("1", "2", "3", "NA"))
#' parse_number(c("1", "2", "3", "NA", "Nothing"), na = c("NA", "Nothing"))
parse_number <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_number(), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_number
#' @export
col_number <- function() {
  collector("number")
}


#' Parse using the "best" type
#'
#' `parse_guess()` returns the parser vector; `guess_parser()`
#' returns the name of the parser. These functions use a number of heuristics
#' to determine which type of vector is "best". Generally they try to err of
#' the side of safety, as it's straightforward to override the parsing choice
#' if needed.
#'
#' @inheritParams parse_atomic
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @family parsers
#' @export
#' @examples
#' # Logical vectors
#' parse_guess(c("FALSE", "TRUE", "F", "T"))
#'
#' # Integers and doubles
#' parse_guess(c("1", "2", "3"))
#' parse_guess(c("1.6", "2.6", "3.4"))
#'
#' # Numbers containing grouping mark
#' guess_parser("1,234,566")
#' parse_guess("1,234,566")
#'
#' # ISO 8601 date times
#' guess_parser(c("2010-10-10"))
#' parse_guess(c("2010-10-10"))
parse_guess <- function(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE, guess_integer = FALSE) {
  parse_vector(x, guess_parser(x, locale, guess_integer = guess_integer, na = na), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_guess
#' @export
col_guess <- function() {
  collector("guess")
}

#' @rdname parse_guess
#' @param guess_integer If `TRUE`, guess integer types for whole numbers, if
#'   `FALSE` guess numeric type for all numbers.
#' @export
guess_parser <- function(x, locale = default_locale(), guess_integer = FALSE, na = c("", "NA")) {
  x[x %in% na] <- NA_character_

  stopifnot(is.locale(locale))

  collectorGuess(x, locale, guessInteger = guess_integer)
}

#' Parse factors
#'
#' `parse_factor()` is similar to [factor()], but generates a warning if
#' `levels` have been specified and some elements of `x` are not found in those
#' `levels`.
#'
#' @param levels Character vector of the allowed levels. When `levels = NULL`
#'   (the default), `levels` are discovered from the unique values of `x`, in
#'   the order in which they appear in `x`.
#' @param ordered Is it an ordered factor?
#' @param include_na If `TRUE` and `x` contains at least one `NA`, then `NA`
#'   is included in the levels of the constructed factor.
#'
#' @inheritParams parse_atomic
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @family parsers
#' @export
#' @examples
#' # discover the levels from the data
#' parse_factor(c("a", "b"))
#' parse_factor(c("a", "b", "-99"))
#' parse_factor(c("a", "b", "-99"), na = c("", "NA", "-99"))
#' parse_factor(c("a", "b", "-99"), na = c("", "NA", "-99"), include_na = FALSE)
#'
#' # provide the levels explicitly
#' parse_factor(c("a", "b"), levels = letters[1:5])
#'
#' x <- c("cat", "dog", "caw")
#' animals <- c("cat", "dog", "cow")
#'
#' # base::factor() silently converts elements that do not match any levels to
#' # NA
#' factor(x, levels = animals)
#'
#' # parse_factor() generates same factor as base::factor() but throws a warning
#' # and reports problems
#' parse_factor(x, levels = animals)
parse_factor <- function(x, levels = NULL, ordered = FALSE, na = c("", "NA"),
                         locale = default_locale(), include_na = TRUE, trim_ws = TRUE) {
  parse_vector(x, col_factor(levels, ordered, include_na), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_factor
#' @export
col_factor <- function(levels = NULL, ordered = FALSE, include_na = FALSE) {
  if (!(is.null(levels) || is.character(levels))) {
    stop(sprintf("`levels` must be `NULL` or a character vector:\n- `levels` is a '%s'", class(levels)), call. = FALSE)
  }
  collector("factor", levels = levels, ordered = ordered, include_na = include_na)
}

# More complex ------------------------------------------------------------

#' Parse date/times
#'
#' @section Format specification:
#' `readr` uses a format specification similar to [strptime()].
#' There are three types of element:
#'
#' 1. Date components are specified with "%" followed by a letter. For example
#'   "%Y" matches a 4 digit year, "%m", matches a 2 digit month and "%d" matches
#'   a 2 digit day. Month and day default to `1`, (i.e. Jan 1st) if not present,
#'   for example if only a year is given.
#' 2. Whitespace is any sequence of zero or more whitespace characters.
#' 3. Any other character is matched exactly.
#'
#' `parse_datetime()` recognises the following format specifications:
#'
#' * Year: "%Y" (4 digits). "%y" (2 digits); 00-69 -> 2000-2069, 70-99 ->
#'   1970-1999.
#' * Month: "%m" (2 digits), "%b" (abbreviated name in current locale), "%B"
#'   (full name in current locale).
#' * Day: "%d" (2 digits), "%e" (optional leading space), "%a" (abbreviated
#'   name in current locale).
#' * Hour: "%H" or "%I" or "%h", use I (and not H) with AM/PM, use h (and not H)
#'   if your times represent durations longer than one day.
#' * Minutes: "%M"
#' * Seconds: "%S" (integer seconds), "%OS" (partial seconds)
#' * Time zone: "%Z" (as name, e.g. "America/Chicago"), "%z" (as offset from
#'   UTC, e.g. "+0800")
#' * AM/PM indicator: "%p".
#' * Non-digits: "%." skips one non-digit character, "%+" skips one or more
#'   non-digit characters, "%*" skips any number of non-digits characters.
#' * Automatic parsers: "%AD" parses with a flexible YMD parser, "%AT" parses
#'   with a flexible HMS parser.
#' * Time since the Unix epoch: "%s" decimal seconds since the Unix epoch.
#' * Shortcuts: "%D" = "%m/%d/%y", "%F" = "%Y-%m-%d", "%R" = "%H:%M", "%T" =
#'   "%H:%M:%S", "%x" = "%y/%m/%d".
#'
#' @section ISO8601 support:
#'
#' Currently, readr does not support all of ISO8601. Missing features:
#'
#' * Week & weekday specifications, e.g. "2013-W05", "2013-W05-10".
#' * Ordinal dates, e.g. "2013-095".
#' * Using commas instead of a period for decimal separator.
#'
#' The parser is also a little laxer than ISO8601:
#'
#' * Dates and times can be separated with a space, not just T.
#' * Mostly correct specifications like "2009-05-19 14:" and "200912-01" work.
#'
#' @param x A character vector of dates to parse.
#' @param format A format specification, as described below. If set to "",
#'   date times are parsed as ISO8601, dates and times used the date and
#'   time formats specified in the [locale()].
#'
#'   Unlike [strptime()], the format specification must match
#'   the complete string.
#' @inheritParams read_delim
#' @inheritParams tokenizer_delim
#' @return A [POSIXct()] vector with `tzone` attribute set to
#'   `tz`. Elements that could not be parsed (or did not generate valid
#'   dates) will be set to `NA`, and a warning message will inform
#'   you of the total number of failures.
#' @family parsers
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
#'   locale = locale(tz = "US/Central")
#' )
#' parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M",
#'   locale = locale(tz = "US/Eastern")
#' )
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
parse_datetime <- function(x, format = "", na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_datetime(format), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_datetime
#' @export
parse_date <- function(x, format = "", na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_date(format), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_datetime
#' @export
parse_time <- function(x, format = "", na = c("", "NA"), locale = default_locale(), trim_ws = TRUE) {
  parse_vector(x, col_time(format), na = na, locale = locale, trim_ws = trim_ws)
}

#' @rdname parse_datetime
#' @export
col_datetime <- function(format = "") {
  collector("datetime", format = format)
}

#' @rdname parse_datetime
#' @export
col_date <- function(format = "") {
  collector("date", format = format)
}

#' @rdname parse_datetime
#' @export
col_time <- function(format = "") {
  collector("time", format = format)
}

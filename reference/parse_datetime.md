# Parse date/times

Parse date/times

## Usage

``` r
parse_datetime(
  x,
  format = "",
  na = c("", "NA"),
  locale = default_locale(),
  trim_ws = TRUE
)

parse_date(
  x,
  format = "",
  na = c("", "NA"),
  locale = default_locale(),
  trim_ws = TRUE
)

parse_time(
  x,
  format = "",
  na = c("", "NA"),
  locale = default_locale(),
  trim_ws = TRUE
)

col_datetime(format = "")

col_date(format = "")

col_time(format = "")
```

## Arguments

- x:

  A character vector of dates to parse.

- format:

  A format specification, as described below. If set to "", date times
  are parsed as ISO8601, dates and times used the date and time formats
  specified in the
  [`locale()`](https://readr.tidyverse.org/reference/locale.md).

  Unlike [`strptime()`](https://rdrr.io/r/base/strptime.html), the
  format specification must match the complete string.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

## Value

A
[`POSIXct()`](https://lubridate.tidyverse.org/reference/posix_utils.html)
vector with `tzone` attribute set to `tz`. Elements that could not be
parsed (or did not generate valid dates) will be set to `NA`, and a
warning message will inform you of the total number of failures.

## Format specification

`readr` uses a format specification similar to
[`strptime()`](https://rdrr.io/r/base/strptime.html). There are three
types of element:

1.  Date components are specified with "%" followed by a letter. For
    example "%Y" matches a 4 digit year, "%m", matches a 2 digit month
    and "%d" matches a 2 digit day. Month and day default to `1`, (i.e.
    Jan 1st) if not present, for example if only a year is given.

2.  Whitespace is any sequence of zero or more whitespace characters.

3.  Any other character is matched exactly.

`parse_datetime()` recognises the following format specifications:

- Year: "%Y" (4 digits). "%y" (2 digits); 00-69 -\> 2000-2069, 70-99 -\>
  1970-1999.

- Month: "%m" (2 digits), "%b" (abbreviated name in current locale),
  "%B" (full name in current locale).

- Day: "%d" (2 digits), "%e" (optional leading space), "%a" (abbreviated
  name in current locale).

- Hour: "%H" or "%I" or "%h", use I (and not H) with AM/PM, use h (and
  not H) if your times represent durations longer than one day.

- Minutes: "%M"

- Seconds: "%S" (integer seconds), "%OS" (partial seconds)

- Time zone: "%Z" (as name, e.g. "America/Chicago"), "%z" (as offset
  from UTC, e.g. "+0800")

- AM/PM indicator: "%p".

- Non-digits: "%." skips one non-digit character, "%+" skips one or more
  non-digit characters, "%\*" skips any number of non-digits characters.

- Automatic parsers: "%AD" parses with a flexible YMD parser, "%AT"
  parses with a flexible HMS parser.

- Time since the Unix epoch: "%s" decimal seconds since the Unix epoch.

- Shortcuts: "%D" = "%m/%d/%y", "%F" = "%Y-%m-%d", "%R" = "%H:%M", "%T"
  = "%H:%M:%S", "%x" = "%y/%m/%d".

## ISO8601 support

Currently, readr does not support all of ISO8601. Missing features:

- Week & weekday specifications, e.g. "2013-W05", "2013-W05-10".

- Ordinal dates, e.g. "2013-095".

- Using commas instead of a period for decimal separator.

The parser is also a little laxer than ISO8601:

- Dates and times can be separated with a space, not just T.

- Mostly correct specifications like "2009-05-19 14:" and "200912-01"
  work.

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/reference/spec.md),
[`parse_factor()`](https://readr.tidyverse.org/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/reference/parse_vector.md)

## Examples

``` r
# Format strings --------------------------------------------------------
parse_datetime("01/02/2010", "%d/%m/%Y")
#> [1] "2010-02-01 UTC"
parse_datetime("01/02/2010", "%m/%d/%Y")
#> [1] "2010-01-02 UTC"
# Handle any separator
parse_datetime("01/02/2010", "%m%.%d%.%Y")
#> [1] "2010-01-02 UTC"

# Dates look the same, but internally they use the number of days since
# 1970-01-01 instead of the number of seconds. This avoids a whole lot
# of troubles related to time zones, so use if you can.
parse_date("01/02/2010", "%d/%m/%Y")
#> [1] "2010-02-01"
parse_date("01/02/2010", "%m/%d/%Y")
#> [1] "2010-01-02"

# You can parse timezones from strings (as listed in OlsonNames())
parse_datetime("2010/01/01 12:00 US/Central", "%Y/%m/%d %H:%M %Z")
#> [1] "2010-01-01 18:00:00 UTC"
# Or from offsets
parse_datetime("2010/01/01 12:00 -0600", "%Y/%m/%d %H:%M %z")
#> [1] "2010-01-01 18:00:00 UTC"

# Use the locale parameter to control the default time zone
# (but note UTC is considerably faster than other options)
parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M",
  locale = locale(tz = "US/Central")
)
#> [1] "2010-01-01 12:00:00 CST"
parse_datetime("2010/01/01 12:00", "%Y/%m/%d %H:%M",
  locale = locale(tz = "US/Eastern")
)
#> [1] "2010-01-01 12:00:00 EST"

# Unlike strptime, the format specification must match the complete
# string (ignoring leading and trailing whitespace). This avoids common
# errors:
strptime("01/02/2010", "%d/%m/%y")
#> [1] "2020-02-01 UTC"
parse_datetime("01/02/2010", "%d/%m/%y")
#> Warning: 1 parsing failure.
#> row col           expected     actual
#>   1  -- date like %d/%m/%y 01/02/2010
#> [1] NA

# Failures -------------------------------------------------------------
parse_datetime("01/01/2010", "%d/%m/%Y")
#> [1] "2010-01-01 UTC"
parse_datetime(c("01/ab/2010", "32/01/2010"), "%d/%m/%Y")
#> Warning: 2 parsing failures.
#> row col           expected     actual
#>   1  -- date like %d/%m/%Y 01/ab/2010
#>   2  -- valid date         32/01/2010
#> [1] NA NA

# Locales --------------------------------------------------------------
# By default, readr expects English date/times, but that's easy to change'
parse_datetime("1 janvier 2015", "%d %B %Y", locale = locale("fr"))
#> [1] "2015-01-01 UTC"
parse_datetime("1 enero 2015", "%d %B %Y", locale = locale("es"))
#> [1] "2015-01-01 UTC"

# ISO8601 --------------------------------------------------------------
# With separators
parse_datetime("1979-10-14")
#> [1] "1979-10-14 UTC"
parse_datetime("1979-10-14T10")
#> [1] "1979-10-14 10:00:00 UTC"
parse_datetime("1979-10-14T10:11")
#> [1] "1979-10-14 10:11:00 UTC"
parse_datetime("1979-10-14T10:11:12")
#> [1] "1979-10-14 10:11:12 UTC"
parse_datetime("1979-10-14T10:11:12.12345")
#> [1] "1979-10-14 10:11:12 UTC"

# Without separators
parse_datetime("19791014")
#> [1] "1979-10-14 UTC"
parse_datetime("19791014T101112")
#> [1] "1979-10-14 10:11:12 UTC"

# Time zones
us_central <- locale(tz = "US/Central")
parse_datetime("1979-10-14T1010", locale = us_central)
#> [1] "1979-10-14 10:10:00 CDT"
parse_datetime("1979-10-14T1010-0500", locale = us_central)
#> [1] "1979-10-14 10:10:00 CDT"
parse_datetime("1979-10-14T1010Z", locale = us_central)
#> [1] "1979-10-14 05:10:00 CDT"
# Your current time zone
parse_datetime("1979-10-14T1010", locale = locale(tz = ""))
#> [1] "1979-10-14 10:10:00 UTC"
```

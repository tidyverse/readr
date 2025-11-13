# Parse numbers, flexibly

This parses the first number it finds, dropping any non-numeric
characters before the first number and all characters after the first
number. The grouping mark specified by the locale is ignored inside the
number.

## Usage

``` r
parse_number(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE)

col_number()
```

## Arguments

- x:

  Character vector of values to parse.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

## Value

A numeric vector (double) of parsed numbers.

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/dev/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_vector()`](https://readr.tidyverse.org/dev/reference/parse_vector.md)

## Examples

``` r
## These all return 1000
parse_number("$1,000") ## leading `$` and grouping character `,` ignored
#> [1] 1000
parse_number("euro1,000") ## leading non-numeric euro ignored
#> [1] 1000
parse_number("t1000t1000") ## only parses first number found
#> [1] 1000

parse_number("1,234.56")
#> [1] 1234.56
## explicit locale specifying European grouping and decimal marks
parse_number("1.234,56", locale = locale(decimal_mark = ",", grouping_mark = "."))
#> [1] 1234.56
## SI/ISO 31-0 standard spaces for number grouping
parse_number("1 234.56", locale = locale(decimal_mark = ".", grouping_mark = " "))
#> [1] 1234.56

## Specifying strings for NAs
parse_number(c("1", "2", "3", "NA"))
#> [1]  1  2  3 NA
parse_number(c("1", "2", "3", "NA", "Nothing"), na = c("NA", "Nothing"))
#> [1]  1  2  3 NA NA
```

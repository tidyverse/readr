# Parse using the "best" type

`parse_guess()` returns the parser vector; `guess_parser()` returns the
name of the parser. These functions use a number of heuristics to
determine which type of vector is "best". Generally they try to err of
the side of safety, as it's straightforward to override the parsing
choice if needed.

## Usage

``` r
parse_guess(
  x,
  na = c("", "NA"),
  locale = default_locale(),
  trim_ws = TRUE,
  guess_integer = FALSE
)

col_guess()

guess_parser(
  x,
  locale = default_locale(),
  guess_integer = FALSE,
  na = c("", "NA")
)
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
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- guess_integer:

  If `TRUE`, guess integer types for whole numbers, if `FALSE` guess
  numeric type for all numbers.

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/reference/parse_factor.md),
[`parse_logical()`](https://readr.tidyverse.org/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/reference/parse_vector.md)

## Examples

``` r
# Logical vectors
parse_guess(c("FALSE", "TRUE", "F", "T"))
#> [1] FALSE  TRUE FALSE  TRUE

# Integers and doubles
parse_guess(c("1", "2", "3"))
#> [1] 1 2 3
parse_guess(c("1.6", "2.6", "3.4"))
#> [1] 1.6 2.6 3.4

# Numbers containing grouping mark
guess_parser("1,234,566")
#> [1] "number"
parse_guess("1,234,566")
#> [1] 1234566

# ISO 8601 date times
guess_parser(c("2010-10-10"))
#> [1] "date"
parse_guess(c("2010-10-10"))
#> [1] "2010-10-10"
```

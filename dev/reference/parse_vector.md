# Parse a character vector.

Parse a character vector.

## Usage

``` r
parse_vector(
  x,
  collector,
  na = c("", "NA"),
  locale = default_locale(),
  trim_ws = TRUE
)
```

## Arguments

- x:

  Character vector of elements to parse.

- collector:

  Column specification.

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

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/dev/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)

## Examples

``` r
x <- c("1", "2", "3", "NA")
parse_vector(x, col_integer())
#> [1]  1  2  3 NA
parse_vector(x, col_double())
#> [1]  1  2  3 NA
```

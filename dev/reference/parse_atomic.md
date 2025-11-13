# Parse logicals, integers, and reals

Use `parse_*()` if you have a character vector you want to parse. Use
`col_*()` in conjunction with a `read_*()` function to parse the values
as they're read in.

## Usage

``` r
parse_logical(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE)

parse_integer(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE)

parse_double(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE)

parse_character(x, na = c("", "NA"), locale = default_locale(), trim_ws = TRUE)

col_logical()

col_integer()

col_double()

col_character()
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

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/dev/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md),
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/dev/reference/parse_vector.md)

## Examples

``` r
parse_integer(c("1", "2", "3"))
#> [1] 1 2 3
parse_double(c("1", "2", "3.123"))
#> [1] 1.000 2.000 3.123
parse_number("$1,123,456.00")
#> [1] 1123456

# Use locale to override default decimal and grouping marks
es_MX <- locale("es", decimal_mark = ",")
parse_number("$1.123.456,00", locale = es_MX)
#> [1] 1123456

# Invalid values are replaced with missing values with a warning.
x <- c("1", "2", "3", "-")
parse_double(x)
#> Warning: 1 parsing failure.
#> row col expected actual
#>   4  -- a double      -
#> [1]  1  2  3 NA
#> attr(,"problems")
#> # A tibble: 1 × 4
#>     row   col expected actual
#>   <int> <int> <chr>    <chr> 
#> 1     4    NA a double -     
# Or flag values as missing
parse_double(x, na = "-")
#> [1]  1  2  3 NA
```

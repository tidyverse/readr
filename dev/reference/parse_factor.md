# Parse factors

`parse_factor()` is similar to
[`factor()`](https://rdrr.io/r/base/factor.html), but generates a
warning if `levels` have been specified and some elements of `x` are not
found in those `levels`.

## Usage

``` r
parse_factor(
  x,
  levels = NULL,
  ordered = FALSE,
  na = c("", "NA"),
  locale = default_locale(),
  include_na = TRUE,
  trim_ws = TRUE
)

col_factor(levels = NULL, ordered = FALSE, include_na = FALSE)
```

## Arguments

- x:

  Character vector of values to parse.

- levels:

  Character vector of the allowed levels. When `levels = NULL` (the
  default), `levels` are discovered from the unique values of `x`, in
  the order in which they appear in `x`.

- ordered:

  Is it an ordered factor?

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

- include_na:

  If `TRUE` and `x` contains at least one `NA`, then `NA` is included in
  the levels of the constructed factor.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/dev/reference/cols.md),
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/dev/reference/parse_vector.md)

## Examples

``` r
# discover the levels from the data
parse_factor(c("a", "b"))
#> [1] a b
#> Levels: a b
parse_factor(c("a", "b", "-99"))
#> [1] a   b   -99
#> Levels: a b -99
parse_factor(c("a", "b", "-99"), na = c("", "NA", "-99"))
#> [1] a    b    <NA>
#> Levels: a b <NA>
parse_factor(c("a", "b", "-99"), na = c("", "NA", "-99"), include_na = FALSE)
#> [1] a    b    <NA>
#> Levels: a b

# provide the levels explicitly
parse_factor(c("a", "b"), levels = letters[1:5])
#> [1] a b
#> Levels: a b c d e

x <- c("cat", "dog", "caw")
animals <- c("cat", "dog", "cow")

# base::factor() silently converts elements that do not match any levels to
# NA
factor(x, levels = animals)
#> [1] cat  dog  <NA>
#> Levels: cat dog cow

# parse_factor() generates same factor as base::factor() but throws a warning
# and reports problems
parse_factor(x, levels = animals)
#> Warning: 1 parsing failure.
#> row col           expected actual
#>   3  -- value in level set    caw
#> [1] cat  dog  <NA>
#> attr(,"problems")
#> # A tibble: 1 × 4
#>     row   col expected           actual
#>   <int> <int> <chr>              <chr> 
#> 1     3    NA value in level set caw   
#> Levels: cat dog cow
```

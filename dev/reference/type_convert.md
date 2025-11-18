# Re-convert character columns in existing data frame

This is useful if you need to do some manual munging - you can read the
columns in as character, clean it up with (e.g.) regular expressions and
then let readr take another stab at parsing it. The name is a homage to
the base
[`utils::type.convert()`](https://rdrr.io/r/utils/type.convert.html).

## Usage

``` r
type_convert(
  df,
  col_types = NULL,
  na = c("", "NA"),
  trim_ws = TRUE,
  locale = default_locale(),
  guess_integer = FALSE
)
```

## Arguments

- df:

  A data frame.

- col_types:

  One of `NULL`, a
  [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md)
  specification, or a string. See
  [`vignette("readr")`](https://readr.tidyverse.org/dev/articles/readr.md)
  for more details.

  If `NULL`, column types will be imputed using all rows.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- guess_integer:

  If `TRUE`, guess integer types for whole numbers, if `FALSE` guess
  numeric type for all numbers.

## Note

`type_convert()` removes a 'spec' attribute, because it likely modifies
the column data types. (see
[`spec()`](https://readr.tidyverse.org/dev/reference/spec.md) for more
information about column specifications).

## Examples

``` r
df <- data.frame(
  x = as.character(runif(10)),
  y = as.character(sample(10)),
  stringsAsFactors = FALSE
)
str(df)
#> 'data.frame':    10 obs. of  2 variables:
#>  $ x: chr  "0.947763937758282" "0.542480408679694" "0.544603393413126" "0.278597153956071" ...
#>  $ y: chr  "2" "7" "10" "3" ...
str(type_convert(df))
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   x = col_double(),
#>   y = col_double()
#> )
#> 'data.frame':    10 obs. of  2 variables:
#>  $ x: num  0.948 0.542 0.545 0.279 0.447 ...
#>  $ y: num  2 7 10 3 6 4 8 1 9 5

df <- data.frame(x = c("NA", "10"), stringsAsFactors = FALSE)
str(type_convert(df))
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   x = col_double()
#> )
#> 'data.frame':    2 obs. of  1 variable:
#>  $ x: num  NA 10

# Type convert can be used to infer types from an entire dataset

# first read the data as character
data <- read_csv(readr_example("mtcars.csv"),
  col_types = list(.default = col_character())
)
str(data)
#> spc_tbl_ [32 × 11] (S3: spec_tbl_df/tbl_df/tbl/data.frame)
#>  $ mpg : chr [1:32] "21" "21" "22.8" "21.4" ...
#>  $ cyl : chr [1:32] "6" "6" "4" "6" ...
#>  $ disp: chr [1:32] "160" "160" "108" "258" ...
#>  $ hp  : chr [1:32] "110" "110" "93" "110" ...
#>  $ drat: chr [1:32] "3.9" "3.9" "3.85" "3.08" ...
#>  $ wt  : chr [1:32] "2.62" "2.875" "2.32" "3.215" ...
#>  $ qsec: chr [1:32] "16.46" "17.02" "18.61" "19.44" ...
#>  $ vs  : chr [1:32] "0" "0" "1" "1" ...
#>  $ am  : chr [1:32] "1" "1" "1" "0" ...
#>  $ gear: chr [1:32] "4" "4" "4" "3" ...
#>  $ carb: chr [1:32] "4" "4" "1" "1" ...
#>  - attr(*, "spec")=
#>   .. cols(
#>   ..   .default = col_character(),
#>   ..   mpg = col_character(),
#>   ..   cyl = col_character(),
#>   ..   disp = col_character(),
#>   ..   hp = col_character(),
#>   ..   drat = col_character(),
#>   ..   wt = col_character(),
#>   ..   qsec = col_character(),
#>   ..   vs = col_character(),
#>   ..   am = col_character(),
#>   ..   gear = col_character(),
#>   ..   carb = col_character()
#>   .. )
#>  - attr(*, "problems")=<externalptr> 
# Then convert it with type_convert
type_convert(data)
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   mpg = col_double(),
#>   cyl = col_double(),
#>   disp = col_double(),
#>   hp = col_double(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_double(),
#>   am = col_double(),
#>   gear = col_double(),
#>   carb = col_double()
#> )
#> # A tibble: 32 × 11
#>      mpg   cyl  disp    hp  drat    wt  qsec    vs    am  gear  carb
#>    <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl>
#>  1  21       6  160    110  3.9   2.62  16.5     0     1     4     4
#>  2  21       6  160    110  3.9   2.88  17.0     0     1     4     4
#>  3  22.8     4  108     93  3.85  2.32  18.6     1     1     4     1
#>  4  21.4     6  258    110  3.08  3.22  19.4     1     0     3     1
#>  5  18.7     8  360    175  3.15  3.44  17.0     0     0     3     2
#>  6  18.1     6  225    105  2.76  3.46  20.2     1     0     3     1
#>  7  14.3     8  360    245  3.21  3.57  15.8     0     0     3     4
#>  8  24.4     4  147.    62  3.69  3.19  20       1     0     4     2
#>  9  22.8     4  141.    95  3.92  3.15  22.9     1     0     4     2
#> 10  19.2     6  168.   123  3.92  3.44  18.3     1     0     4     4
#> # ℹ 22 more rows
```

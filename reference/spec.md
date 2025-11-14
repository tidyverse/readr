# Examine the column specifications for a data frame

`cols_condense()` takes a spec object and condenses its definition by
setting the default column type to the most frequent type and only
listing columns with a different type.

`spec()` extracts the full column specification from a tibble created by
readr.

## Usage

``` r
cols_condense(x)

spec(x)
```

## Arguments

- x:

  The data frame object to extract from

## Value

A col_spec object.

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/reference/col_skip.md),
[`cols()`](https://readr.tidyverse.org/reference/cols.md),
[`parse_datetime()`](https://readr.tidyverse.org/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/reference/parse_vector.md)

## Examples

``` r
df <- read_csv(readr_example("mtcars.csv"))
#> Rows: 32 Columns: 11
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
s <- spec(df)
s
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

cols_condense(s)
#> cols(
#>   .default = col_double()
#> )
```

# Temporarily change the active readr edition

`with_edition()` allows you to change the active edition of readr for a
given block of code. `local_edition()` allows you to change the active
edition of readr until the end of the current function or file.

## Usage

``` r
with_edition(edition, code)

local_edition(edition, env = parent.frame())
```

## Arguments

- edition:

  Should be a single integer, such as `1` or `2`.

- code:

  Code to run with the changed edition.

- env:

  Environment that controls scope of changes. For expert use only.

## Examples

``` r
with_edition(1, edition_get())
#> [1] 1
with_edition(2, edition_get())
#> [1] 2

# readr 1e and 2e behave differently when input rows have different number
# number of fields
with_edition(1, read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z")))
#> Warning: 1 parsing failure.
#> row col  expected    actual         file
#>   1  -- 3 columns 2 columns literal data
#> # A tibble: 2 × 3
#>       X     Y     Z
#>   <dbl> <dbl> <dbl>
#> 1     1     2    NA
#> 2     3     4     5
with_edition(2, read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z")))
#> Warning: The `file` argument of `vroom()` must use `I()` for literal data as of
#> vroom 1.5.0.
#>   
#>   # Bad:
#>   vroom("X,Y\n1.5,2.3\n")
#>   
#>   # Good:
#>   vroom(I("X,Y\n1.5,2.3\n"))
#> ℹ The deprecated feature was likely used in the readr package.
#>   Please report the issue at
#>   <https://github.com/tidyverse/readr/issues>.
#> Warning: One or more parsing issues, call `problems()` on your data frame for
#> details, e.g.:
#>   dat <- vroom(...)
#>   problems(dat)
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (1): X
#> num (1): Y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>       X     Y
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3    45

# local_edition() applies in a specific scope, for example, inside a function
read_csv_1e <- function(...) {
  local_edition(1)
  read_csv(...)
}
read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z"))      # 2e behaviour
#> Warning: One or more parsing issues, call `problems()` on your data frame for
#> details, e.g.:
#>   dat <- vroom(...)
#>   problems(dat)
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (1): X
#> num (1): Y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>       X     Y
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3    45
read_csv_1e("1,2\n3,4,5", col_names = c("X", "Y", "Z"))   # 1e behaviour
#> Warning: 1 parsing failure.
#> row col  expected    actual         file
#>   1  -- 3 columns 2 columns literal data
#> # A tibble: 2 × 3
#>       X     Y     Z
#>   <dbl> <dbl> <dbl>
#> 1     1     2    NA
#> 2     3     4     5
read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z"))      # 2e behaviour
#> Warning: One or more parsing issues, call `problems()` on your data frame for
#> details, e.g.:
#>   dat <- vroom(...)
#>   problems(dat)
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (1): X
#> num (1): Y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>       X     Y
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3    45
```

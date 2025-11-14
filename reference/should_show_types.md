# Determine whether column types should be shown

Wrapper around `getOption("readr.show_col_types")` that implements some
fall back logic if the option is unset. This returns:

- `TRUE` if the option is set to `TRUE`

- `FALSE` if the option is set to `FALSE`

- `FALSE` if the option is unset and we appear to be running tests

- `NULL` otherwise, in which case the caller determines whether to show
  column types based on context, e.g. whether `show_col_types` or actual
  `col_types` were explicitly specified

## Usage

``` r
should_show_types()
```

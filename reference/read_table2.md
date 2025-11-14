# Read whitespace-separated columns into a tibble

**\[deprecated\]**

This function is deprecated because we renamed it to
[`read_table()`](https://readr.tidyverse.org/reference/read_table.md)
and removed the old `read_table` function, which was too strict for most
cases and was analogous to just using
[`read_fwf()`](https://readr.tidyverse.org/reference/read_fwf.md).

## Usage

``` r
read_table2(
  file,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  comment = "",
  skip_empty_rows = TRUE
)
```

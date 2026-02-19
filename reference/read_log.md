# Read common/combined log file into a tibble

This is a fairly standard format for log files - it uses both quotes and
square brackets for quoting, and there may be literal quotes embedded in
a quoted string. The dash, "-", is used for missing values.

## Usage

``` r
read_log(
  file,
  col_names = FALSE,
  col_types = NULL,
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  show_col_types = should_show_types(),
  progress = show_progress()
)
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector).

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  uncompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote `.gz` files can
  also be automatically downloaded and decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, wrap the input with
  [`I()`](https://rdrr.io/r/base/AsIs.html).

  Using a value of
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
  will read from the system clipboard.

- col_names:

  Either `TRUE`, `FALSE` or a character vector of column names.

  If `TRUE`, the first row of the input will be used as the column
  names, and will not be included in the data frame. If `FALSE`, column
  names will be generated automatically: X1, X2, X3 etc.

  If `col_names` is a character vector, the values will be used as the
  names of the columns, and the first row of the input will be read into
  the first row of the output data frame.

  Missing (`NA`) column names will generate a warning, and be filled in
  with dummy names `...1`, `...2` etc. Duplicate column names will
  generate a warning and be made unique, see `name_repair` to control
  how this is done.

- col_types:

  One of `NULL`, a
  [`cols()`](https://readr.tidyverse.org/reference/cols.md)
  specification, or a string. See
  [`vignette("readr")`](https://readr.tidyverse.org/articles/readr.md)
  for more details.

  If `NULL`, all column types will be inferred from `guess_max` rows of
  the input, interspersed throughout the file. This is convenient (and
  fast), but not robust. If the guessed types are wrong, you'll need to
  increase `guess_max` or supply the correct types yourself.

  Column specifications created by
  [`list()`](https://rdrr.io/r/base/list.html) or
  [`cols()`](https://readr.tidyverse.org/reference/cols.md) must contain
  one column specification for each column. If you only want to read a
  subset of the columns, use
  [`cols_only()`](https://readr.tidyverse.org/reference/cols.md).

  Alternatively, you can use a compact string representation where each
  character represents one column:

  - c = character

  - i = integer

  - n = number

  - d = double

  - l = logical

  - f = factor

  - D = date

  - T = date time

  - t = time

  - ? = guess

  - \_ or - = skip

  By default, reading a file without a column specification will print a
  message showing what `readr` guessed they were. To remove this
  message, set `show_col_types = FALSE` or set
  `options(readr.show_col_types = FALSE)`.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- skip:

  Number of lines to skip before reading data.

- n_max:

  Maximum number of lines to read.

- show_col_types:

  If `FALSE`, do not show the guessed column types. If `TRUE` always
  show the column types, even if they are supplied. If `NULL` (the
  default) only show the column types if they are not explicitly
  supplied by the `col_types` argument.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The automatic
  progress bar can be disabled by setting option `readr.show_progress`
  to `FALSE`.

## Examples

``` r
read_log(readr_example("example.log"))
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   X1 = col_character(),
#>   X2 = col_logical(),
#>   X3 = col_character(),
#>   X4 = col_character(),
#>   X5 = col_character(),
#>   X6 = col_double(),
#>   X7 = col_double()
#> )
#> # A tibble: 2 × 7
#>   X1           X2    X3                   X4          X5       X6    X7
#>   <chr>        <lgl> <chr>                <chr>       <chr> <dbl> <dbl>
#> 1 172.21.13.45 NA    "Microsoft\\JohnDoe" 08/Apr/200… GET …   200  3401
#> 2 127.0.0.1    NA    "frank"              10/Oct/200… GET …   200  2326
```

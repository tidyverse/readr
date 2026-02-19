# Read a delimited file by chunks

Read a delimited file by chunks

## Usage

``` r
read_delim_chunked(
  file,
  callback,
  delim = NULL,
  chunk_size = 10000,
  quote = "\"",
  escape_backslash = FALSE,
  escape_double = TRUE,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  comment = "",
  trim_ws = FALSE,
  skip = 0,
  guess_max = chunk_size,
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
)

read_csv_chunked(
  file,
  callback,
  chunk_size = 10000,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  guess_max = chunk_size,
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
)

read_csv2_chunked(
  file,
  callback,
  chunk_size = 10000,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  guess_max = chunk_size,
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
)

read_tsv_chunked(
  file,
  callback,
  chunk_size = 10000,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  guess_max = chunk_size,
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
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

- callback:

  A callback function to call on each chunk

- delim:

  Single character used to separate fields within a record.

- chunk_size:

  The number of rows to include in each chunk

- quote:

  Single character used to quote strings.

- escape_backslash:

  Does the file use backslashes to escape special characters? This is
  more general than `escape_double` as backslashes can be used to escape
  the delimiter character, the quote character, or to add special
  characters like `\\n`.

- escape_double:

  Does the file escape quotes by doubling them? i.e. If this option is
  `TRUE`, the value `""""` represents a single quote, `\"`.

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

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- quoted_na:

  Should missing values inside quotes be treated as missing values (the
  default) or strings.

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- skip:

  Number of lines to skip before reading data.

- guess_max:

  Maximum number of lines to use for guessing column types. Will never
  use more than the number of lines read. See
  [`vignette("column-types", package = "readr")`](https://readr.tidyverse.org/articles/column-types.md)
  for more details.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The automatic
  progress bar can be disabled by setting option `readr.show_progress`
  to `FALSE`.

- show_col_types:

  If `FALSE`, do not show the guessed column types. If `TRUE` always
  show the column types, even if they are supplied. If `NULL` (the
  default) only show the column types if they are not explicitly
  supplied by the `col_types` argument.

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

## Details

The number of lines in `file` can exceed the maximum integer value in R
(~2 billion).

## See also

Other chunked:
[`callback`](https://readr.tidyverse.org/reference/callback.md),
[`read_lines_chunked()`](https://readr.tidyverse.org/reference/read_lines_chunked.md)

## Examples

``` r
# Cars with 3 gears
f <- function(x, pos) subset(x, gear == 3)
read_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
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
#> # A tibble: 15 × 11
#>      mpg   cyl  disp    hp  drat    wt  qsec    vs    am  gear  carb
#>    <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl>
#>  1  21.4     6  258    110  3.08  3.22  19.4     1     0     3     1
#>  2  18.7     8  360    175  3.15  3.44  17.0     0     0     3     2
#>  3  18.1     6  225    105  2.76  3.46  20.2     1     0     3     1
#>  4  14.3     8  360    245  3.21  3.57  15.8     0     0     3     4
#>  5  16.4     8  276.   180  3.07  4.07  17.4     0     0     3     3
#>  6  17.3     8  276.   180  3.07  3.73  17.6     0     0     3     3
#>  7  15.2     8  276.   180  3.07  3.78  18       0     0     3     3
#>  8  10.4     8  472    205  2.93  5.25  18.0     0     0     3     4
#>  9  10.4     8  460    215  3     5.42  17.8     0     0     3     4
#> 10  14.7     8  440    230  3.23  5.34  17.4     0     0     3     4
#> 11  21.5     4  120.    97  3.7   2.46  20.0     1     0     3     1
#> 12  15.5     8  318    150  2.76  3.52  16.9     0     0     3     2
#> 13  15.2     8  304    150  3.15  3.44  17.3     0     0     3     2
#> 14  13.3     8  350    245  3.73  3.84  15.4     0     0     3     4
#> 15  19.2     8  400    175  3.08  3.84  17.0     0     0     3     2
```

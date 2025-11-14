# Melt a delimited file by chunks

For certain non-rectangular data formats, it can be useful to parse the
data into a melted format where each row represents a single token.

## Usage

``` r
melt_delim_chunked(
  file,
  callback,
  chunk_size = 10000,
  delim,
  quote = "\"",
  escape_backslash = FALSE,
  escape_double = TRUE,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  comment = "",
  trim_ws = FALSE,
  skip = 0,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_csv_chunked(
  file,
  callback,
  chunk_size = 10000,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_csv2_chunked(
  file,
  callback,
  chunk_size = 10000,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_tsv_chunked(
  file,
  callback,
  chunk_size = 10000,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  progress = show_progress(),
  skip_empty_rows = FALSE
)
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector).

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  uncompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote gz files can also
  be automatically downloaded and decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, the input must be either wrapped with
  [`I()`](https://rdrr.io/r/base/AsIs.html), be a string containing at
  least one new line, or be a vector containing at least one string with
  a new line.

  Using a value of
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
  will read from the system clipboard.

- callback:

  A callback function to call on each chunk

- chunk_size:

  The number of rows to include in each chunk

- delim:

  Single character used to separate fields within a record.

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

  **\[deprecated\]** Should missing values inside quotes be treated as
  missing values (the default) or strings. This parameter is soft
  deprecated as of readr 2.0.0.

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- skip:

  Number of lines to skip before reading data. If `comment` is supplied
  any commented lines are ignored *after* skipping.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The automatic
  progress bar can be disabled by setting option `readr.show_progress`
  to `FALSE`.

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

## Details

`melt_delim_chunked()` and the specialisations `melt_csv_chunked()`,
`melt_csv2_chunked()` and `melt_tsv_chunked()` read files by a chunk of
rows at a time, executing a given function on one chunk before reading
the next.

## See also

Other chunked:
[`callback`](https://readr.tidyverse.org/reference/callback.md),
[`read_delim_chunked()`](https://readr.tidyverse.org/reference/read_delim_chunked.md),
[`read_lines_chunked()`](https://readr.tidyverse.org/reference/read_lines_chunked.md)

## Examples

``` r
# Cars with 3 gears
f <- function(x, pos) subset(x, data_type == "integer")
melt_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
#> # A tibble: 218 × 4
#>      row   col data_type value
#>    <dbl> <dbl> <chr>     <chr>
#>  1     2     1 integer   21   
#>  2     2     2 integer   6    
#>  3     2     3 integer   160  
#>  4     2     4 integer   110  
#>  5     2     8 integer   0    
#>  6     2     9 integer   1    
#>  7     2    10 integer   4    
#>  8     2    11 integer   4    
#>  9     3     1 integer   21   
#> 10     3     2 integer   6    
#> # ℹ 208 more rows
```

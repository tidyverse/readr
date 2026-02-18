# Generate a column specification

When printed, only the first 20 columns are printed by default. To
override, set `options(readr.num_columns)` can be used to modify this (a
value of 0 turns off printing).

## Usage

``` r
spec_delim(
  file,
  delim = NULL,
  quote = "\"",
  escape_backslash = FALSE,
  escape_double = TRUE,
  col_names = TRUE,
  col_types = list(),
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = deprecated(),
  comment = "",
  trim_ws = FALSE,
  skip = 0,
  n_max = 0,
  guess_max = 1000,
  name_repair = "unique",
  num_threads = readr_threads(),
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

spec_csv(
  file,
  col_names = TRUE,
  col_types = list(),
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = deprecated(),
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = 0,
  guess_max = 1000,
  name_repair = "unique",
  num_threads = readr_threads(),
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

spec_csv2(
  file,
  col_names = TRUE,
  col_types = list(),
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = deprecated(),
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = 0,
  guess_max = 1000,
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

spec_tsv(
  file,
  col_names = TRUE,
  col_types = list(),
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = deprecated(),
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = 0,
  guess_max = 1000,
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

spec_table(
  file,
  col_names = TRUE,
  col_types = list(),
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = 0,
  guess_max = 1000,
  progress = show_progress(),
  comment = "",
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
)
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector). `file` can also be a character vector
  containing multiple filepaths or a list containing multiple
  connections.

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  decompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote compressed files
  (`.gz`, `.bz2`, `.xz`, `.zip`) will be automatically downloaded and
  decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, wrap the input with
  [`I()`](https://rdrr.io/r/base/AsIs.html).

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
  [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md)
  specification, or a string. See
  [`vignette("readr")`](https://readr.tidyverse.org/dev/articles/readr.md)
  for more details.

  If `NULL`, all column types will be inferred from `guess_max` rows of
  the input, interspersed throughout the file. This is convenient (and
  fast), but not robust. If the guessed types are wrong, you'll need to
  increase `guess_max` or supply the correct types yourself.

  Column specifications created by
  [`list()`](https://rdrr.io/r/base/list.html) or
  [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md) must
  contain one column specification for each column. If you only want to
  read a subset of the columns, use
  [`cols_only()`](https://readr.tidyverse.org/dev/reference/cols.md).

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

- col_select:

  Columns to include in the results. You can use the same mini-language
  as
  [`dplyr::select()`](https://dplyr.tidyverse.org/reference/select.html)
  to refer to the columns by name. Use
  [`c()`](https://rdrr.io/r/base/c.html) to use more than one selection
  expression. Although this usage is less common, `col_select` also
  accepts a numeric column index. See
  [`?tidyselect::language`](https://tidyselect.r-lib.org/reference/language.html)
  for full details on the selection language.

- id:

  The name of a column in which to store the file path. This is useful
  when reading multiple input files and there is data in the file paths,
  such as the data collection date. If `NULL` (the default) no extra
  column is created.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- quoted_na:

  **\[deprecated\]** Should missing values inside quotes be treated as
  missing values (the default) or strings. This argument is deprecated
  and only works when using the legacy first edition parser. See
  [`with_edition()`](https://readr.tidyverse.org/dev/reference/with_edition.md)
  for more.

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- skip:

  Number of lines to skip before reading data. If `comment` is supplied
  any commented lines are ignored *after* skipping.

- n_max:

  Maximum number of lines to read.

- guess_max:

  Maximum number of lines to use for guessing column types. Will never
  use more than the number of lines read. See
  [`vignette("column-types", package = "readr")`](https://readr.tidyverse.org/dev/articles/column-types.md)
  for more details.

- name_repair:

  Handling of column names. The default behaviour is to ensure column
  names are `"unique"`. Various repair strategies are supported:

  - `"minimal"`: No name repair or checks, beyond basic existence of
    names.

  - `"unique"` (default value): Make sure names are unique and not
    empty.

  - `"check_unique"`: No name repair, but check they are `unique`.

  - `"unique_quiet"`: Repair with the `unique` strategy, quietly.

  - `"universal"`: Make the names `unique` and syntactic.

  - `"universal_quiet"`: Repair with the `universal` strategy, quietly.

  - A function: Apply custom name repair (e.g.,
    `name_repair = make.names` for names in the style of base R).

  - A purrr-style anonymous function, see
    [`rlang::as_function()`](https://rlang.r-lib.org/reference/as_function.html).

  This argument is passed on as `repair` to
  [`vctrs::vec_as_names()`](https://vctrs.r-lib.org/reference/vec_as_names.html).
  See there for more details on these terms and the strategies used to
  enforce them.

- num_threads:

  The number of processing threads to use for initial parsing and lazy
  reading of data. If your data contains newlines within fields the
  parser should automatically detect this and fall back to using one
  thread only. However if you know your file has newlines within quoted
  fields it is safest to set `num_threads = 1` explicitly.

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

- lazy:

  Read values lazily? By default, this is `FALSE`, because there are
  special considerations when reading a file lazily that have tripped up
  some users. Specifically, things get tricky when reading and then
  writing back into the same file. But, in general, lazy reading
  (`lazy = TRUE`) has many benefits, especially for interactive use and
  when your downstream work only involves a subset of the rows or
  columns.

  Learn more in
  [`should_read_lazy()`](https://readr.tidyverse.org/dev/reference/should_read_lazy.md)
  and in the documentation for the `altrep` argument of
  [`vroom::vroom()`](https://vroom.tidyverse.org/reference/vroom.html).

## Value

The `col_spec` generated for the file.

## Examples

``` r
# Input sources -------------------------------------------------------------
# Retrieve specs from a path
spec_csv(system.file("extdata/mtcars.csv", package = "readr"))
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
spec_csv(system.file("extdata/mtcars.csv.zip", package = "readr"))
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

# Or directly from a string (must contain a newline)
spec_csv(I("x,y\n1,2\n3,4"))
#> cols(
#>   x = col_double(),
#>   y = col_double()
#> )

# Column types --------------------------------------------------------------
# By default, readr guesses the columns types, looking at 1000 rows
# throughout the file.
# You can specify the number of rows used with guess_max.
spec_csv(system.file("extdata/mtcars.csv", package = "readr"), guess_max = 20)
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
```

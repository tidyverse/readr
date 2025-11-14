# Read a fixed width file into a tibble

A fixed width file can be a very compact representation of numeric data.
It's also very fast to parse, because every field is in the same place
in every line. Unfortunately, it's painful to parse because you need to
describe the length of every field. Readr aims to make it as easy as
possible by providing a number of different ways to describe the field
structure.

- `fwf_empty()` - Guesses based on the positions of empty columns.

- `fwf_widths()` - Supply the widths of the columns.

- `fwf_positions()` - Supply paired vectors of start and end positions.

- `fwf_cols()` - Supply named arguments of paired start and end
  positions or column widths.

## Usage

``` r
read_fwf(
  file,
  col_positions = fwf_empty(file, skip, n = guess_max),
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  lazy = should_read_lazy(),
  skip_empty_rows = TRUE
)

fwf_empty(
  file,
  skip = 0,
  skip_empty_rows = FALSE,
  col_names = NULL,
  comment = "",
  n = 100L
)

fwf_widths(widths, col_names = NULL)

fwf_positions(start, end = NULL, col_names = NULL)

fwf_cols(...)
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

- col_positions:

  Column positions, as created by `fwf_empty()`, `fwf_widths()` or
  `fwf_positions()`. To read in only selected fields, use
  `fwf_positions()`. If the width of the last column is variable (a
  ragged fwf file), supply the last end position as NA.

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
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- skip:

  Number of lines to skip before reading data.

- n_max:

  Maximum number of lines to read.

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

- show_col_types:

  If `FALSE`, do not show the guessed column types. If `TRUE` always
  show the column types, even if they are supplied. If `NULL` (the
  default) only show the column types if they are not explicitly
  supplied by the `col_types` argument.

- lazy:

  Read values lazily? By default, this is `FALSE`, because there are
  special considerations when reading a file lazily that have tripped up
  some users. Specifically, things get tricky when reading and then
  writing back into the same file. But, in general, lazy reading
  (`lazy = TRUE`) has many benefits, especially for interactive use and
  when your downstream work only involves a subset of the rows or
  columns.

  Learn more in
  [`should_read_lazy()`](https://readr.tidyverse.org/reference/should_read_lazy.md)
  and in the documentation for the `altrep` argument of
  [`vroom::vroom()`](https://vroom.r-lib.org/reference/vroom.html).

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

- col_names:

  Either NULL, or a character vector column names.

- n:

  Number of lines the tokenizer will read to determine file structure.
  By default it is set to 100.

- widths:

  Width of each field. Use NA as width of last field when reading a
  ragged fwf file.

- start, end:

  Starting and ending (inclusive) positions of each field. Use NA as
  last end field when reading a ragged fwf file.

- ...:

  If the first element is a data frame, then it must have all numeric
  columns and either one or two rows. The column names are the variable
  names. The column values are the variable widths if a length one
  vector, and if length two, variable start and end positions. The
  elements of `...` are used to construct a data frame with or or two
  rows as above.

## Second edition changes

Comments are no longer looked for anywhere in the file. They are now
only ignored at the start of a line.

## See also

[`read_table()`](https://readr.tidyverse.org/reference/read_table.md) to
read fixed width files where each column is separated by whitespace.

## Examples

``` r
fwf_sample <- readr_example("fwf-sample.txt")
writeLines(read_lines(fwf_sample))
#> John Smith          WA        418-Y11-4111
#> Mary Hartford       CA        319-Z19-4341
#> Evan Nolan          IL        219-532-c301

# You can specify column positions in several ways:
# 1. Guess based on position of empty columns
read_fwf(fwf_sample, fwf_empty(fwf_sample, col_names = c("first", "last", "state", "ssn")))
#> Rows: 3 Columns: 4
#> ── Column specification ───────────────────────────────────────────────
#> 
#> chr (4): first, last, state, ssn
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 3 × 4
#>   first last     state ssn         
#>   <chr> <chr>    <chr> <chr>       
#> 1 John  Smith    WA    418-Y11-4111
#> 2 Mary  Hartford CA    319-Z19-4341
#> 3 Evan  Nolan    IL    219-532-c301
# 2. A vector of field widths
read_fwf(fwf_sample, fwf_widths(c(20, 10, 12), c("name", "state", "ssn")))
#> Rows: 3 Columns: 3
#> ── Column specification ───────────────────────────────────────────────
#> 
#> chr (3): name, state, ssn
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 3 × 3
#>   name          state ssn         
#>   <chr>         <chr> <chr>       
#> 1 John Smith    WA    418-Y11-4111
#> 2 Mary Hartford CA    319-Z19-4341
#> 3 Evan Nolan    IL    219-532-c301
# 3. Paired vectors of start and end positions
read_fwf(fwf_sample, fwf_positions(c(1, 30), c(20, 42), c("name", "ssn")))
#> Rows: 3 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> 
#> chr (2): name, ssn
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 3 × 2
#>   name          ssn         
#>   <chr>         <chr>       
#> 1 John Smith    418-Y11-4111
#> 2 Mary Hartford 319-Z19-4341
#> 3 Evan Nolan    219-532-c301
# 4. Named arguments with start and end positions
read_fwf(fwf_sample, fwf_cols(name = c(1, 20), ssn = c(30, 42)))
#> Rows: 3 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> 
#> chr (2): name, ssn
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 3 × 2
#>   name          ssn         
#>   <chr>         <chr>       
#> 1 John Smith    418-Y11-4111
#> 2 Mary Hartford 319-Z19-4341
#> 3 Evan Nolan    219-532-c301
# 5. Named arguments with column widths
read_fwf(fwf_sample, fwf_cols(name = 20, state = 10, ssn = 12))
#> Rows: 3 Columns: 3
#> ── Column specification ───────────────────────────────────────────────
#> 
#> chr (3): name, state, ssn
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 3 × 3
#>   name          state ssn         
#>   <chr>         <chr> <chr>       
#> 1 John Smith    WA    418-Y11-4111
#> 2 Mary Hartford CA    319-Z19-4341
#> 3 Evan Nolan    IL    219-532-c301
```

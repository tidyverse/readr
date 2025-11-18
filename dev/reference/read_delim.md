# Read a delimited file (including CSV and TSV) into a tibble

`read_csv()` and `read_tsv()` are special cases of the more general
`read_delim()`. They're useful for reading the most common types of flat
file data, comma separated values and tab separated values,
respectively. `read_csv2()` uses `;` for the field separator and `,` for
the decimal point. This format is common in some European countries.

## Usage

``` r
read_delim(
  file,
  delim = NULL,
  quote = "\"",
  escape_backslash = FALSE,
  escape_double = TRUE,
  col_names = TRUE,
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  comment = "",
  trim_ws = FALSE,
  skip = 0,
  n_max = Inf,
  guess_max = min(1000, n_max),
  name_repair = "unique",
  num_threads = readr_threads(),
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

read_csv(
  file,
  col_names = TRUE,
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  guess_max = min(1000, n_max),
  name_repair = "unique",
  num_threads = readr_threads(),
  progress = show_progress(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

read_csv2(
  file,
  col_names = TRUE,
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  guess_max = min(1000, n_max),
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
)

read_tsv(
  file,
  col_names = TRUE,
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  guess_max = min(1000, n_max),
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE,
  lazy = should_read_lazy()
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
  [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  will read from the system clipboard.

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
  [`vroom::vroom()`](https://vroom.r-lib.org/reference/vroom.html).

## Value

A
[`tibble::tibble()`](https://tibble.tidyverse.org/reference/tibble.html).
If there are parsing problems, a warning will alert you. You can
retrieve the full details by calling
[`problems()`](https://readr.tidyverse.org/dev/reference/problems.md) on
your dataset.

## Examples

``` r
# Input sources -------------------------------------------------------------
# Read from a path
read_csv(readr_example("mtcars.csv"))
#> Rows: 32 Columns: 11
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
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
read_csv(readr_example("mtcars.csv.zip"))
#> Rows: 32 Columns: 11
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
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
read_csv(readr_example("mtcars.csv.bz2"))
#> Rows: 32 Columns: 11
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
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
if (FALSE) { # \dontrun{
# Including remote paths
read_csv("https://github.com/tidyverse/readr/raw/main/inst/extdata/mtcars.csv")
} # }

# Read from multiple file paths at once
continents <- c("africa", "americas", "asia", "europe", "oceania")
filepaths <- vapply(
  paste0("mini-gapminder-", continents, ".csv"),
  FUN = readr_example,
  FUN.VALUE = character(1)
)
read_csv(filepaths, id = "file")
#> Rows: 26 Columns: 6
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> chr (1): country
#> dbl (4): year, lifeExp, pop, gdpPercap
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 26 × 6
#>    file                          country  year lifeExp    pop gdpPercap
#>    <chr>                         <chr>   <dbl>   <dbl>  <dbl>     <dbl>
#>  1 /home/runner/work/_temp/Libr… Algeria  1952    43.1 9.28e6     2449.
#>  2 /home/runner/work/_temp/Libr… Angola   1952    30.0 4.23e6     3521.
#>  3 /home/runner/work/_temp/Libr… Benin    1952    38.2 1.74e6     1063.
#>  4 /home/runner/work/_temp/Libr… Botswa…  1952    47.6 4.42e5      851.
#>  5 /home/runner/work/_temp/Libr… Burkin…  1952    32.0 4.47e6      543.
#>  6 /home/runner/work/_temp/Libr… Burundi  1952    39.0 2.45e6      339.
#>  7 /home/runner/work/_temp/Libr… Argent…  1952    62.5 1.79e7     5911.
#>  8 /home/runner/work/_temp/Libr… Bolivia  1952    40.4 2.88e6     2677.
#>  9 /home/runner/work/_temp/Libr… Brazil   1952    50.9 5.66e7     2109.
#> 10 /home/runner/work/_temp/Libr… Canada   1952    68.8 1.48e7    11367.
#> # ℹ 16 more rows

# Or directly from a string with `I()`
read_csv(I("x,y\n1,2\n3,4"))
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): x, y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>       x     y
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3     4

# Column selection-----------------------------------------------------------
# Pass column names or indexes directly to select them
read_csv(readr_example("chickens.csv"), col_select = c(chicken, eggs_laid))
#> Rows: 5 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> chr (1): chicken
#> dbl (1): eggs_laid
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 5 × 2
#>   chicken                 eggs_laid
#>   <chr>                       <dbl>
#> 1 Foghorn Leghorn                 0
#> 2 Chicken Little                  3
#> 3 Ginger                         12
#> 4 Camilla the Chicken             7
#> 5 Ernie The Giant Chicken         0
read_csv(readr_example("chickens.csv"), col_select = c(1, 3:4))
#> Rows: 5 Columns: 3
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> chr (2): chicken, motto
#> dbl (1): eggs_laid
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 5 × 3
#>   chicken                 eggs_laid motto                              
#>   <chr>                       <dbl> <chr>                              
#> 1 Foghorn Leghorn                 0 That's a joke, ah say, that's a jo…
#> 2 Chicken Little                  3 The sky is falling!                
#> 3 Ginger                         12 Listen. We'll either die free chic…
#> 4 Camilla the Chicken             7 Bawk, buck, ba-gawk.               
#> 5 Ernie The Giant Chicken         0 Put Captain Solo in the cargo hold.

# Or use the selection helpers
read_csv(
  readr_example("chickens.csv"),
  col_select = c(starts_with("c"), last_col())
)
#> Rows: 5 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> chr (2): chicken, motto
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 5 × 2
#>   chicken                 motto                                        
#>   <chr>                   <chr>                                        
#> 1 Foghorn Leghorn         That's a joke, ah say, that's a joke, son.   
#> 2 Chicken Little          The sky is falling!                          
#> 3 Ginger                  Listen. We'll either die free chickens or we…
#> 4 Camilla the Chicken     Bawk, buck, ba-gawk.                         
#> 5 Ernie The Giant Chicken Put Captain Solo in the cargo hold.          

# You can also rename specific columns
read_csv(
  readr_example("chickens.csv"),
  col_select = c(egg_yield = eggs_laid, everything())
)
#> Rows: 5 Columns: 4
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> chr (3): chicken, sex, motto
#> dbl (1): eggs_laid
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 5 × 4
#>   egg_yield chicken                 sex     motto                      
#>       <dbl> <chr>                   <chr>   <chr>                      
#> 1         0 Foghorn Leghorn         rooster That's a joke, ah say, tha…
#> 2         3 Chicken Little          hen     The sky is falling!        
#> 3        12 Ginger                  hen     Listen. We'll either die f…
#> 4         7 Camilla the Chicken     hen     Bawk, buck, ba-gawk.       
#> 5         0 Ernie The Giant Chicken rooster Put Captain Solo in the ca…

# Column types --------------------------------------------------------------
# By default, readr guesses the columns types, looking at `guess_max` rows.
# You can override with a compact specification:
read_csv(I("x,y\n1,2\n3,4"), col_types = "dc")
#> # A tibble: 2 × 2
#>       x y    
#>   <dbl> <chr>
#> 1     1 2    
#> 2     3 4    

# Or with a list of column types:
read_csv(I("x,y\n1,2\n3,4"), col_types = list(col_double(), col_character()))
#> # A tibble: 2 × 2
#>       x y    
#>   <dbl> <chr>
#> 1     1 2    
#> 2     3 4    

# If there are parsing problems, you get a warning, and can extract
# more details with problems()
y <- read_csv(I("x\n1\n2\nb"), col_types = list(col_double()))
#> Warning: One or more parsing issues, call `problems()` on your data frame for
#> details, e.g.:
#>   dat <- vroom(...)
#>   problems(dat)
y
#> # A tibble: 3 × 1
#>       x
#>   <dbl>
#> 1     1
#> 2     2
#> 3    NA
problems(y)
#> # A tibble: 1 × 5
#>     row   col expected actual file                            
#>   <int> <int> <chr>    <chr>  <chr>                           
#> 1     4     1 a double b      /tmp/RtmpqF7Dlu/file18ca17773d94

# Column names --------------------------------------------------------------
# By default, readr duplicate name repair is noisy
read_csv(I("x,x\n1,2\n3,4"))
#> New names:
#> • `x` -> `x...1`
#> • `x` -> `x...2`
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): x...1, x...2
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>   x...1 x...2
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3     4

# Same default repair strategy, but quiet
read_csv(I("x,x\n1,2\n3,4"), name_repair = "unique_quiet")
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): x...1, x...2
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>   x...1 x...2
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3     4

# There's also a global option that controls verbosity of name repair
withr::with_options(
  list(rlib_name_repair_verbosity = "quiet"),
  read_csv(I("x,x\n1,2\n3,4"))
)
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): x...1, x...2
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>   x...1 x...2
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3     4

# Or use "minimal" to turn off name repair
read_csv(I("x,x\n1,2\n3,4"), name_repair = "minimal")
#> Rows: 2 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): x, x
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 2 × 2
#>       x     x
#>   <dbl> <dbl>
#> 1     1     2
#> 2     3     4

# File types ----------------------------------------------------------------
read_csv(I("a,b\n1.0,2.0"))
#> Rows: 1 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl (2): a, b
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 1 × 2
#>       a     b
#>   <dbl> <dbl>
#> 1     1     2
read_csv2(I("a;b\n1,0;2,0"))
#> ℹ Using "','" as decimal and "'.'" as grouping mark. Use `read_delim()` for more control.
#> Rows: 1 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ";"
#> dbl (2): a, b
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 1 × 2
#>       a     b
#>   <dbl> <dbl>
#> 1     1     2
read_tsv(I("a\tb\n1.0\t2.0"))
#> Rows: 1 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: "\t"
#> dbl (2): a, b
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 1 × 2
#>       a     b
#>   <dbl> <dbl>
#> 1     1     2
read_delim(I("a|b\n1.0|2.0"), delim = "|")
#> Rows: 1 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: "|"
#> dbl (2): a, b
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 1 × 2
#>       a     b
#>   <dbl> <dbl>
#> 1     1     2
```

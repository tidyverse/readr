# Changelog

## readr (development version)

- The `quote_escape` parameter has been removed from
  [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_excel_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_excel_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_tsv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`format_delim()`](https://readr.tidyverse.org/dev/reference/format_delim.md),
  [`format_csv()`](https://readr.tidyverse.org/dev/reference/format_delim.md),
  [`format_csv2()`](https://readr.tidyverse.org/dev/reference/format_delim.md),
  and
  [`format_tsv()`](https://readr.tidyverse.org/dev/reference/format_delim.md).
  This parameter was deprecated in readr 2.0.0 (2021-07-20) in favor of
  the `escape` parameter. Use `escape` instead.

- The `path` parameter has been removed from
  [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_excel_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_excel_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_tsv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md),
  [`write_file()`](https://readr.tidyverse.org/dev/reference/read_file.md),
  and
  [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md).
  This parameter was deprecated in readr 1.4.0 (2020-01-31) in favor of
  the `file` parameter. Use `file` instead.

- `melt_csv()`, `melt_csv2()`, `melt_delim()`, `melt_tsv()`,
  `melt_fwf()`, `melt_table()`, `melt_table2()`, and all
  `melt_*_chunked()` variants have been removed from readr. These
  functions were deprecated in readr 2.0.0 (2021-07-20) and are now
  available in the meltr package (<https://github.com/r-lib/meltr>).

- The `skip_empty_rows` argument of
  [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  now throws an error if used in edition 2. This argument was deprecated
  in readr 2.0.0 (2021-07-20).

## readr 2.1.6

CRAN release: 2025-11-14

- `locale(encoding =)` now warns, instead of errors, when the `encoding`
  cannot be found in the return value of
  [`iconvlist()`](https://rdrr.io/r/base/iconv.html). The motivation is
  to remove an unnecessary blocker on platforms, such as Alpine Linux,
  where the output of [`iconvlist()`](https://rdrr.io/r/base/iconv.html)
  does not reflect the actual capabilities
  ([@bastistician](https://github.com/bastistician),
  [\#1537](https://github.com/tidyverse/readr/issues/1537)).

- Help files below `man/` have been re-generated, as part of the effort
  to support HTML reference manuals on CRAN.

- readr no longer uses `SETLENGTH()`, `SET_TRUELENGTH()`, or
  `SET_GROWABLE_BIT()`. This change improves C API compliance, with a
  small performance cost affecting only the legacy first edition parser.

## readr 2.1.5

CRAN release: 2024-01-10

- No major user-facing changes. Patch release with housekeeping changes
  and internal changes requested by CRAN around format specification in
  compiled code.

## readr 2.1.4

CRAN release: 2023-02-10

- No user-facing changes. Patch release with internal changes requested
  by CRAN.

## readr 2.1.3

CRAN release: 2022-10-01

- Help files below `man/` have been re-generated, so that they give rise
  to valid HTML5. (This is the impetus for this release, to keep the
  package safely on CRAN.)

- `mini-gapminder-africa.csv` and friends are new example datasets
  accessible via
  [`readr_example()`](https://readr.tidyverse.org/dev/reference/readr_example.md),
  which have been added to illustrate reading multiple files at once,
  into a single data frame.

## readr 2.1.2

CRAN release: 2022-01-30

- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md),
  [`read_log()`](https://readr.tidyverse.org/dev/reference/read_log.md),
  and
  [`read_delim_chunked()`](https://readr.tidyverse.org/dev/reference/read_delim_chunked.md)
  (and friends) gain the `show_col_types` argument found elsewhere. All
  `read_*()` functions now respect the `show_col_types` argument or
  option, even when using the first edition parsing engine
  ([\#1331](https://github.com/tidyverse/readr/issues/1331)).

- [`show_progress()`](https://readr.tidyverse.org/dev/reference/show_progress.md)
  uses
  [`rlang::is_interactive()`](https://rlang.r-lib.org/reference/is_interactive.html)
  instead of
  [`base::interactive()`](https://rdrr.io/r/base/interactive.html)
  ([\#1356](https://github.com/tidyverse/readr/issues/1356)).

- [`read_builtin()`](https://readr.tidyverse.org/dev/reference/read_builtin.md)
  does more argument checking, so that we catch obviously malformed
  input before passing along to
  [`utils::data()`](https://rdrr.io/r/utils/data.html)
  ([\#1361](https://github.com/tidyverse/readr/issues/1361)).

- `chickens.csv` and `whitespace-sample.txt` are new example datasets
  accessible via
  [`readr_example()`](https://readr.tidyverse.org/dev/reference/readr_example.md)
  ([\#1354](https://github.com/tidyverse/readr/issues/1354)).

## readr 2.1.1

CRAN release: 2021-11-30

- Jenny Bryan is now the maintainer.

- Fix buffer overflow when trying to parse an integer from a field that
  is over 64 characters long
  ([\#1326](https://github.com/tidyverse/readr/issues/1326))

## readr 2.1.0

CRAN release: 2021-11-11

- All readr functions again read eagerly by default. Unfortunately many
  users experienced frustration from the drawbacks of lazy reading, in
  particular locking files on Windows, so it was decided to disable lazy
  reading default. However `options(readr.read_lazy = TRUE)` can be used
  to set the default to by lazy if desired.
- New `readr.read_lazy` global option to control if readr reads files
  lazily or not
  ([\#1266](https://github.com/tidyverse/readr/issues/1266))

## readr 2.0.2

CRAN release: 2021-09-27

- minor test tweak for compatibility with testthat 3.1.0 (#@lionel-,
  [\#1304](https://github.com/tidyverse/readr/issues/1304))

- [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  gains a `text=` argument, to control using a text based object
  representation, like the `ascii=` argument in
  [`saveRDS()`](https://rdrr.io/r/base/readRDS.html)
  ([\#1270](https://github.com/tidyverse/readr/issues/1270))

## readr 2.0.1

CRAN release: 2021-08-10

- `options(readr.show_col_types = FALSE)` now works as intended
  ([\#1250](https://github.com/tidyverse/readr/issues/1250))

- [`read_delim_chunked()`](https://readr.tidyverse.org/dev/reference/read_delim_chunked.md)
  now again correctly respects the `chunk_size` parameter
  ([\#1248](https://github.com/tidyverse/readr/issues/1248))

- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  gains a `guess_integer` argument, passed to
  [`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  ([@jmbarbone](https://github.com/jmbarbone),
  [\#1264](https://github.com/tidyverse/readr/issues/1264))

- [`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  now correctly passes the `quote` and `na` arguments to
  [`vroom::vroom()`](https://vroom.r-lib.org/reference/vroom.html)
  ([\#1254](https://github.com/tidyverse/readr/issues/1254),
  [\#1255](https://github.com/tidyverse/readr/issues/1255))

- Avoid spurious byte compilation errors due to the programmatically
  generated `spec_*()` functions.

## readr 2.0.0

CRAN release: 2021-07-20

### second edition changes

readr 2.0.0 is a major release of readr and introduces a new second
edition parsing and writing engine implemented via the
[vroom](https://vroom.r-lib.org/) package.

This engine takes advantage of lazy reading, multi-threading and
performance characteristics of modern SSD drives to significantly
improve the performance of reading and writing compared to the first
edition engine.

We will continue to support the first edition for a number of releases,
but eventually this support will be first deprecated and then removed.

You can use the
[`with_edition()`](https://readr.tidyverse.org/dev/reference/with_edition.md)
or
[`local_edition()`](https://readr.tidyverse.org/dev/reference/with_edition.md)
functions to temporarily change the edition of readr for a section of
code.

e.g.

- `with_edition(1, read_csv("my_file.csv"))` will read `my_file.csv`
  with the first edition of readr.

- `readr::local_edition(1)` placed at the top of your function or script
  will use the first edition for the rest of the function or script.

#### Lazy reading

Edition two uses lazy reading by default. When you first call a
`read_*()` function the delimiters and newlines throughout the entire
file are found, but the data is not actually read until it is used in
your program. This can provide substantial speed improvements for
reading character data. It is particularly useful during interactive
exploration of only a subset of a full dataset.

However this also means that problematic values are not necessarily seen
immediately, only when they are actually read. Because of this a warning
will be issued the first time a problem is encountered, which may happen
after initial reading.

Run
[`problems()`](https://readr.tidyverse.org/dev/reference/problems.md) on
your dataset to read the entire dataset and return all of the problems
found. Run `problems(lazy = TRUE)` if you only want to retrieve the
problems found so far.

Deleting files after reading is also impacted by laziness. On Windows
open files cannot be deleted as long as a process has the file open.
Because readr keeps a file open when reading lazily this means you
cannot read, then immediately delete the file. readr will in most cases
close the file once it has been completely read. However, if you know
you want to be able to delete the file after reading it is best to pass
`lazy = FALSE` when reading the file.

#### Reading multiple files at once

Edition two has built-in support for reading sets of files with the same
columns into one output table in a single command. Just pass the
filenames to be read in the same vector to the reading function.

First we generate some files to read by splitting the nycflights dataset
by airline.

`{r} library(nycflights13) purrr::iwalk( split(flights, flights$carrier), ~ { .x$carrier[[1]]; vroom::vroom_write(.x, glue::glue("flights_{.y}.tsv"), delim = "\t") } )`

Then we can efficiently read them into one tibble by passing the
filenames directly to readr.

`{r} files <- fs::dir_ls(glob = "flights*tsv") files readr::read_tsv(files)`

If the filenames contain data, such as the date when the sample was
collected, use `id` argument to include the paths as a column in the
data. You will likely have to post-process the paths to keep only the
relevant portion for your use case.

#### Delimiter guessing

Edition two supports automatic guessing of delimiters. Because of this
you can now use
[`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
without specifying a `delim` argument in many cases.

`{r} x <- read_delim(readr_example("mtcars.csv"))`

#### Literal data

In edition one the reading functions treated any input with a newline in
it or vectors of length \> 1 as literal data. In edition two vectors of
length \> 1 are now assumed to correspond to multiple files. Because of
this we now have a more explicit way to represent literal data, by
putting [`I()`](https://rdrr.io/r/base/AsIs.html) around the input.

`{r} readr::read_csv(I("a,b\n1,2"))`

#### License changes

We are systematically re-licensing tidyverse and r-lib packages to use
the MIT license, to make our package licenses as clear and permissive as
possible.

To this end the readr and vroom packages are now released under the MIT
license.

#### Deprecated or superseded functions and features

- `melt_csv()`, `melt_delim()`, `melt_tsv()` and `melt_fwf()` have been
  superseded by functions in the same name in the meltr package. The
  versions in readr have been deprecated. These functions rely on the
  first edition parsing code and would be challenging to update to the
  new parser. When the first edition parsing code is eventually removed
  from readr they will be removed.

- [`read_table2()`](https://readr.tidyverse.org/dev/reference/read_table2.md)
  has been renamed to
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md),
  as most users expect
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  to work like
  [`utils::read.table()`](https://rdrr.io/r/utils/read.table.html). If
  you want the previous strict behavior of the
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  you can use
  [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  with
  [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  directly ([\#717](https://github.com/tidyverse/readr/issues/717)).

- Normalizing newlines in files with just carriage returns `\r` is no
  longer supported. The last major OS to use only CR as the newline was
  ‘classic’ Mac OS, which had its final release in 2001.

#### Other second edition changes

- `read_*_chunked()` functions now include their specification as an
  attribute ([\#1143](https://github.com/tidyverse/readr/issues/1143))

- All `read_*()` functions gain a `col_select` argument to more easily
  choose which columns to select.

- All `read_*()` functions gain a `id` argument to optionally store the
  file paths when reading multiple files.

- All `read_*()` functions gain a `name_repair` argument to control how
  column names are repaired.

- All `read_*()` and `write_*()` functions gain a `num_threads` argument
  to control the number of processing threads they use
  ([\#1201](https://github.com/tidyverse/readr/issues/1201))

- All `write_*()` and `format_*()` functions gain `quote` and `escape`
  arguments, to explicitly control how fields are quoted and how double
  quotes are escaped.
  ([\#653](https://github.com/tidyverse/readr/issues/653),
  [\#759](https://github.com/tidyverse/readr/issues/759),
  [\#844](https://github.com/tidyverse/readr/issues/844),
  [\#993](https://github.com/tidyverse/readr/issues/993),
  [\#1018](https://github.com/tidyverse/readr/issues/1018),
  [\#1083](https://github.com/tidyverse/readr/issues/1083))

- All `write_*()` functions gain a `progress` argument and display a
  progress bar when writing
  ([\#791](https://github.com/tidyverse/readr/issues/791)).

- write_excel_csv() now defaults to `quote = "all"`
  ([\#759](https://github.com/tidyverse/readr/issues/759))

- write_tsv() now defaults to `quote = "none"`
  ([\#993](https://github.com/tidyverse/readr/issues/993))

- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  now handles skipped lines with unpaired quotes properly
  ([\#1180](https://github.com/tidyverse/readr/issues/1180))

### Additional features and fixes

- The BH package is no longer a dependency. The boost C++ headers in BH
  have thousands of files, so can take a long time to extract and
  compiling them takes a great deal of memory, which made readr
  difficult to compile on systems with limited memory
  ([\#1147](https://github.com/tidyverse/readr/issues/1147)).

- readr now uses the tzdb package when parsing date-times
  ([@DavisVaughan](https://github.com/DavisVaughan), r-lib/vroom#273)

- Chunked readers now support files with more than `INT_MAX` (~ 2
  Billion) number of lines
  ([\#1177](https://github.com/tidyverse/readr/issues/1177))

- Memory no longer inadvertently leaks when reading memory from R
  connections ([\#1161](https://github.com/tidyverse/readr/issues/1161))

- Invalid date formats no longer can potentially crash R
  ([\#1151](https://github.com/tidyverse/readr/issues/1151))

- [`col_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  now throws a more informative error message if given non-character
  levels ([\#1140](https://github.com/tidyverse/readr/issues/1140))

- [`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  now takes `.Last.value` as its default argument. This lets you run
  [`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  without an argument to see the problems in the previously read
  dataset.

- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  fails when sample of parsing problems contains non-ASCII characters
  ([@hidekoji](https://github.com/hidekoji),
  [\#1136](https://github.com/tidyverse/readr/issues/1136))

- [`read_log()`](https://readr.tidyverse.org/dev/reference/read_log.md)
  gains a `trim_ws` argument
  ([\#738](https://github.com/tidyverse/readr/issues/738))

- [`read_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  and
  [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  gain a `refhook` argument, to pass functions that handle references
  objects ([\#1206](https://github.com/tidyverse/readr/issues/1206))

- [`read_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  can now read .Rds files from URLs
  ([\#1186](https://github.com/tidyverse/readr/issues/1186))

- `read_*()` functions gain a `show_col_types` argument, if set to
  `FALSE` this turns off showing the column types unconditionally.

- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  now throws a warning if the input has no character columns
  ([\#1020](https://github.com/tidyverse/readr/issues/1020))

- [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  now errors if given a matrix column
  ([\#1171](https://github.com/tidyverse/readr/issues/1171))

- [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  now again is able to write data with duplicated column names
  ([\#1169](https://github.com/tidyverse/readr/issues/1169))

- [`write_file()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  now forces its argument before opening the output file
  ([\#1158](https://github.com/tidyverse/readr/issues/1158))

## readr 1.4.0

CRAN release: 2020-10-05

### Breaking changes

- `write_*()` functions first argument is now `file` instead of `path`,
  for consistency with the `read_*()` functions. `path` has been
  deprecated and will be removed in a future version of readr
  ([\#1110](https://github.com/tidyverse/readr/issues/1110),
  [@brianrice2](https://github.com/brianrice2))

- `write_*()` functions now output any NaN values in the same way as NA
  values, controlled by the `na=` argument.
  ([\#1082](https://github.com/tidyverse/readr/issues/1082)).

### New features

- It is now possible to generate a column specification from any tibble
  (or data.frame) with
  [`as.col_spec()`](https://readr.tidyverse.org/dev/reference/as.col_spec.md)
  and convert any column specification to a short representation with
  [`as.character()`](https://rdrr.io/r/base/character.html)

  ``` R
  s <- as.col_spec(iris)
  s
  #> cols(
  #>   Sepal.Length = col_double(),
  #>   Sepal.Width = col_double(),
  #>   Petal.Length = col_double(),
  #>   Petal.Width = col_double(),
  #>   Species = col_factor(levels = c("setosa", "versicolor", "virginica"), ordered = FALSE, include_na = FALSE)
  #> )
  as.character(s)
  #> [1] "ddddf"
  ```

- The cli package is now used for all messages.

- The runtime performance for tables with an extreme number of columns
  is greatly improved
  ([\#825](https://github.com/tidyverse/readr/issues/825))

- Compressed files are now detected by magic numbers rather than by the
  file extension
  ([\#1125](https://github.com/tidyverse/readr/issues/1125))

- A memory leak when reading files is now fixed
  ([\#1092](https://github.com/tidyverse/readr/issues/1092))

- `write_*()` functions gain a `eol =` argument to control the end of
  line character used
  ([\#857](https://github.com/tidyverse/readr/issues/857)). This allows
  writing of CSV files with Windows newlines (CRLF) if desired.

- The Rcpp dependency has been removed in favor of cpp11.

- The build system has been greatly simplified so should work on more
  systems.

### Additional features and fixes

- The full problem field is now displayed in the problems tibble, as
  intended ([\#444](https://github.com/tidyverse/readr/issues/444)).

- New `%h` placeholder for parsing unrestricted hours (\<0 and \>23) to
  support parsing durations
  ([\#549](https://github.com/tidyverse/readr/issues/549),
  [@krlmlr](https://github.com/krlmlr)).

- `as.character.col_spec()` now handles logical columns as well
  ([\#1127](https://github.com/tidyverse/readr/issues/1127))

- `fwf_positions(end)` no longer has a default argument and must be
  specified ([\#996](https://github.com/tidyverse/readr/issues/996))

- [`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  gains a `na` argument and removes NA values before guessing
  ([\#1041](https://github.com/tidyverse/readr/issues/1041)).

- [`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  now passes the `na` argument to
  [`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)

- `read_*` functions now close properly all connections, including on
  errors like HTTP errors when reading from a url
  ([@cderv](https://github.com/cderv),
  [\#1050](https://github.com/tidyverse/readr/issues/1050)).

- `read_delimited()` no longer mistakenly stats literal filenames
  ([\#1063](https://github.com/tidyverse/readr/issues/1063))

- [`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  now ignores quotations when skipping lines
  ([\#991](https://github.com/tidyverse/readr/issues/991)).

- `read_lines(skip_empty_rows = TRUE)` no longer crashes if a file ends
  with an empty line
  ([\#968](https://github.com/tidyverse/readr/issues/968))

- `write_*()` functions now invisibly return the input data frame
  unchanged, rather than a version with factors and dates converted to
  strings. ([@jesse-ross](https://github.com/jesse-ross),
  [\#975](https://github.com/tidyverse/readr/issues/975)).

- [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  now formats decimal numbers more consistently with
  [`utils::write.csv2()`](https://rdrr.io/r/utils/write.table.html)
  ([\#1087](https://github.com/tidyverse/readr/issues/1087))

- [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  and
  [`format_csv2()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  no longer pad number columns with whitespaces
  ([@keesdeschepper](https://github.com/keesdeschepper),
  [\#1046](https://github.com/tidyverse/readr/issues/1046)).

- [`write_excel_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  no longer outputs a byte order mark when appending to a file
  ([\#1075](https://github.com/tidyverse/readr/issues/1075)).

- Uses of
  [`tibble::data_frame`](https://tibble.tidyverse.org/reference/deprecated.html)
  updated to
  [`tibble::tibble`](https://tibble.tidyverse.org/reference/tibble.html)
  ([tidyverse/dplyr#4069](https://github.com/tidyverse/dplyr/issues/4069),
  [@thays42](https://github.com/thays42),
  [\#1124](https://github.com/tidyverse/readr/issues/1124),
  [@brianrice2](https://github.com/brianrice2))

- `read_delimited()` now returns an empty
  [`tibble::data_frame()`](https://tibble.tidyverse.org/reference/deprecated.html)
  rather than signaling an error when given a connection with an empty
  file ([@pralitp](https://github.com/pralitp),
  [\#963](https://github.com/tidyverse/readr/issues/963)).

- More helpful error when trying to write out data frames with list
  columns ([@ellessenne](https://github.com/ellessenne),
  [\#938](https://github.com/tidyverse/readr/issues/938))

- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  removes a ‘spec’ attribute, because the current columns likely have
  modified data types. The ‘spec’ attribute is set by functions like
  [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  ([@jimhester](https://github.com/jimhester),
  [@wibeasley](https://github.com/wibeasley),
  [\#1032](https://github.com/tidyverse/readr/issues/1032)).

- [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  now can specify the Rds version to use. The default value is 2 as it’s
  compatible to R versions prior to 3.5.0
  ([@shrektan](https://github.com/shrektan),
  [\#1001](https://github.com/tidyverse/readr/issues/1001)).

- Fixes for issues related to variable initialization in C++ code
  ([@michaelquinn32](https://github.com/michaelquinn32), \##1133).

## readr 1.3.1

CRAN release: 2018-12-21

- Column specifications are now coloured when printed. This makes it
  easy to see at a glance when a column is input as a different type
  then the rest. Colouring can be disabled by setting
  `options(crayon.enabled = FALSE)`.

- [`as.col_spec()`](https://readr.tidyverse.org/dev/reference/as.col_spec.md)
  can now use named character vectors, which makes
  `read_csv("file.csv", col_types = c(xyz = "c"))` equivalent to
  `read_csv("file.csv", col_types = cols(xyz = col_character())`

- Fix skipping when single quotes are embedded in double quoted strings,
  and single quotes in skipped or commented lines
  ([\#944](https://github.com/tidyverse/readr/issues/944),
  [\#945](https://github.com/tidyverse/readr/issues/945)).

- Fix for compilation using custom architectures on macOS
  ([\#919](https://github.com/tidyverse/readr/issues/919))

- Fix for valgrind errors
  ([\#941](https://github.com/tidyverse/readr/issues/941))

## readr 1.3.0

CRAN release: 2018-12-11

### Breaking Changes

#### Blank line skipping

readr’s blank line skipping has been modified to be more consistent and
to avoid edge cases that affected the behavior in 1.2.0. The skip
parameter now behaves more similar to how it worked previous to readr
1.2.0, but in addition the parameter `skip_blank_rows` can be used to
control if fully blank lines are skipped.
([\#923](https://github.com/tidyverse/readr/issues/923))

#### tibble data frame subclass

readr 1.3.0 returns results with a `spec_tbl_df` subclass. This differs
from a regular tibble only that the `spec` attribute (which holds the
column specification) is lost as soon as the object is subset (and a
normal `tbl_df` object is returned).

Historically `tbl_df`’s lost their attributes once they were subset.
However recent versions of tibble retain the attributes when subetting,
so the `spec_tbl_df` subclass is needed to ensure the previous behavior.

This should only break compatibility if you are explicitly checking the
class of the returned object. A way to get backwards compatible behavior
is to call subset with no arguments on your object, e.g. `x[]`.

### Bugfixes

- `hms` objects with NA values are now written without whitespace
  padding ([\#930](https://github.com/tidyverse/readr/issues/930)).
- `read_*()` functions now return `spec_tbl_df` objects, which differ
  from regular `tbl_df` objects only in that the `spec` attribute is
  removed (and they are demoted to regular `tbl_df` objects) as soon as
  they are subset
  ([\#934](https://github.com/tidyverse/readr/issues/934)).
- [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  now properly respects the `na` argument
  ([\#928](https://github.com/tidyverse/readr/issues/928))
- Fixes compilation with multiple architectures on linux
  ([\#922](https://github.com/tidyverse/readr/issues/922)).
- Fixes compilation with R \< 3.3.0

## readr 1.2.1

CRAN release: 2018-11-22

This release skips the clipboard tests on CRAN servers

## readr 1.2.0

CRAN release: 2018-11-22

### Breaking Changes

#### Integer column guessing

readr functions no longer guess columns are of type integer, instead
these columns are guessed as numeric. Because R uses 32 bit integers and
64 bit doubles all integers can be stored in doubles, guaranteeing no
loss of information. This change was made to remove errors when numeric
columns were incorrectly guessed as integers. If you know a certain
column is an integer and would like to read them as such you can do so
by specifying the column type explicitly with the `col_types` argument.

#### Blank line skipping

readr now always skips blank lines automatically when parsing, which may
change the number of lines you need to pass to the `skip` parameter. For
instance if your file had a one blank line then two more lines you want
to skip previously you would pass `skip = 3`, now you only need to pass
`skip = 2`.

### New features

#### Melt functions

There is now a family of `melt_*()` functions in readr. These functions
store data in ‘long’ or ‘melted’ form, where each row corresponds to a
single value in the dataset. This form is useful when your data is
ragged and not rectangular.

``` r
data <-"a,b,c
1,2
w,x,y,z"

readr::melt_csv(data)
#> # A tibble: 9 x 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character a    
#> 2     1     2 character b    
#> 3     1     3 character c    
#> 4     2     1 integer   1    
#> 5     2     2 integer   2    
#> 6     3     1 character w    
#> 7     3     2 character x    
#> 8     3     3 character y    
#> 9     3     4 character z
```

Thanks to Duncan Garmonsway ([@nacnudus](https://github.com/nacnudus))
for great work on the idea an implementation of the `melt_*()`
functions!

#### Connection improvements

readr 1.2.0 changes how R connections are parsed by readr. In previous
versions of readr the connections were read into an in-memory raw
vector, then passed to the readr functions. This made reading
connections from small to medium datasets fast, but also meant that the
dataset had to fit into memory at least twice (once for the raw data,
once for the parsed data). It also meant that reading could not begin
until the full vector was read through the connection.

Now we instead write the connection to a temporary file (in the R
temporary directory), than parse that temporary file. This means
connections may take a little longer to be read, but also means they
will no longer need to fit into memory. It also allows the use of the
chunked readers to process the data in parts.

Future improvements to readr would allow it to parse data from
connections in a streaming fashion, which would avoid many of the
drawbacks of either method.

#### Additional new features

- `melt_*()` functions added for reading ragged data
  ([\#760](https://github.com/tidyverse/readr/issues/760),
  [@nacnudus](https://github.com/nacnudus)).
- `AccumulateCallback` R6 class added to provide an example of
  accumulating values in a single result
  ([\#689](https://github.com/tidyverse/readr/issues/689),
  [@blakeboswell](https://github.com/blakeboswell)).
- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  can now accept overlapping field specifications
  ([\#692](https://github.com/tidyverse/readr/issues/692),
  [@gergness](https://github.com/gergness))
- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  now allows character column specifications and also silently skips
  non-character columns
  ([\#369](https://github.com/tidyverse/readr/issues/369),
  [\#699](https://github.com/tidyverse/readr/issues/699))
- The `parse_*()` functions and
  [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  gain a `trim_ws` argument to control whether the fields should be
  trimmed before parsing
  ([\#636](https://github.com/tidyverse/readr/issues/636),
  [\#735](https://github.com/tidyverse/readr/issues/735)).
- [`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  now parses numbers in scientific notation using `e` and `E`
  ([\#684](https://github.com/tidyverse/readr/issues/684),
  [@sambrady3](https://github.com/sambrady3)).
- Add
  [`write_excel_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  function to allow writing csv files with comma as a decimal separator
  and semicolon as a column separator
  ([\#753](https://github.com/tidyverse/readr/issues/753),
  [@olgamie](https://github.com/olgamie)).
- `read_*()` files now support reading from the clipboard by using
  [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  ([\#656](https://github.com/tidyverse/readr/issues/656)).
- [`write_file()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  gains a `sep` argument, to specify the line separator
  ([\#665](https://github.com/tidyverse/readr/issues/665)).
- Allow files to be read via FTP over SSH by recognising `sftp` as a URL
  protocol ([\#707](https://github.com/tidyverse/readr/issues/707),
  [@jdeboer](https://github.com/jdeboer)).
- `parse_date*() accepts`%a\` for local day of week
  ([\#763](https://github.com/tidyverse/readr/issues/763),
  [@tigertoes](https://github.com/tigertoes)).
- Added function
  [`read_lines_raw_chunked()`](https://readr.tidyverse.org/dev/reference/read_lines_chunked.md)
  ([\#710](https://github.com/tidyverse/readr/issues/710),
  [@gergness](https://github.com/gergness))
- [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  added to complement
  [`write_excel_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  and allow writing csv file readable by
  [`read_csv2()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  ([\#870](https://github.com/tidyverse/readr/issues/870),
  [@cderv](https://github.com/cderv)).
- [`as.col_spec()`](https://readr.tidyverse.org/dev/reference/as.col_spec.md)
  is now exported
  ([\#517](https://github.com/tidyverse/readr/issues/517)).
- `write*()` functions gain a `quote_escape` argument to control how
  quotes are escaped in the output
  ([\#854](https://github.com/tidyverse/readr/issues/854)).
- `read*()` functions now have a more informative error when trying to
  read a remote bz2 file
  ([\#891](https://github.com/tidyverse/readr/issues/891)).
- `spec_table2()` function added to correspond to
  [`read_table2()`](https://readr.tidyverse.org/dev/reference/read_table2.md)
  ([\#778](https://github.com/tidyverse/readr/issues/778),
  [@mawds](https://github.com/mawds)).
- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  now has `levels = NULL` by default
  ([\#862](https://github.com/tidyverse/readr/issues/862),
  [@mikmart](https://github.com/mikmart)).
- `"f"` can now be used as a shortcode for
  [`col_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  in [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md) and
  the `col_types` argument to
  [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  and friends ([\#810](https://github.com/tidyverse/readr/issues/810),
  [@mikmart](https://github.com/mikmart)).
- Functions now read connections to a temporary file rather than to an
  in-memory object
  ([\#610](https://github.com/tidyverse/readr/issues/610),
  [\#76](https://github.com/tidyverse/readr/issues/76)).

### Bug Fixes

- `standardise_path()` now uses a case-insensitive comparison for the
  file extensions
  ([\#794](https://github.com/tidyverse/readr/issues/794)).
- [`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  now guesses logical types when given (lowercase) ‘true’ and ‘false’
  inputs ([\#818](https://github.com/tidyverse/readr/issues/818)).
- `read_*()` now do not print a progress bar when running inside a
  RStudio notebook chunk
  ([\#793](https://github.com/tidyverse/readr/issues/793))
- [`read_table2()`](https://readr.tidyverse.org/dev/reference/read_table2.md)
  now skips comments anywhere in the file
  ([\#908](https://github.com/tidyverse/readr/issues/908)).
- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  now handles the case of empty strings separately, so you can have a
  factor level that is an empty string
  ([\#864](https://github.com/tidyverse/readr/issues/864)).
- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  now correctly reads quoted headers with embedded newlines
  ([\#784](https://github.com/tidyverse/readr/issues/784)).
- [`fwf_positions()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  now always returns `col_names` as a character
  ([\#797](https://github.com/tidyverse/readr/issues/797)).
- `format_*()` now explicitly marks it’s output encoding as UTF-8
  ([\#697](https://github.com/tidyverse/readr/issues/697)).
- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  now ignores whitespace between the delimiter and quoted fields
  ([\#668](https://github.com/tidyverse/readr/issues/668)).
- [`read_table2()`](https://readr.tidyverse.org/dev/reference/read_table2.md)
  now properly ignores blank lines at the end of a file like
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  and
  [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  ([\#657](https://github.com/tidyverse/readr/issues/657)).
- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  and
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  now skip blank lines at the start of a file
  ([\#680](https://github.com/tidyverse/readr/issues/680),
  [\#747](https://github.com/tidyverse/readr/issues/747)).
- [`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  now guesses a logical type for columns which are all missing. This is
  useful when binding multiple files together where some files have
  missing columns.
  ([\#662](https://github.com/tidyverse/readr/issues/662)).
- Column guessing will now never guess an integer type. This avoids
  issues where double columns are incorrectly guessed as integers if
  they have only integer values in the first 1000
  ([\#645](https://github.com/tidyverse/readr/issues/645),
  [\#652](https://github.com/tidyverse/readr/issues/652)).
- `read_*()` now converts string `file`s to UTF-8 before parsing, which
  is convenient for non-UTF-8 platforms in most cases
  ([\#730](https://github.com/tidyverse/readr/issues/730),
  [@yutannihilation](https://github.com/yutannihilation)).
- [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  writes integers up to 10^15 without scientific notation
  ([\#765](https://github.com/tidyverse/readr/issues/765),
  [@zeehio](https://github.com/zeehio))
- `read_*()` no longer throws a “length of NULL cannot be changed”
  warning when trying to resize a skipped column
  ([\#750](https://github.com/tidyverse/readr/issues/750),
  [\#833](https://github.com/tidyverse/readr/issues/833)).
- `read_*()` now handles non-ASCII paths properly with R \>=3.5.0 on
  Windows ([\#838](https://github.com/tidyverse/readr/issues/838),
  [@yutannihilation](https://github.com/yutannihilation)).
- `read*()`’s `trim_ws` parameter now trims both spaces and tabs
  ([\#767](https://github.com/tidyverse/readr/issues/767))

## readr 1.1.1

CRAN release: 2017-05-16

- Point release for test compatibility with tibble v1.3.1.
- Fixed undefined behavior in localtime.c when using `locale(tz = "")`
  after loading a timezone due to incomplete reinitialization of the
  global locale.

## readr 1.1.0

CRAN release: 2017-03-22

### New features

#### Parser improvements

- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  gains a `include_na` argument, to include `NA` in the factor levels
  ([\#541](https://github.com/tidyverse/readr/issues/541)).
- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  will now can accept `levels = NULL`, which allows one to generate
  factor levels based on the data (like stringsAsFactors = TRUE)
  ([\#497](https://github.com/tidyverse/readr/issues/497)).
- [`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  now returns the full string if it contains no numbers
  ([\#548](https://github.com/tidyverse/readr/issues/548)).
- [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  now correctly handles 12 AM/PM
  ([\#579](https://github.com/tidyverse/readr/issues/579)).
- [`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  now returns the file path in additional to the location of the error
  in the file ([\#581](https://github.com/tidyverse/readr/issues/581)).
- [`read_csv2()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  gives a message if it updates the default locale
  ([\#443](https://github.com/tidyverse/readr/issues/443),
  [@krlmlr](https://github.com/krlmlr)).
- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  now signals an error if given an empty delimiter
  ([\#557](https://github.com/tidyverse/readr/issues/557)).
- `write_*()` functions witting whole number doubles are no longer
  written with a trailing `.0`
  ([\#526](https://github.com/tidyverse/readr/issues/526)).

#### Whitespace / fixed width improvements

- [`fwf_cols()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  allows for specifying the `col_positions` argument of
  [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  with named arguments of either column positions or widths
  ([\#616](https://github.com/tidyverse/readr/issues/616),
  [@jrnold](https://github.com/jrnold)).
- [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  gains an `n` argument to control how many lines are read for
  whitespace to determine column structure
  ([\#518](https://github.com/tidyverse/readr/issues/518),
  [@Yeedle](https://github.com/Yeedle)).
- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  gives error message if specifications have overlapping columns
  ([\#534](https://github.com/tidyverse/readr/issues/534),
  [@gergness](https://github.com/gergness))
- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  can now handle [`pipe()`](https://rdrr.io/r/base/connections.html)
  connections ([\#552](https://github.com/tidyverse/readr/issues/552)).
- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  can now handle files with many lines of leading comments
  ([\#563](https://github.com/tidyverse/readr/issues/563)).
- [`read_table2()`](https://readr.tidyverse.org/dev/reference/read_table2.md)
  which allows any number of whitespace characters as delimiters, a more
  exact replacement for
  [`utils::read.table()`](https://rdrr.io/r/utils/read.table.html)
  ([\#608](https://github.com/tidyverse/readr/issues/608)).

### Writing to connections

- `write_*()` functions now support writing to binary connections. In
  addition output filenames with `.gz`, `.bz2` or `.xz` will
  automatically open the appropriate connection and to write the
  compressed file.
  ([\#348](https://github.com/tidyverse/readr/issues/348))
- [`write_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  now accepts a list of raw vectors
  ([\#542](https://github.com/tidyverse/readr/issues/542)).

### Miscellaneous features

- `col_euro_double()`, `parse_euro_double()`, `col_numeric()`, and
  `parse_numeric()` have been removed.
- [`guess_encoding()`](https://readr.tidyverse.org/dev/reference/encoding.md)
  returns a tibble, and works better with lists of raw vectors (as
  returned by
  [`read_lines_raw()`](https://readr.tidyverse.org/dev/reference/read_lines.md)).
- `ListCallback` R6 Class to provide a more flexible return type for
  callback functions
  ([\#568](https://github.com/tidyverse/readr/issues/568),
  [@mmuurr](https://github.com/mmuurr))
- [`tibble::as.tibble()`](https://tibble.tidyverse.org/reference/deprecated.html)
  now used to construct tibbles
  ([\#538](https://github.com/tidyverse/readr/issues/538)).
- `read_csv`, `read_csv2`, and `read_tsv` gain a `quote` argument,
  ([\#631](https://github.com/tidyverse/readr/issues/631),
  [@noamross](https://github.com/noamross))

### Bugfixes

- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  now converts data to UTF-8 based on the supplied locale
  ([\#615](https://github.com/tidyverse/readr/issues/615)).
- `read_*()` functions with the `guess_max` argument now throw errors on
  inappropriate inputs
  ([\#588](https://github.com/tidyverse/readr/issues/588)).
- `read_*_chunked()` functions now properly end the stream if `FALSE` is
  returned from the callback.
- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  and
  [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  when columns are skipped using `col_types` now report the correct
  column name ([\#573](https://github.com/tidyverse/readr/issues/573),
  [@cb4ds](https://github.com/cb4ds)).
- [`spec()`](https://readr.tidyverse.org/dev/reference/spec.md)
  declarations that are long now print properly
  ([\#597](https://github.com/tidyverse/readr/issues/597)).
- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  does not print `spec` when `col_types` is not `NULL`
  ([\#630](https://github.com/tidyverse/readr/issues/630),
  [@jrnold](https://github.com/jrnold)).
- [`guess_encoding()`](https://readr.tidyverse.org/dev/reference/encoding.md)
  now returns a tibble for all ASCII input as well
  ([\#641](https://github.com/tidyverse/readr/issues/641)).

## readr 1.0.0

CRAN release: 2016-08-03

### Column guessing

The process by which readr guesses the types of columns has received a
substantial overhaul to make it easier to fix problems when the initial
guesses aren’t correct, and to make it easier to generate reproducible
code. Now column specifications are printing by default when you read
from a file:

``` r
challenge <- read_csv(readr_example("challenge.csv"))
#> Parsed with column specification:
#> cols(
#>   x = col_integer(),
#>   y = col_character()
#> )
```

And you can extract those values after the fact with
[`spec()`](https://readr.tidyverse.org/dev/reference/spec.md):

``` r
spec(challenge)
#> cols(
#>   x = col_integer(),
#>   y = col_character()
#> )
```

This makes it easier to quickly identify parsing problems and fix them
([\#314](https://github.com/tidyverse/readr/issues/314)). If the column
specification is long, the new
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md)
is used to condense the spec by identifying the most common type and
setting it as the default. This is particularly useful when only a
handful of columns have a different type
([\#466](https://github.com/tidyverse/readr/issues/466)).

You can also generating an initial specification without parsing the
file using
[`spec_csv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md),
[`spec_tsv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md),
etc.

Once you have figured out the correct column types for a file, it’s
often useful to make the parsing strict. You can do this either by
copying and pasting the printed output, or for very long specs, saving
the spec to disk with
[`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md).
In production scripts, combine this with
[`stop_for_problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
([\#465](https://github.com/tidyverse/readr/issues/465)): if the input
data changes form, you’ll fail fast with an error.

You can now also adjust the number of rows that readr uses to guess the
column types with `guess_max`:

``` r
challenge <- read_csv(readr_example("challenge.csv"), guess_max = 1500)
#> Parsed with column specification:
#> cols(
#>   x = col_double(),
#>   y = col_date(format = "")
#> )
```

You can now access the guessing algorithm from R.
[`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
will tell you which parser readr will select for a character vector
([\#377](https://github.com/tidyverse/readr/issues/377)). We’ve made a
number of fixes to the guessing algorithm:

- New example `extdata/challenge.csv` which is carefully created to
  cause problems with the default column type guessing heuristics.

- Blank lines and lines with only comments are now skipped automatically
  without warning
  ([\#381](https://github.com/tidyverse/readr/issues/381),
  [\#321](https://github.com/tidyverse/readr/issues/321)).

- Single ‘-’ or ‘.’ are now parsed as characters, not numbers
  ([\#297](https://github.com/tidyverse/readr/issues/297)).

- Numbers followed by a single trailing character are parsed as
  character, not numbers
  ([\#316](https://github.com/tidyverse/readr/issues/316)).

- We now guess at times using the `time_format` specified in the
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md).

We have made a number of improvements to the reification of the
`col_types`, `col_names` and the actual data:

- If `col_types` is too long, it is subsetted correctly
  ([\#372](https://github.com/tidyverse/readr/issues/372),
  [@jennybc](https://github.com/jennybc)).

- If `col_names` is too short, the added names are numbered correctly
  ([\#374](https://github.com/tidyverse/readr/issues/374),
  [@jennybc](https://github.com/jennybc)).

- Missing column name names are now given a default name (`X2`, `X7`
  etc) ([\#318](https://github.com/tidyverse/readr/issues/318)).
  Duplicated column names are now deduplicated. Both changes generate a
  warning; to suppress it supply an explicit `col_names` (setting
  `skip = 1` if there’s an existing ill-formed header).

- `col_types()` accepts a named list as input
  ([\#401](https://github.com/tidyverse/readr/issues/401)).

### Column parsing

The date time parsers recognise three new format strings:

- `%I` for 12 hour time format
  ([\#340](https://github.com/tidyverse/readr/issues/340)).

- `%AD` and `%AT` are “automatic” date and time parsers. They are both
  slightly less flexible than previous defaults. The automatic date
  parser requires a four digit year, and only accepts `-` and `/` as
  separators ([\#442](https://github.com/tidyverse/readr/issues/442)).
  The flexible time parser now requires colons between hours and minutes
  and optional seconds
  ([\#424](https://github.com/tidyverse/readr/issues/424)).

`%y` and `%Y` are now strict and require 2 or 4 characters respectively.

Date and time parsing functions received a number of small enhancements:

- [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  returns `hms` objects rather than a custom `time` class
  ([\#409](https://github.com/tidyverse/readr/issues/409)). It now
  correctly parses missing values
  ([\#398](https://github.com/tidyverse/readr/issues/398)).

- [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  returns a numeric vector (instead of an integer vector)
  ([\#357](https://github.com/tidyverse/readr/issues/357)).

- [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
  [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  and
  [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  gain an `na` argument to match all other parsers
  ([\#413](https://github.com/tidyverse/readr/issues/413)).

- If the format argument is omitted
  [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  or
  [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
  date and time formats specified in the locale will be used. These now
  default to `%AD` and `%AT` respectively.

- You can now parse partial dates with
  [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  and
  [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
  e.g. `parse_date("2001", "%Y")` returns `2001-01-01`.

[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
is slightly more flexible - it now parses numbers up to the first
ill-formed character. For example `parse_number("-3-")` and
`parse_number("...3...")` now return -3 and 3 respectively. We also
fixed a major bug where parsing negative numbers yielded positive values
([\#308](https://github.com/tidyverse/readr/issues/308)).

[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
now accepts `0`, `1` as well as lowercase `t`, `f`, `true`, `false`.

### New readers and writers

- [`read_file_raw()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  reads a complete file into a single raw vector
  ([\#451](https://github.com/tidyverse/readr/issues/451)).

- `read_*()` functions gain a `quoted_na` argument to control whether
  missing values within quotes are treated as missing values or as
  strings ([\#295](https://github.com/tidyverse/readr/issues/295)).

- [`write_excel_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  can be used to write a csv file with a UTF-8 BOM at the start, which
  forces Excel to read it as UTF-8 encoded
  ([\#375](https://github.com/tidyverse/readr/issues/375)).

- [`write_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  writes a character vector to a file
  ([\#302](https://github.com/tidyverse/readr/issues/302)).

- [`write_file()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  to write a single character or raw vector to a file
  ([\#474](https://github.com/tidyverse/readr/issues/474)).

- Experimental support for chunked reading a writing
  (`read_*_chunked()`) functions. The API is unstable and subject to
  change in the future
  ([\#427](https://github.com/tidyverse/readr/issues/427)).

### Minor features and bug fixes

- Printing double values now uses an
  [implementation](https://github.com/juj/MathGeoLib/blob/master/src/Math/grisu3.c)
  of the [grisu3
  algorithm](http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf)
  which speeds up writing of large numeric data frames by ~10X.
  ([\#432](https://github.com/tidyverse/readr/issues/432)) ‘.0’ is
  appended to whole number doubles, to ensure they will be read as
  doubles as well.
  ([\#483](https://github.com/tidyverse/readr/issues/483))

- readr imports tibble so that you get consistent `tbl_df` behaviour
  ([\#317](https://github.com/tidyverse/readr/issues/317),
  [\#385](https://github.com/tidyverse/readr/issues/385)).

- New example `extdata/challenge.csv` which is carefully created to
  cause problems with the default column type guessing heuristics.

- [`default_locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  now sets the default locale in `readr.default_locale` rather than
  regenerating it for each call.
  ([\#416](https://github.com/tidyverse/readr/issues/416)).

- [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) now
  automatically sets decimal mark if you set the grouping mark. It
  throws an error if you accidentally set decimal and grouping marks to
  the same character
  ([\#450](https://github.com/tidyverse/readr/issues/450)).

- All `read_*()` can read into long vectors, substantially increasing
  the number of rows you can read
  ([\#309](https://github.com/tidyverse/readr/issues/309)).

- All `read_*()` functions return empty objects rather than signaling an
  error when run on an empty file
  ([\#356](https://github.com/tidyverse/readr/issues/356),
  [\#441](https://github.com/tidyverse/readr/issues/441)).

- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  gains a `trim_ws` argument
  ([\#312](https://github.com/tidyverse/readr/issues/312), noamross)

- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  received a number of improvements:

  - [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    now can now reliably read only a partial set of columns
    ([\#322](https://github.com/tidyverse/readr/issues/322),
    [\#353](https://github.com/tidyverse/readr/issues/353),
    [\#469](https://github.com/tidyverse/readr/issues/469))

  - [`fwf_widths()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    accepts negative column widths for compatibility with the `widths`
    argument in [`read.fwf()`](https://rdrr.io/r/utils/read.fwf.html)
    ([\#380](https://github.com/tidyverse/readr/issues/380),
    [@leeper](https://github.com/leeper)).

  - You can now read fixed width files with ragged final columns, by
    setting the final end position in
    [`fwf_positions()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    or final width in
    [`fwf_widths()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    to `NA` ([\#353](https://github.com/tidyverse/readr/issues/353),
    [@ghaarsma](https://github.com/ghaarsma)).
    [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    does this automatically.

  - [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    and
    [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
    can now skip commented lines by setting a `comment` argument
    ([\#334](https://github.com/tidyverse/readr/issues/334)).

- [`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  ignores embedded null’s in strings
  ([\#338](https://github.com/tidyverse/readr/issues/338)) and gains a
  `na` argument
  ([\#479](https://github.com/tidyverse/readr/issues/479)).

- [`readr_example()`](https://readr.tidyverse.org/dev/reference/readr_example.md)
  makes it easy to access example files bundled with readr.

- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  now accepts only `NULL` or a `cols` specification for `col_types`
  ([\#369](https://github.com/tidyverse/readr/issues/369)).

- [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  and
  [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  now invisibly return the input data frame (as documented,
  [\#363](https://github.com/tidyverse/readr/issues/363)).

- Doubles are parsed with `boost::spirit::qi::long_double` to work
  around a bug in the spirit library when parsing large numbers
  ([\#412](https://github.com/tidyverse/readr/issues/412)).

- Fix bug when detecting column types for single row files without
  headers ([\#333](https://github.com/tidyverse/readr/issues/333)).

## readr 0.2.2

CRAN release: 2015-10-22

- Fix bug when checking empty values for missingness (caused valgrind
  issue and random crashes).

## readr 0.2.1

CRAN release: 2015-10-21

- Fixes so that readr works on Solaris.

## readr 0.2.0

CRAN release: 2015-10-19

### Internationalisation

readr now has a strategy for dealing with settings that vary from place
to place: locales. The default locale is still US centric (because R
itself is), but you can now easily override the default timezone,
decimal separator, grouping mark, day & month names, date format, and
encoding. This has lead to a number of changes:

- [`read_csv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
  [`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
  [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md),
  [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md),
  [`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md),
  [`read_file()`](https://readr.tidyverse.org/dev/reference/read_file.md),
  [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md),
  [`parse_vector()`](https://readr.tidyverse.org/dev/reference/parse_vector.md)
  all gain a `locale` argument.

- [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  controls all the input settings that vary from place-to-place.

- `col_euro_double()` and `parse_euro_double()` have been deprecated.
  Use the `decimal_mark` parameter to
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  instead.

- The default encoding is now UTF-8. To load files that are not in
  UTF-8, set the `encoding` parameter of the
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  ([\#40](https://github.com/tidyverse/readr/issues/40)). New
  [`guess_encoding()`](https://readr.tidyverse.org/dev/reference/encoding.md)
  function uses stringi to help you figure out the encoding of a file.

- [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  and
  [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  with `%B` and `%b` use the month names (full and abbreviate) defined
  in the locale
  ([\#242](https://github.com/tidyverse/readr/issues/242)). They also
  inherit the tz from the locale, rather than using an explicit `tz`
  parameter.

See
[`vignette("locales")`](https://readr.tidyverse.org/dev/articles/locales.md)
for more details.

### File parsing improvements

- [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md) lets you
  pick the default column type for columns not otherwise explicitly
  named ([\#148](https://github.com/tidyverse/readr/issues/148)). You
  can refer to parsers either with their full name
  (e.g. [`col_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md))
  or their one letter abbreviation (e.g. `c`).

- [`cols_only()`](https://readr.tidyverse.org/dev/reference/cols.md)
  allows you to load only named columns. You can also choose to override
  the default column type in
  [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md)
  ([\#72](https://github.com/tidyverse/readr/issues/72)).

- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  is now much more careful with new lines. If a line is too short,
  you’ll get a warning instead of a silent mistake
  ([\#166](https://github.com/tidyverse/readr/issues/166),
  [\#254](https://github.com/tidyverse/readr/issues/254)). Additionally,
  the last column can now be ragged: the width of the last field is
  silently extended until it hits the next line break
  ([\#146](https://github.com/tidyverse/readr/issues/146)). This appears
  to be a common feature of “fixed” width files in the wild.

- In
  [`read_csv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
  [`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
  [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  etc:

  - `comment` argument allows you to ignore comments
    ([\#68](https://github.com/tidyverse/readr/issues/68)).

  - `trim_ws` argument controls whether leading and trailing whitespace
    is removed. It defaults to `TRUE`
    ([\#137](https://github.com/tidyverse/readr/issues/137)).

  - Specifying the wrong number of column names, or having rows with an
    unexpected number of columns, generates a warning, rather than an
    error ([\#189](https://github.com/tidyverse/readr/issues/189)).

  - Multiple NA values can be specified by passing a character vector to
    `na` ([\#125](https://github.com/tidyverse/readr/issues/125)). The
    default has been changed to `na = c("", "NA")`. Specifying `na = ""`
    now works as expected with character columns
    ([\#114](https://github.com/tidyverse/readr/issues/114)).

### Column parsing improvements

Readr gains
[`vignette("column-types")`](https://readr.tidyverse.org/dev/articles/column-types.md)
which describes how the defaults work and how to override them
([\#122](https://github.com/tidyverse/readr/issues/122)).

- [`parse_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  gains better support for embedded nulls: any characters after the
  first null are dropped with a warning
  ([\#202](https://github.com/tidyverse/readr/issues/202)).

- [`parse_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  and
  [`parse_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  no longer silently ignore trailing letters after the number
  ([\#221](https://github.com/tidyverse/readr/issues/221)).

- New
  [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  and
  [`col_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  allows you to parse times (hours, minutes, seconds) into number of
  seconds since midnight. If the format is omitted, it uses a flexible
  parser that looks for hours, then optional colon, then minutes, then
  optional colon, then optional seconds, then optional am/pm
  ([\#249](https://github.com/tidyverse/readr/issues/249)).

- [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  and
  [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md):

  - [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
    no longer incorrectly reads partial dates (e.g. 19, 1900, 1900-01)
    ([\#136](https://github.com/tidyverse/readr/issues/136)). These
    triggered common false positives and after re-reading the ISO8601
    spec, I believe they actually refer to periods of time, and should
    not be translated in to a specific instant
    ([\#228](https://github.com/tidyverse/readr/issues/228)).

  - Compound formats “%D”, “%F”, “%R”, “%X”, “%T”, “%x” are now parsed
    correctly, instead of using the ISO8601 parser
    ([\#178](https://github.com/tidyverse/readr/issues/178),
    [@kmillar](https://github.com/kmillar)).

  - “%.” now requires a non-digit. New “%+” skips one or more
    non-digits.

  - You can now use `%p` to refer to AM/PM (and am/pm)
    ([\#126](https://github.com/tidyverse/readr/issues/126)).

  - `%b` and `%B` formats (month and abbreviated month name) ignore case
    when matching
    ([\#219](https://github.com/tidyverse/readr/issues/219)).

  - Local (non-UTC) times with and without daylight savings are now
    parsed correctly
    ([\#120](https://github.com/tidyverse/readr/issues/120),
    [@andres-s](https://github.com/andres-s)).

- [`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  is a somewhat flexible numeric parser designed to read currencies and
  percentages. It only reads the first number from a string (using the
  grouping mark defined by the locale).

- `parse_numeric()` has been deprecated because the name is confusing -
  it’s a flexible number parser, not a parser of “numerics”, as R
  collectively calls doubles and integers. Use
  [`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  instead.

As well as improvements to the parser, I’ve also made a number of tweaks
to the heuristics that readr uses to guess column types:

- New
  [`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  and
  [`col_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  to explicitly guess column type.

- Bumped up row inspection for column typing guessing from 100 to 1000.

- The heuristics for guessing
  [`col_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  and
  [`col_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  are stricter. Numbers with leading zeros now default to being parsed
  as text, rather than as integers/doubles
  ([\#266](https://github.com/tidyverse/readr/issues/266)).

- A column is guessed as
  [`col_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  only if it parses as a regular number when you ignoring the grouping
  marks.

### Minor improvements and bug fixes

- Now use R’s platform independent `iconv` wrapper, thanks to BDR
  ([\#149](https://github.com/tidyverse/readr/issues/149)).

- Pathological zero row inputs (due to empty input, `skip` or `n_max`)
  now return zero row data frames
  ([\#119](https://github.com/tidyverse/readr/issues/119)).

- When guessing field types, and there’s no information to go on, use
  character instead of logical
  ([\#124](https://github.com/tidyverse/readr/issues/124),
  [\#128](https://github.com/tidyverse/readr/issues/128)).

- Concise `col_types` specification now understands `?` (guess) and `-`
  (skip) ([\#188](https://github.com/tidyverse/readr/issues/188)).

- [`count_fields()`](https://readr.tidyverse.org/dev/reference/count_fields.md)
  starts counting from 1, not 0
  ([\#200](https://github.com/tidyverse/readr/issues/200)).

- [`format_csv()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  and
  [`format_delim()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  make it easy to render a csv or delimited file into a string.

- [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  now works correctly when `col_names` supplied
  ([\#186](https://github.com/tidyverse/readr/issues/186),
  [\#222](https://github.com/tidyverse/readr/issues/222)).

- `parse_*()` gains a `na` argument that allows you to specify which
  values should be converted to missing.

- [`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  now reports column names rather than column numbers
  ([\#143](https://github.com/tidyverse/readr/issues/143)). Whenever
  there is a problem, the first five problems are printing out in a
  warning message, so you can more easily see what’s wrong.

- `read_*()` throws a warning instead of an error is `col_types`
  specifies a non-existent column
  ([\#145](https://github.com/tidyverse/readr/issues/145),
  [@alyst](https://github.com/alyst)).

- `read_*()` can read from a remote gz compressed file
  ([\#163](https://github.com/tidyverse/readr/issues/163)).

- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  defaults to `escape_backslash = FALSE` and `escape_double = TRUE` for
  consistency. `n_max` also affects the number of rows read to guess the
  column types ([\#224](https://github.com/tidyverse/readr/issues/224)).

- [`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  gains a progress bar. It now also correctly checks for interrupts
  every 500,000 lines so you can interrupt long running jobs. It also
  correctly estimates the number of lines in the file, considerably
  speeding up the reading of large files (60s -\> 15s for a 1.5 Gb
  file).

- [`read_lines_raw()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  allows you to read a file into a list of raw vectors, one element for
  each line.

- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  gains `NA` and `trim_ws` arguments, and removes missing values before
  determining column types.

- [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
  and
  [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  all invisibly return their input so you can use them in a pipe
  ([\#290](https://github.com/tidyverse/readr/issues/290)).

- [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  generalises
  [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  to write any delimited format
  ([\#135](https://github.com/tidyverse/readr/issues/135)).
  [`write_tsv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  is a helpful wrapper for tab separated files.

  - Quotes are only used when they’re needed
    ([\#116](https://github.com/tidyverse/readr/issues/116)): when the
    string contains a quote, the delimiter, a new line or NA.

  - Double vectors are saved using same amount of precision as
    [`as.character()`](https://rdrr.io/r/base/character.html)
    ([\#117](https://github.com/tidyverse/readr/issues/117)).

  - New `na` argument that specifies how missing values should be
    written ([\#187](https://github.com/tidyverse/readr/issues/187))

  - POSIXt vectors are saved in a ISO8601 compatible format
    ([\#134](https://github.com/tidyverse/readr/issues/134)).

  - No longer fails silently if it can’t open the target for writing
    ([\#193](https://github.com/tidyverse/readr/issues/193),
    [\#172](https://github.com/tidyverse/readr/issues/172)).

- [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  and
  [`read_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  wrap around [`readRDS()`](https://rdrr.io/r/base/readRDS.html) and
  [`saveRDS()`](https://rdrr.io/r/base/readRDS.html), defaulting to no
  compression ([\#140](https://github.com/tidyverse/readr/issues/140),
  [@nicolasCoutin](https://github.com/nicolasCoutin)).

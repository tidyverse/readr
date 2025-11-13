# Package index

## Read rectangular files

These functions parse rectangular files (like csv or fixed-width format)
into tibbles. They specify the overall structure of the file, and how
each line is divided up into fields.

- [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  [`read_csv()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  [`read_csv2()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  [`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  : Read a delimited file (including CSV and TSV) into a tibble
- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  [`fwf_widths()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  [`fwf_positions()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  [`fwf_cols()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  : Read a fixed width file into a tibble
- [`read_log()`](https://readr.tidyverse.org/dev/reference/read_log.md)
  : Read common/combined log file into a tibble
- [`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md)
  : Read whitespace-separated columns into a tibble

## Column specification

The column specification describes how each column is parsed from a
character vector in to a more specific data type. readr does make an
educated guess about the type of each column, but you’ll need override
those guesses when it gets them wrong.

- [`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  [`stop_for_problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
  : Retrieve parsing problems
- [`cols()`](https://readr.tidyverse.org/dev/reference/cols.md)
  [`cols_only()`](https://readr.tidyverse.org/dev/reference/cols.md) :
  Create column specification
- [`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md)
  [`spec()`](https://readr.tidyverse.org/dev/reference/spec.md) :
  Examine the column specifications for a data frame
- [`spec_delim()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
  [`spec_csv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
  [`spec_csv2()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
  [`spec_tsv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
  [`spec_table()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
  : Generate a column specification

## Column parsers

Column parsers define how a single column is parsed, or how to parse a
single vector. Each parser comes in two forms: `parse_xxx()` which is
used to parse vectors that already exist in R and `col_xxx()` which is
used to parse vectors as they are loaded by a `read_xxx()` function.

- [`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`parse_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`parse_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`parse_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`col_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`col_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`col_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  [`col_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  : Parse logicals, integers, and reals
- [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  [`col_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  [`col_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  [`col_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  : Parse date/times
- [`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  [`col_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
  : Parse factors
- [`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  [`col_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  [`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  : Parse using the "best" type
- [`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  [`col_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  : Parse numbers, flexibly
- [`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md)
  : Skip a column

## Locale controls

The “locale” controls all options that vary from country-to-country or
language-to-language. This includes things like the character used as
the decimal mark, the names of days of the week, and the encoding. See
[`vignette("locales")`](https://readr.tidyverse.org/dev/articles/locales.md)
for more details.

- [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  [`default_locale()`](https://readr.tidyverse.org/dev/reference/locale.md)
  : Create locales
- [`date_names()`](https://readr.tidyverse.org/dev/reference/date_names.md)
  [`date_names_lang()`](https://readr.tidyverse.org/dev/reference/date_names.md)
  [`date_names_langs()`](https://readr.tidyverse.org/dev/reference/date_names.md)
  : Create or retrieve date names

## Write rectangular files

Despite its name, readr also provides a number of functions to **write**
data frames to disk, or to convert them to in-memory strings.

- [`format_delim()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  [`format_csv()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  [`format_csv2()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  [`format_tsv()`](https://readr.tidyverse.org/dev/reference/format_delim.md)
  : Convert a data frame to a delimited string
- [`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  [`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  [`write_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  [`write_excel_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  [`write_excel_csv2()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  [`write_tsv()`](https://readr.tidyverse.org/dev/reference/write_delim.md)
  : Write a data frame to a delimited file

## Readr editions

readr supports two editions of parser. Version one is a single threaded
eager parser that readr used by default from its first release to
version 1.4.0. Version two is a multi-threaded lazy parser used by
default from readr 2.0.0 onwards.

- [`with_edition()`](https://readr.tidyverse.org/dev/reference/with_edition.md)
  [`local_edition()`](https://readr.tidyverse.org/dev/reference/with_edition.md)
  : Temporarily change the active readr edition
- [`edition_get()`](https://readr.tidyverse.org/dev/reference/edition_get.md)
  : Retrieve the currently active edition

## Read non-rectangular files

These functions parse non-rectangular files (like csv or fixed-width
format) into long (so-called melted) format. They specify the overall
structure of the file, and how each line is divided up into fields.

- [`melt_delim()`](https://readr.tidyverse.org/dev/reference/melt_delim.md)
  [`melt_csv()`](https://readr.tidyverse.org/dev/reference/melt_delim.md)
  [`melt_csv2()`](https://readr.tidyverse.org/dev/reference/melt_delim.md)
  [`melt_tsv()`](https://readr.tidyverse.org/dev/reference/melt_delim.md)
  **\[superseded\]** : Return melted data for each token in a delimited
  file (including csv & tsv)
- [`melt_fwf()`](https://readr.tidyverse.org/dev/reference/melt_fwf.md)
  **\[superseded\]** : Return melted data for each token in a fixed
  width file
- [`melt_table()`](https://readr.tidyverse.org/dev/reference/melt_table.md)
  [`melt_table2()`](https://readr.tidyverse.org/dev/reference/melt_table.md)
  **\[superseded\]** : Return melted data for each token in a
  whitespace-separated file

## Low-level IO and debugging tools

These functions can be used with non-rectangular files, binary data, and
to help debug rectangular files that fail to parse.

- [`read_file()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  [`read_file_raw()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  [`write_file()`](https://readr.tidyverse.org/dev/reference/read_file.md)
  : Read/write a complete file
- [`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  [`read_lines_raw()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  [`write_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md)
  : Read/write lines to/from a file
- [`read_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  [`write_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md)
  : Read/write RDS files.
- [`read_builtin()`](https://readr.tidyverse.org/dev/reference/read_builtin.md)
  : Read built-in object from package
- [`count_fields()`](https://readr.tidyverse.org/dev/reference/count_fields.md)
  : Count the number of fields in each line of a file
- [`guess_encoding()`](https://readr.tidyverse.org/dev/reference/encoding.md)
  : Guess encoding of file
- [`type_convert()`](https://readr.tidyverse.org/dev/reference/type_convert.md)
  : Re-convert character columns in existing data frame
- [`readr_example()`](https://readr.tidyverse.org/dev/reference/readr_example.md)
  : Get path to readr example
- [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  : Returns values from the clipboard
- [`show_progress()`](https://readr.tidyverse.org/dev/reference/show_progress.md)
  : Determine whether progress bars should be shown
- [`readr_threads()`](https://readr.tidyverse.org/dev/reference/readr_threads.md)
  : Determine how many threads readr should use when processing
- [`should_show_types()`](https://readr.tidyverse.org/dev/reference/should_show_types.md)
  : Determine whether column types should be shown
- [`should_read_lazy()`](https://readr.tidyverse.org/dev/reference/should_read_lazy.md)
  : Determine whether to read a file lazily

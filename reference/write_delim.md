# Write a data frame to a delimited file

The `write_*()` family of functions are an improvement to analogous
function such as
[`write.csv()`](https://rdrr.io/r/utils/write.table.html) because they
are approximately twice as fast. Unlike
[`write.csv()`](https://rdrr.io/r/utils/write.table.html), these
functions do not include row names as a column in the written file. A
generic function,
[`output_column()`](https://readr.tidyverse.org/reference/output_column.md),
is applied to each variable to coerce columns to suitable output.

## Usage

``` r
write_delim(
  x,
  file,
  delim = " ",
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)

write_csv(
  x,
  file,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)

write_csv2(
  x,
  file,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)

write_excel_csv(
  x,
  file,
  na = "NA",
  append = FALSE,
  col_names = !append,
  delim = ",",
  quote = "all",
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)

write_excel_csv2(
  x,
  file,
  na = "NA",
  append = FALSE,
  col_names = !append,
  delim = ";",
  quote = "all",
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)

write_tsv(
  x,
  file,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = "none",
  escape = c("double", "backslash", "none"),
  eol = "\n",
  num_threads = readr_threads(),
  progress = show_progress(),
  path = deprecated(),
  quote_escape = deprecated()
)
```

## Arguments

- x:

  A data frame or tibble to write to disk.

- file:

  File or connection to write to.

- delim:

  Delimiter used to separate values. Defaults to `" "` for
  `write_delim()`, `","` for `write_excel_csv()` and `";"` for
  `write_excel_csv2()`. Must be a single character.

- na:

  String used for missing values. Defaults to NA. Missing values will
  never be quoted; strings with the same value as `na` will always be
  quoted.

- append:

  If `FALSE`, will overwrite existing file. If `TRUE`, will append to
  existing file. In both cases, if the file does not exist a new file is
  created.

- col_names:

  If `FALSE`, column names will not be included at the top of the file.
  If `TRUE`, column names will be included. If not specified,
  `col_names` will take the opposite value given to `append`.

- quote:

  How to handle fields which contain characters that need to be quoted.

  - `needed` - Values are only quoted if needed: if they contain a
    delimiter, quote, or newline.

  - `all` - Quote all fields.

  - `none` - Never quote fields.

- escape:

  The type of escape to use when quotes are in the data.

  - `double` - quotes are escaped by doubling them.

  - `backslash` - quotes are escaped by a preceding backslash.

  - `none` - quotes are not escaped.

- eol:

  The end of line character to use. Most commonly either `"\n"` for Unix
  style newlines, or `"\r\n"` for Windows style newlines.

- num_threads:

  Number of threads to use when reading and materializing vectors. If
  your data contains newlines within fields the parser will
  automatically be forced to use a single thread only.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The display is
  updated every 50,000 values and will only display if estimated reading
  time is 5 seconds or more. The automatic progress bar can be disabled
  by setting option `readr.show_progress` to `FALSE`.

- path:

  **\[deprecated\]** Use the `file` argument instead.

- quote_escape:

  **\[deprecated\]** Use the `escape` argument instead.

## Value

`write_*()` returns the input `x` invisibly.

## Output

Factors are coerced to character. Doubles are formatted to a decimal
string using the grisu3 algorithm. `POSIXct` values are formatted as
ISO8601 with a UTC timezone *Note: `POSIXct` objects in local or non-UTC
timezones will be converted to UTC time before writing.*

All columns are encoded as UTF-8. `write_excel_csv()` and
`write_excel_csv2()` also include a [UTF-8 Byte order
mark](https://en.wikipedia.org/wiki/Byte_order_mark) which indicates to
Excel the csv is UTF-8 encoded.

`write_excel_csv2()` and `write_csv2` were created to allow users with
different locale settings to save .csv files using their default
settings (e.g. `;` as the column separator and `,` as the decimal
separator). This is common in some European countries.

Values are only quoted if they contain a comma, quote or newline.

The `write_*()` functions will automatically compress outputs if an
appropriate extension is given. Three extensions are currently
supported: `.gz` for gzip compression, `.bz2` for bzip2 compression and
`.xz` for lzma compression. See the examples for more information.

## References

Florian Loitsch, Printing Floating-Point Numbers Quickly and Accurately
with Integers, PLDI '10,
<http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf>

## Examples

``` r
# If only a file name is specified, write_()* will write
# the file to the current working directory.
write_csv(mtcars, "mtcars.csv")
write_tsv(mtcars, "mtcars.tsv")

# If you add an extension to the file name, write_()* will
# automatically compress the output.
write_tsv(mtcars, "mtcars.tsv.gz")
write_tsv(mtcars, "mtcars.tsv.bz2")
write_tsv(mtcars, "mtcars.tsv.xz")
```

# Return melted data for each token in a whitespace-separated file

**\[superseded\]** This function has been superseded in readr and moved
to [the meltr package](https://r-lib.github.io/meltr/).

For certain non-rectangular data formats, it can be useful to parse the
data into a melted format where each row represents a single token.

`melt_table()` and `melt_table2()` are designed to read the type of
textual data where each column is separated by one (or more) columns of
space.

`melt_table2()` allows any number of whitespace characters between
columns, and the lines can be of different lengths.

`melt_table()` is more strict, each line must be the same length, and
each field is in the same position in every line. It first finds empty
columns and then parses like a fixed width file.

## Usage

``` r
melt_table(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  comment = "",
  skip_empty_rows = FALSE
)

melt_table2(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  comment = "",
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

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

## See also

[`melt_fwf()`](https://readr.tidyverse.org/reference/melt_fwf.md) to
melt fixed width files where each column is not separated by whitespace.
[`melt_fwf()`](https://readr.tidyverse.org/reference/melt_fwf.md) is
also useful for reading tabular data with non-standard formatting.
[`read_table()`](https://readr.tidyverse.org/reference/read_table.md) is
the conventional way to read tabular data from whitespace-separated
files.

## Examples

``` r
fwf <- readr_example("fwf-sample.txt")
writeLines(read_lines(fwf))
#> John Smith          WA        418-Y11-4111
#> Mary Hartford       CA        319-Z19-4341
#> Evan Nolan          IL        219-532-c301
melt_table(fwf)
#> Warning: `melt_table()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_table()` instead
#> # A tibble: 12 × 4
#>      row   col data_type value       
#>    <dbl> <dbl> <chr>     <chr>       
#>  1     1     1 character John        
#>  2     1     2 character Smith       
#>  3     1     3 character WA          
#>  4     1     4 character 418-Y11-4111
#>  5     2     1 character Mary        
#>  6     2     2 character Hartford    
#>  7     2     3 character CA          
#>  8     2     4 character 319-Z19-4341
#>  9     3     1 character Evan        
#> 10     3     2 character Nolan       
#> 11     3     3 character IL          
#> 12     3     4 character 219-532-c301

ws <- readr_example("whitespace-sample.txt")
writeLines(read_lines(ws))
#> first last state phone
#> John Smith WA 418-Y11-4111
#> Mary Hartford CA 319-Z19-4341
#> Evan Nolan IL 219-532-c301
melt_table2(ws)
#> Warning: `melt_table2()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_table2()` instead
#> # A tibble: 16 × 4
#>      row   col data_type value       
#>    <dbl> <dbl> <chr>     <chr>       
#>  1     1     1 character first       
#>  2     1     2 character last        
#>  3     1     3 character state       
#>  4     1     4 character phone       
#>  5     2     1 character John        
#>  6     2     2 character Smith       
#>  7     2     3 character WA          
#>  8     2     4 character 418-Y11-4111
#>  9     3     1 character Mary        
#> 10     3     2 character Hartford    
#> 11     3     3 character CA          
#> 12     3     4 character 319-Z19-4341
#> 13     4     1 character Evan        
#> 14     4     2 character Nolan       
#> 15     4     3 character IL          
#> 16     4     4 character 219-532-c301
```

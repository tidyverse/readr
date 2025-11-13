# Return melted data for each token in a fixed width file

**\[superseded\]** This function has been superseded in readr and moved
to [the meltr package](https://r-lib.github.io/meltr/).

## Usage

``` r
melt_fwf(
  file,
  col_positions,
  locale = default_locale(),
  na = c("", "NA"),
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
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
  [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  will read from the system clipboard.

- col_positions:

  Column positions, as created by
  [`fwf_empty()`](https://readr.tidyverse.org/dev/reference/read_fwf.md),
  [`fwf_widths()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  or
  [`fwf_positions()`](https://readr.tidyverse.org/dev/reference/read_fwf.md).
  To read in only selected fields, use
  [`fwf_positions()`](https://readr.tidyverse.org/dev/reference/read_fwf.md).
  If the width of the last column is variable (a ragged fwf file),
  supply the last end position as NA.

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

For certain non-rectangular data formats, it can be useful to parse the
data into a melted format where each row represents a single token.

`melt_fwf()` parses each token of a fixed width file into a single row,
but it still requires that each field is in the same in every row of the
source file.

## See also

[`melt_table()`](https://readr.tidyverse.org/dev/reference/melt_table.md)
to melt fixed width files where each column is separated by whitespace,
and
[`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
for the conventional way to read rectangular data from fixed width
files.

## Examples

``` r
fwf_sample <- readr_example("fwf-sample.txt")
cat(read_lines(fwf_sample))
#> John Smith          WA        418-Y11-4111 Mary Hartford       CA        319-Z19-4341 Evan Nolan          IL        219-532-c301

# You can specify column positions in several ways:
# 1. Guess based on position of empty columns
melt_fwf(fwf_sample, fwf_empty(fwf_sample, col_names = c("first", "last", "state", "ssn")))
#> Warning: `melt_fwf()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_fwf()` instead
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
# 2. A vector of field widths
melt_fwf(fwf_sample, fwf_widths(c(20, 10, 12), c("name", "state", "ssn")))
#> # A tibble: 9 × 4
#>     row   col data_type value        
#>   <dbl> <dbl> <chr>     <chr>        
#> 1     1     1 character John Smith   
#> 2     1     2 character WA           
#> 3     1     3 character 418-Y11-4111 
#> 4     2     1 character Mary Hartford
#> 5     2     2 character CA           
#> 6     2     3 character 319-Z19-4341 
#> 7     3     1 character Evan Nolan   
#> 8     3     2 character IL           
#> 9     3     3 character 219-532-c301 
# 3. Paired vectors of start and end positions
melt_fwf(fwf_sample, fwf_positions(c(1, 30), c(10, 42), c("name", "ssn")))
#> # A tibble: 6 × 4
#>     row   col data_type value       
#>   <dbl> <dbl> <chr>     <chr>       
#> 1     1     1 character John Smith  
#> 2     1     2 character 418-Y11-4111
#> 3     2     1 character Mary Hartf  
#> 4     2     2 character 319-Z19-4341
#> 5     3     1 character Evan Nolan  
#> 6     3     2 character 219-532-c301
# 4. Named arguments with start and end positions
melt_fwf(fwf_sample, fwf_cols(name = c(1, 10), ssn = c(30, 42)))
#> # A tibble: 6 × 4
#>     row   col data_type value       
#>   <dbl> <dbl> <chr>     <chr>       
#> 1     1     1 character John Smith  
#> 2     1     2 character 418-Y11-4111
#> 3     2     1 character Mary Hartf  
#> 4     2     2 character 319-Z19-4341
#> 5     3     1 character Evan Nolan  
#> 6     3     2 character 219-532-c301
# 5. Named arguments with column widths
melt_fwf(fwf_sample, fwf_cols(name = 20, state = 10, ssn = 12))
#> # A tibble: 9 × 4
#>     row   col data_type value        
#>   <dbl> <dbl> <chr>     <chr>        
#> 1     1     1 character John Smith   
#> 2     1     2 character WA           
#> 3     1     3 character 418-Y11-4111 
#> 4     2     1 character Mary Hartford
#> 5     2     2 character CA           
#> 6     2     3 character 319-Z19-4341 
#> 7     3     1 character Evan Nolan   
#> 8     3     2 character IL           
#> 9     3     3 character 219-532-c301 
```

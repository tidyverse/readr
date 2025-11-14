# Return melted data for each token in a delimited file (including csv & tsv)

**\[superseded\]** This function has been superseded in readr and moved
to [the meltr package](https://r-lib.github.io/meltr/).

## Usage

``` r
melt_delim(
  file,
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
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_csv(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_csv2(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
)

melt_tsv(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
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
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
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

## Value

A
[`tibble::tibble()`](https://tibble.tidyverse.org/reference/tibble.html)
of four columns:

- `row`, the row that the token comes from in the original file

- `col`, the column that the token comes from in the original file

- `data_type`, the data type of the token, e.g. `"integer"`,
  `"character"`, `"date"`, guessed in a similar way to the
  [`guess_parser()`](https://readr.tidyverse.org/reference/parse_guess.md)
  function.

- `value`, the token itself as a character string, unchanged from its
  representation in the original file.

If there are parsing problems, a warning tells you how many, and you can
retrieve the details with
[`problems()`](https://readr.tidyverse.org/reference/problems.md).

## Details

For certain non-rectangular data formats, it can be useful to parse the
data into a melted format where each row represents a single token.

`melt_csv()` and `melt_tsv()` are special cases of the general
`melt_delim()`. They're useful for reading the most common types of flat
file data, comma separated values and tab separated values,
respectively. `melt_csv2()` uses `;` for the field separator and `,` for
the decimal point. This is common in some European countries.

## See also

[`read_delim()`](https://readr.tidyverse.org/reference/read_delim.md)
for the conventional way to read rectangular data from delimited files.

## Examples

``` r
# Input sources -------------------------------------------------------------
# Read from a path
melt_csv(readr_example("mtcars.csv"))
#> Warning: `melt_csv()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_csv()` instead
#> # A tibble: 363 × 4
#>      row   col data_type value
#>    <dbl> <dbl> <chr>     <chr>
#>  1     1     1 character mpg  
#>  2     1     2 character cyl  
#>  3     1     3 character disp 
#>  4     1     4 character hp   
#>  5     1     5 character drat 
#>  6     1     6 character wt   
#>  7     1     7 character qsec 
#>  8     1     8 character vs   
#>  9     1     9 character am   
#> 10     1    10 character gear 
#> # ℹ 353 more rows
melt_csv(readr_example("mtcars.csv.zip"))
#> # A tibble: 363 × 4
#>      row   col data_type value
#>    <dbl> <dbl> <chr>     <chr>
#>  1     1     1 character mpg  
#>  2     1     2 character cyl  
#>  3     1     3 character disp 
#>  4     1     4 character hp   
#>  5     1     5 character drat 
#>  6     1     6 character wt   
#>  7     1     7 character qsec 
#>  8     1     8 character vs   
#>  9     1     9 character am   
#> 10     1    10 character gear 
#> # ℹ 353 more rows
melt_csv(readr_example("mtcars.csv.bz2"))
#> # A tibble: 363 × 4
#>      row   col data_type value
#>    <dbl> <dbl> <chr>     <chr>
#>  1     1     1 character mpg  
#>  2     1     2 character cyl  
#>  3     1     3 character disp 
#>  4     1     4 character hp   
#>  5     1     5 character drat 
#>  6     1     6 character wt   
#>  7     1     7 character qsec 
#>  8     1     8 character vs   
#>  9     1     9 character am   
#> 10     1    10 character gear 
#> # ℹ 353 more rows
if (FALSE) { # \dontrun{
melt_csv("https://github.com/tidyverse/readr/raw/main/inst/extdata/mtcars.csv")
} # }

# Or directly from a string (must contain a newline)
melt_csv("x,y\n1,2\n3,4")
#> # A tibble: 6 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character x    
#> 2     1     2 character y    
#> 3     2     1 integer   1    
#> 4     2     2 integer   2    
#> 5     3     1 integer   3    
#> 6     3     2 integer   4    

# To import empty cells as 'empty' rather than `NA`
melt_csv("x,y\n,NA,\"\",''", na = "NA")
#> # A tibble: 6 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character "x"  
#> 2     1     2 character "y"  
#> 3     2     1 empty     ""   
#> 4     2     2 missing    NA  
#> 5     2     3 empty     ""   
#> 6     2     4 character "''" 

# File types ----------------------------------------------------------------
melt_csv("a,b\n1.0,2.0")
#> # A tibble: 4 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character a    
#> 2     1     2 character b    
#> 3     2     1 double    1.0  
#> 4     2     2 double    2.0  
melt_csv2("a;b\n1,0;2,0")
#> Warning: `melt_csv2()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_csv2()` instead
#> ℹ Using "','" as decimal and "'.'" as grouping mark. Use `read_delim()` for more control.
#> # A tibble: 4 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character a    
#> 2     1     2 character b    
#> 3     2     1 double    1,0  
#> 4     2     2 double    2,0  
melt_tsv("a\tb\n1.0\t2.0")
#> Warning: `melt_tsv()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_tsv()` instead
#> # A tibble: 4 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character a    
#> 2     1     2 character b    
#> 3     2     1 double    1.0  
#> 4     2     2 double    2.0  
melt_delim("a|b\n1.0|2.0", delim = "|")
#> Warning: `melt_delim()` was deprecated in readr 2.0.0.
#> ℹ Please use `meltr::melt_delim()` instead
#> # A tibble: 4 × 4
#>     row   col data_type value
#>   <dbl> <dbl> <chr>     <chr>
#> 1     1     1 character a    
#> 2     1     2 character b    
#> 3     2     1 double    1.0  
#> 4     2     2 double    2.0  
```

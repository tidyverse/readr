# Create a source object.

Create a source object.

## Usage

``` r
datasource(
  file,
  skip = 0,
  skip_empty_rows = FALSE,
  comment = "",
  skip_quote = TRUE
)
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector).

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  uncompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote `.gz` files can
  also be automatically downloaded and decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, wrap the input with
  [`I()`](https://rdrr.io/r/base/AsIs.html).

  Using a value of
  [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  will read from the system clipboard.

- skip:

  Number of lines to skip before reading data.

## Examples

``` r
# Literal csv
datasource("a,b,c\n1,2,3")
#> [[1]]
#> [1] "a,b,c\n1,2,3"
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> attr(,"class")
#> [1] "source_string" "source"       
datasource(charToRaw("a,b,c\n1,2,3"))
#> [[1]]
#>  [1] 61 2c 62 2c 63 0a 31 2c 32 2c 33
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> attr(,"class")
#> [1] "source_raw" "source"    

# Strings
datasource(readr_example("mtcars.csv"))
#> [[1]]
#> [1] "/home/runner/work/_temp/Library/readr/extdata/mtcars.csv"
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> attr(,"class")
#> [1] "source_file" "source"     
datasource(readr_example("mtcars.csv.bz2"))
#> [[1]]
#> [1] "/tmp/RtmpxekGrG/file19d22312a864"
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> $env
#> <environment: 0x55fb8813e4d0>
#> 
#> attr(,"class")
#> [1] "source_file" "source"     
datasource(readr_example("mtcars.csv.zip"))
#> [[1]]
#> [1] "/tmp/RtmpxekGrG/file19d2263fb4d1"
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> $env
#> <environment: 0x55fb881b1210>
#> 
#> attr(,"class")
#> [1] "source_file" "source"     
if (FALSE) { # \dontrun{
datasource("https://github.com/tidyverse/readr/raw/main/inst/extdata/mtcars.csv")
} # }

# Connection
con <- rawConnection(charToRaw("abc\n123"))
datasource(con)
#> [[1]]
#> [1] "/tmp/RtmpxekGrG/file19d26b4ab0ac"
#> 
#> $skip
#> [1] 0
#> 
#> $skip_empty_rows
#> [1] FALSE
#> 
#> $comment
#> [1] ""
#> 
#> $skip_quote
#> [1] TRUE
#> 
#> $env
#> <environment: 0x55fb8824ea18>
#> 
#> attr(,"class")
#> [1] "source_file" "source"     
close(con)
```

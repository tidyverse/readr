# Tokenize a file/string.

Turns input into a character vector. Usually the tokenization is done
purely in C++, and never exposed to R (because that requires a copy).
This function is useful for testing, or when a file doesn't parse
correctly and you want to see the underlying tokens.

## Usage

``` r
tokenize(file, tokenizer = tokenizer_csv(), skip = 0, n_max = -1L)
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

- tokenizer:

  A tokenizer specification.

- skip:

  Number of lines to skip before reading data.

- n_max:

  Optionally, maximum number of rows to tokenize.

## Examples

``` r
tokenize("1,2\n3,4,5\n\n6")
#> [[1]]
#> [1] "1" "2"
#> 
#> [[2]]
#> [1] "3" "4" "5"
#> 
#> [[3]]
#> [1] "6"
#> 

# Only tokenize first two lines
tokenize("1,2\n3,4,5\n\n6", n = 2)
#> [[1]]
#> [1] "1" "2"
#> 
#> [[2]]
#> [1] "3" "4" "5"
#> 
```

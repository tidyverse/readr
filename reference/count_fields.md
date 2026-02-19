# Count the number of fields in each line of a file

This is useful for diagnosing problems with functions that fail to parse
correctly.

## Usage

``` r
count_fields(file, tokenizer, skip = 0, n_max = -1L)
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
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
  will read from the system clipboard.

- tokenizer:

  A tokenizer that specifies how to break the `file` up into fields,
  e.g.,
  [`tokenizer_csv()`](https://readr.tidyverse.org/reference/Tokenizers.md),
  [`tokenizer_fwf()`](https://readr.tidyverse.org/reference/Tokenizers.md)

- skip:

  Number of lines to skip before reading data.

- n_max:

  Optionally, maximum number of rows to count fields for.

## Examples

``` r
count_fields(readr_example("mtcars.csv"), tokenizer_csv())
#>  [1] 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
#> [23] 11 11 11 11 11 11 11 11 11 11 11
```

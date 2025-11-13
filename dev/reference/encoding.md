# Guess encoding of file

Uses
[`stringi::stri_enc_detect()`](https://rdrr.io/pkg/stringi/man/stri_enc_detect.html):
see the documentation there for caveats.

## Usage

``` r
guess_encoding(file, n_max = 10000, threshold = 0.2)
```

## Arguments

- file:

  A character string specifying an input as specified in
  [`datasource()`](https://readr.tidyverse.org/dev/reference/datasource.md),
  a raw vector, or a list of raw vectors.

- n_max:

  Number of lines to read. If `n_max` is -1, all lines in file will be
  read.

- threshold:

  Only report guesses above this threshold of certainty.

## Value

A tibble

## Examples

``` r
guess_encoding(readr_example("mtcars.csv"))
#> # A tibble: 1 × 2
#>   encoding confidence
#>   <chr>         <dbl>
#> 1 ASCII             1
guess_encoding(read_lines_raw(readr_example("mtcars.csv")))
#> # A tibble: 1 × 2
#>   encoding confidence
#>   <chr>         <dbl>
#> 1 ASCII             1
guess_encoding(read_file_raw(readr_example("mtcars.csv")))
#> # A tibble: 1 × 2
#>   encoding confidence
#>   <chr>         <dbl>
#> 1 ASCII             1

guess_encoding("a\n\u00b5\u00b5")
#> # A tibble: 1 × 2
#>   encoding confidence
#>   <chr>         <dbl>
#> 1 UTF-8           0.8
```

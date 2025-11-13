# Determine how many threads readr should use when processing

The number of threads returned can be set by

- The global option `readr.num_threads`

- The environment variable `VROOM_THREADS`

- The value of
  [`parallel::detectCores()`](https://rdrr.io/r/parallel/detectCores.html)

## Usage

``` r
readr_threads()
```

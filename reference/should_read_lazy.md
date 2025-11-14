# Determine whether to read a file lazily

This function consults the option `readr.read_lazy` to figure out
whether to do lazy reading or not. If the option is unset, the default
is `FALSE`, meaning readr will read files eagerly, not lazily. If you
want to use this option to express a preference for lazy reading, do
this:

    options(readr.read_lazy = TRUE)

Typically, one would use the option to control lazy reading at the
session, file, or user level. The `lazy` argument of functions like
[`read_csv()`](https://readr.tidyverse.org/reference/read_delim.md) can
be used to control laziness in an individual call.

## Usage

``` r
should_read_lazy()
```

## See also

The blog post ["Eager vs lazy reading in readr
2.1.0"](https://tidyverse.org/blog/2021/11/readr-2-1-0-lazy/) explains
the benefits (and downsides) of lazy reading.

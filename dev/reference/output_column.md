# Preprocess column for output

This is a generic function that applied to each column before it is
saved to disk. It provides a hook for S3 classes that need special
handling.

## Usage

``` r
output_column(x, name)
```

## Arguments

- x:

  A vector

## Examples

``` r
# Most columns are not altered, but POSIXct are converted to ISO8601.
x <- parse_datetime("2016-01-01")
str(output_column(x))
#>  chr "2016-01-01T00:00:00Z"
```

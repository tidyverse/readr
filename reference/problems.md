# Retrieve parsing problems

Readr functions will only throw an error if parsing fails in an
unrecoverable way. However, there are lots of potential problems that
you might want to know about - these are stored in the `problems`
attribute of the output, which you can easily access with this function.
`stop_for_problems()` will throw an error if there are any parsing
problems: this is useful for automated scripts where you want to throw
an error as soon as you encounter a problem.

## Usage

``` r
problems(x = .Last.value)

stop_for_problems(x)
```

## Arguments

- x:

  A data frame (from `read_*()`) or a vector (from `parse_*()`).

## Value

A data frame with one row for each problem and four columns:

- row,col:

  Row and column of problem

- expected:

  What readr expected to find

- actual:

  What it actually got

## Examples

``` r
x <- parse_integer(c("1X", "blah", "3"))
#> Warning: 2 parsing failures.
#> row col               expected actual
#>   1  -- no trailing characters   1X  
#>   2  -- no trailing characters   blah
problems(x)
#> # A tibble: 2 × 4
#>     row   col expected               actual
#>   <int> <int> <chr>                  <chr> 
#> 1     1    NA no trailing characters 1X    
#> 2     2    NA no trailing characters blah  

y <- parse_integer(c("1", "2", "3"))
problems(y)
```

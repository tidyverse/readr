# Callback classes

These classes are used to define callback behaviors.

## Details

- ChunkCallback:

  Callback interface definition, all callback functions should inherit
  from this class.

- SideEffectChunkCallback:

  Callback function that is used only for side effects, no results are
  returned.

- DataFrameCallback:

  Callback function that combines each result together at the end.

- AccumulateCallBack:

  Callback function that accumulates a single result. Requires the
  parameter `acc` to specify the initial value of the accumulator. The
  parameter `acc` is `NULL` by default.

## See also

Other chunked:
[`melt_delim_chunked()`](https://readr.tidyverse.org/reference/melt_delim_chunked.md),
[`read_delim_chunked()`](https://readr.tidyverse.org/reference/read_delim_chunked.md),
[`read_lines_chunked()`](https://readr.tidyverse.org/reference/read_lines_chunked.md)

## Examples

``` r
## If given a regular function it is converted to a SideEffectChunkCallback

# view structure of each chunk
read_lines_chunked(readr_example("mtcars.csv"), str, chunk_size = 5)
#>  chr [1:5] "\"mpg\",\"cyl\",\"disp\",\"hp\",\"drat\",\"wt\",\"qsec\",\"vs\",\"am\",\"gear\",\"carb\"" ...
#>  chr [1:5] "18.7,8,360,175,3.15,3.44,17.02,0,0,3,2" ...
#>  chr [1:5] "19.2,6,167.6,123,3.92,3.44,18.3,1,0,4,4" ...
#>  chr [1:5] "10.4,8,472,205,2.93,5.25,17.98,0,0,3,4" ...
#>  chr [1:5] "33.9,4,71.1,65,4.22,1.835,19.9,1,1,4,1" ...
#>  chr [1:5] "19.2,8,400,175,3.08,3.845,17.05,0,0,3,2" ...
#>  chr [1:3] "19.7,6,145,175,3.62,2.77,15.5,0,1,5,6" ...
#> NULL

# Print starting line of each chunk
f <- function(x, pos) print(pos)
read_lines_chunked(readr_example("mtcars.csv"), SideEffectChunkCallback$new(f), chunk_size = 5)
#> [1] 1
#> [1] 6
#> [1] 11
#> [1] 16
#> [1] 21
#> [1] 26
#> [1] 31
#> NULL

# If combined results are desired you can use the DataFrameCallback

# Cars with 3 gears
f <- function(x, pos) subset(x, gear == 3)
read_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   mpg = col_double(),
#>   cyl = col_double(),
#>   disp = col_double(),
#>   hp = col_double(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_double(),
#>   am = col_double(),
#>   gear = col_double(),
#>   carb = col_double()
#> )
#> # A tibble: 15 × 11
#>      mpg   cyl  disp    hp  drat    wt  qsec    vs    am  gear  carb
#>    <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl> <dbl>
#>  1  21.4     6  258    110  3.08  3.22  19.4     1     0     3     1
#>  2  18.7     8  360    175  3.15  3.44  17.0     0     0     3     2
#>  3  18.1     6  225    105  2.76  3.46  20.2     1     0     3     1
#>  4  14.3     8  360    245  3.21  3.57  15.8     0     0     3     4
#>  5  16.4     8  276.   180  3.07  4.07  17.4     0     0     3     3
#>  6  17.3     8  276.   180  3.07  3.73  17.6     0     0     3     3
#>  7  15.2     8  276.   180  3.07  3.78  18       0     0     3     3
#>  8  10.4     8  472    205  2.93  5.25  18.0     0     0     3     4
#>  9  10.4     8  460    215  3     5.42  17.8     0     0     3     4
#> 10  14.7     8  440    230  3.23  5.34  17.4     0     0     3     4
#> 11  21.5     4  120.    97  3.7   2.46  20.0     1     0     3     1
#> 12  15.5     8  318    150  2.76  3.52  16.9     0     0     3     2
#> 13  15.2     8  304    150  3.15  3.44  17.3     0     0     3     2
#> 14  13.3     8  350    245  3.73  3.84  15.4     0     0     3     4
#> 15  19.2     8  400    175  3.08  3.84  17.0     0     0     3     2

# The ListCallback can be used for more flexible output
f <- function(x, pos) x$mpg[x$hp > 100]
read_csv_chunked(readr_example("mtcars.csv"), ListCallback$new(f), chunk_size = 5)
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   mpg = col_double(),
#>   cyl = col_double(),
#>   disp = col_double(),
#>   hp = col_double(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_double(),
#>   am = col_double(),
#>   gear = col_double(),
#>   carb = col_double()
#> )
#> [[1]]
#> [1] 21.0 21.0 21.4 18.7
#> 
#> [[2]]
#> [1] 18.1 14.3 19.2
#> 
#> [[3]]
#> [1] 17.8 16.4 17.3 15.2 10.4
#> 
#> [[4]]
#> [1] 10.4 14.7
#> 
#> [[5]]
#> [1] 15.5 15.2 13.3 19.2
#> 
#> [[6]]
#> [1] 30.4 15.8 19.7
#> 
#> [[7]]
#> [1] 15.0 21.4
#> 

# The AccumulateCallback accumulates results from each chunk
f <- function(x, pos, acc) sum(x$mpg) + acc
read_csv_chunked(readr_example("mtcars.csv"), AccumulateCallback$new(f, acc = 0), chunk_size = 5)
#> 
#> ── Column specification ───────────────────────────────────────────────
#> cols(
#>   mpg = col_double(),
#>   cyl = col_double(),
#>   disp = col_double(),
#>   hp = col_double(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_double(),
#>   am = col_double(),
#>   gear = col_double(),
#>   carb = col_double()
#> )
#> [1] 642.9
```

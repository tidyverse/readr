# Get path to readr example

readr comes bundled with a number of sample files in its `inst/extdata`
directory. This function make them easy to access

## Usage

``` r
readr_example(file = NULL)
```

## Arguments

- file:

  Name of file. If `NULL`, the example files will be listed.

## Examples

``` r
readr_example()
#>  [1] "challenge.csv"               "chickens.csv"               
#>  [3] "epa78.txt"                   "example.log"                
#>  [5] "fwf-sample.txt"              "massey-rating.txt"          
#>  [7] "mini-gapminder-africa.csv"   "mini-gapminder-americas.csv"
#>  [9] "mini-gapminder-asia.csv"     "mini-gapminder-europe.csv"  
#> [11] "mini-gapminder-oceania.csv"  "mtcars.csv"                 
#> [13] "mtcars.csv.bz2"              "mtcars.csv.zip"             
#> [15] "whitespace-sample.txt"      
readr_example("challenge.csv")
#> [1] "/home/runner/work/_temp/Library/readr/extdata/challenge.csv"
```

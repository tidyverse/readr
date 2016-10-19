
<!-- README.md is generated from README.Rmd. Please edit that file -->
readr <img src="logo.png" align="right" />
==========================================

[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/readr)](http://cran.r-project.org/package=readr) [![Build Status](https://travis-ci.org/tidyverse/readr.png?branch=master)](https://travis-ci.org/tidyverse/readr) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/tidyverse/readr?branch=master&svg=true)](https://ci.appveyor.com/project/tidyverse/readr) [![Coverage Status](http://codecov.io/github/tidyverse/readr/coverage.svg?branch=master)](http://codecov.io/tidyverse/hadley/readr?branch=master)

The goal of readr is to provide a fast and friendly way to read tabular data into R. The most important functions are:

-   Read delimited files: `read_delim()`, `read_csv()`, `read_tsv()`, `read_csv2()`.
-   Read fixed width files: `read_fwf()`, `read_table()`.
-   Read lines: `read_lines()`.
-   Read whole file: `read_file()`.
-   Re-parse existing data frame: `type_convert()`.

Installation
------------

``` r
# The easiest way to get readr is to install the whole tidyverse:
install.packages("tidyverse")

# Alternatively, install just readr:
install.packages("readr")

# Or the the development version from GitHub:
# install.packages("devtools")
devtools::install_github("tidyverse/readr")
```

Usage
-----

``` r
library(readr)

# Read a csv file into a data frame
read_csv(readr_example("mtcars.csv"))
#> Parsed with column specification:
#> cols(
#>   mpg = col_double(),
#>   cyl = col_integer(),
#>   disp = col_double(),
#>   hp = col_integer(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_integer(),
#>   am = col_integer(),
#>   gear = col_integer(),
#>   carb = col_integer()
#> )
#> # A tibble: 32 × 11
#>      mpg   cyl  disp    hp  drat    wt  qsec    vs    am  gear  carb
#>    <dbl> <int> <dbl> <int> <dbl> <dbl> <dbl> <int> <int> <int> <int>
#> 1   21.0     6 160.0   110  3.90 2.620 16.46     0     1     4     4
#> 2   21.0     6 160.0   110  3.90 2.875 17.02     0     1     4     4
#> 3   22.8     4 108.0    93  3.85 2.320 18.61     1     1     4     1
#> 4   21.4     6 258.0   110  3.08 3.215 19.44     1     0     3     1
#> 5   18.7     8 360.0   175  3.15 3.440 17.02     0     0     3     2
#> 6   18.1     6 225.0   105  2.76 3.460 20.22     1     0     3     1
#> 7   14.3     8 360.0   245  3.21 3.570 15.84     0     0     3     4
#> 8   24.4     4 146.7    62  3.69 3.190 20.00     1     0     4     2
#> 9   22.8     4 140.8    95  3.92 3.150 22.90     1     0     4     2
#> 10  19.2     6 167.6   123  3.92 3.440 18.30     1     0     4     4
#> # ... with 22 more rows
```

See `vignette("column-types")` on how readr parses columns, and how you can override the defaults.

Comparison
----------

### To base R

Compared to the corresponding base functions, readr functions:

-   Use a consistent naming scheme for the parameters (e.g. `col_names` and `col_types` not `header` and `colClasses`).

-   Are much faster (up to 10x faster).

-   Have a helpful progress bar if loading is going to take a while.

-   All functions work exactly the same way regardless of the current locale. To override the US-centric defaults, use `locale()`.

### To `fread()`

[data.table](https://github.com/Rdatatable/data.table) has a function similar to `read_csv()` called fread. Compared to fread, readr:

-   Is slower (currently ~1.2-2x slower. If you want absolutely the best performance, use `data.table::fread()`.

-   Readr has a slightly more sophisticated parser, recognising both doubled ("""") and backslash escapes ("""). Readr allows you to read factors and date times directly from disk.

-   `fread()` saves you work by automatically guessing the delimiter, whether or not the file has a header, how many lines to skip by default and more. Readr forces you to supply these parameters.

-   The underlying designs are quite different. Readr is designed to be general, and dealing with new types of rectangular data just requires implementing a new tokenizer. `fread()` is designed to be as fast as possible. `fread()` is pure C, readr is C++ (and Rcpp).

Acknowledgements
----------------

Thanks to:

-   [Joe Cheng](https://github.com/jcheng5) for showing me the beauty of deterministic finite automata for parsing, and for teaching me why I should write a tokenizer.

-   [JJ Allaire](https://github.com/jjallaire) for helping me come up with a design that makes very few copies, and is easy to extend.

-   [Dirk Eddelbuettel](http://dirk.eddelbuettel.com) for coming up with the name!

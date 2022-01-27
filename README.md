
<!-- README.md is generated from README.Rmd. Please edit that file -->

# readr <a href="https://readr.tidyverse.org"><img src="man/figures/logo.png" align="right" height="139" /></a>

<!-- badges: start -->

[![CRAN
status](https://www.r-pkg.org/badges/version/readr)](https://CRAN.R-project.org/package=readr)
[![R-CMD-check](https://github.com/tidyverse/readr/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/tidyverse/readr/actions/workflows/R-CMD-check.yaml)
[![Coverage
Status](https://codecov.io/gh/tidyverse/readr/coverage.svg?branch=main)](https://app.codecov.io/gh/tidyverse/readr?branch=main)
<!-- badges: end -->

## Overview

The goal of readr is to provide a fast and friendly way to read
rectangular data like comma separated (csv) files and tab separated
(tsv) files. It is designed to flexibly parse many types of data found
in the wild, while still cleanly failing when data unexpectedly changes.
If you are new to readr, the best place to start is the [data import
chapter](https://r4ds.had.co.nz/data-import.html) in R for Data Science.

## Installation

``` r
# The easiest way to get readr is to install the whole tidyverse:
install.packages("tidyverse")

# Alternatively, install just readr:
install.packages("readr")

# Or the the development version from GitHub:
# install.packages("devtools")
devtools::install_github("tidyverse/readr")
```

## Cheatsheet

<a href="https://raw.githubusercontent.com/rstudio/cheatsheets/main/data-import.pdf"><img src="https://github.com/rstudio/cheatsheets/raw/main/pngs/thumbnails/data-import-cheatsheet-thumbs.png" height="252"/></a>

## Usage

readr is part of the core tidyverse, so load it with:

``` r
library(tidyverse)
#> ── Attaching packages ─────────────────────────────────────── tidyverse 1.3.1 ──
#> ✓ ggplot2 3.3.5          ✓ purrr   0.3.4     
#> ✓ tibble  3.1.6          ✓ dplyr   1.0.7     
#> ✓ tidyr   1.1.4          ✓ stringr 1.4.0     
#> ✓ readr   2.1.1.9000     ✓ forcats 0.5.1
#> ── Conflicts ────────────────────────────────────────── tidyverse_conflicts() ──
#> x dplyr::filter() masks stats::filter()
#> x dplyr::lag()    masks stats::lag()
```

To accurately read a rectangular dataset with readr you combine two
pieces: a function that parses the overall file, and a column
specification. The column specification describes how each column should
be converted from a character vector to the most appropriate data type.

If column specification is not provided, readr will guess column types.
As always, remember that the best strategy is to provide explicit column
types as any data analysis project matures past the exploratory phase.

`vignette("column-types")` gives more detail on how readr guesses the
column types.

readr supports the following file formats with these `read_` functions:

-   `read_csv()`: comma separated (csv) files
-   `read_tsv()`: tab separated (tsv) files
-   `read_delim()`: general delimited files
-   `read_fwf()`: fixed width files (fwf)
-   `read_table()`: tabular files where columns are separated by
    white-space.
-   `read_log()`: web log files

The following example loads a sample file bundled with readr:

``` r
mtcars <- read_csv(readr_example("mtcars.csv"))
#> Rows: 32 Columns: 11
#> ── Column specification ────────────────────────────────────────────────────────
#> Delimiter: ","
#> dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
```

Note that readr prints the column types. This is useful because it
allows you to check that the columns have been read in as you expect. If
they haven’t, you can use `spec()` to retrieve the column specification
and then copy and paste into a new call with the desired column types:

``` r
spec(mtcars)
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

mtcars <- read_csv(readr_example("mtcars.csv"), col_types = 
  list(
    mpg = col_double(),
    cyl = col_integer(),
    disp = col_double(),
    hp = col_integer(),
    drat = col_double(),
    vs = col_integer(),
    wt = col_double(),
    qsec = col_double(),
    am = col_integer(),
    gear = col_integer(),
    carb = col_integer()
  )
)
```

`vignette("readr")` gives more detail on how readr parses data.

## Editions

readr got a new parsing engine in version 2.0.0 (released July 2021). In
this so-called second edition, readr calls `vroom::vroom()`, by default.
This means, when you call readr you are in effect calling
`vroom::vroom()`.

The parsing engine in readr versions prior to 2.0.0 is now called the
first edition. If you’re using readr \>= 2.0.0, you can still access
first edition parsing via the functions `with_edition()` and
`local_edition()`. And, obviously, if you’re using readr \< 2.0.0, you
will get first edition parsing, by definition, because that’s all there
is.

## Alternatives

There are two main alternatives to readr: base R and data.table’s
`fread()`. The most important differences are discussed below.

### Base R

Compared to the corresponding base functions, readr functions:

-   Use a consistent naming scheme for the parameters (e.g. `col_names`
    and `col_types` not `header` and `colClasses`).

-   Are generally much faster (up to 10x-100x) faster depending on the
    dataset.

-   Leave strings as is by default, and automatically parse common
    date/time formats.

-   Have a helpful progress bar if loading is going to take a while.

-   All functions work exactly the same way regardless of the current
    locale. To override the US-centric defaults, use `locale()`.

### data.table and `fread()`

[data.table](https://github.com/Rdatatable/data.table) has a function
similar to `read_csv()` called fread. Compared to fread, readr
functions:

-   Are sometimes slower, particularly on numeric heavy data.

-   Forces you to supply all parameters, where `fread()` saves you work
    by automatically guessing the delimiter, whether or not the file has
    a header, and how many lines to skip.

## Acknowledgements

Thanks to:

-   [Joe Cheng](https://github.com/jcheng5) for showing me the beauty of
    deterministic finite automata for parsing, and for teaching me why I
    should write a tokenizer.

-   [JJ Allaire](https://github.com/jjallaire) for helping me come up
    with a design that makes very few copies, and is easy to extend.

-   [Dirk Eddelbuettel](http://dirk.eddelbuettel.com) for coming up with
    the name!

## Code of Conduct

Please note that the readr project is released with a [Contributor Code
of Conduct](https://readr.tidyverse.org/CONDUCT.html). By contributing
to this project, you agree to abide by its terms.

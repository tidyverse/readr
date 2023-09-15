
<!-- README.md is generated from README.Rmd. Please edit that file -->

# readr <a href="https://readr.tidyverse.org"><img src="man/figures/logo.png" align="right" height="138" alt = ""/></a>

<!-- badges: start -->

[![CRAN
status](https://www.r-pkg.org/badges/version/readr)](https://CRAN.R-project.org/package=readr)
[![R-CMD-check](https://github.com/tidyverse/readr/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/tidyverse/readr/actions/workflows/R-CMD-check.yaml)
[![Codecov test
coverage](https://codecov.io/gh/tidyverse/readr/branch/main/graph/badge.svg)](https://app.codecov.io/gh/tidyverse/readr?branch=main)
<!-- badges: end -->

## Overview

The goal of readr is to provide a fast and friendly way to read
rectangular data from delimited files, such as comma-separated values
(CSV) and tab-separated values (TSV). It is designed to parse many types
of data found in the wild, while providing an informative problem report
when parsing leads to unexpected results. If you are new to readr, the
best place to start is the [data import
chapter](https://r4ds.hadley.nz/data-import) in R for Data Science.

## Installation

``` r
# The easiest way to get readr is to install the whole tidyverse:
install.packages("tidyverse")

# Alternatively, install just readr:
install.packages("readr")
```

<div class=".pkgdown-devel">

``` r
# Or you can install the development version from GitHub:
# install.packages("pak")
pak::pak("tidyverse/readr")
```

</div>

## Cheatsheet

<a href="https://raw.githubusercontent.com/rstudio/cheatsheets/main/data-import.pdf"><img src="https://github.com/rstudio/cheatsheets/raw/main/pngs/thumbnails/data-import-cheatsheet-thumbs.png" height="252" alt="thumbnail of tidyverse data import cheatsheet"//></a>

## Usage

readr is part of the core tidyverse, so you can load it with:

``` r
library(tidyverse)
#> ── Attaching core tidyverse packages ──────────────────────── tidyverse 2.0.0 ──
#> ✔ dplyr     1.1.3          ✔ readr     2.1.4.9000
#> ✔ forcats   1.0.0          ✔ stringr   1.5.0     
#> ✔ ggplot2   3.4.3          ✔ tibble    3.2.1     
#> ✔ lubridate 1.9.2          ✔ tidyr     1.3.0     
#> ✔ purrr     1.0.2          
#> ── Conflicts ────────────────────────────────────────── tidyverse_conflicts() ──
#> ✖ dplyr::filter() masks stats::filter()
#> ✖ dplyr::lag()    masks stats::lag()
#> ℹ Use the conflicted package (<http://conflicted.r-lib.org/>) to force all conflicts to become errors
```

Of course, you can also load readr as an individual package:

``` r
library(readr)
```

To read a rectangular dataset with readr, you combine two pieces: a
function that parses the lines of the file into individual fields and a
column specification.

readr supports the following file formats with these `read_*()`
functions:

- `read_csv()`: comma-separated values (CSV)
- `read_tsv()`: tab-separated values (TSV)
- `read_csv2()`: semicolon-separated values with `,` as the decimal mark
- `read_delim()`: delimited files (CSV and TSV are important special
  cases)
- `read_fwf()`: fixed-width files
- `read_table()`: whitespace-separated files
- `read_log()`: web log files

A column specification describes how each column should be converted
from a character vector to a specific data type (e.g. character,
numeric, datetime, etc.). In the absence of a column specification,
readr will guess column types from the data. `vignette("column-types")`
gives more detail on how readr guesses the column types. Column type
guessing is very handy, especially during data exploration, but it’s
important to remember these are *just guesses*. As any data analysis
project matures past the exploratory phase, the best strategy is to
provide explicit column types.

The following example loads a sample file bundled with readr and guesses
the column types:

``` r
(chickens <- read_csv(readr_example("chickens.csv")))
#> Rows: 5 Columns: 4
#> ── Column specification ────────────────────────────────────────────────────────
#> Delimiter: ","
#> chr (3): chicken, sex, motto
#> dbl (1): eggs_laid
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
#> # A tibble: 5 × 4
#>   chicken                 sex     eggs_laid motto                               
#>   <chr>                   <chr>       <dbl> <chr>                               
#> 1 Foghorn Leghorn         rooster         0 That's a joke, ah say, that's a jok…
#> 2 Chicken Little          hen             3 The sky is falling!                 
#> 3 Ginger                  hen            12 Listen. We'll either die free chick…
#> 4 Camilla the Chicken     hen             7 Bawk, buck, ba-gawk.                
#> 5 Ernie The Giant Chicken rooster         0 Put Captain Solo in the cargo hold.
```

Note that readr prints the column types – the *guessed* column types, in
this case. This is useful because it allows you to check that the
columns have been read in as you expect. If they haven’t, that means you
need to provide the column specification. This sounds like a lot of
trouble, but luckily readr affords a nice workflow for this. Use
`spec()` to retrieve the (guessed) column specification from your
initial effort.

``` r
spec(chickens)
#> cols(
#>   chicken = col_character(),
#>   sex = col_character(),
#>   eggs_laid = col_double(),
#>   motto = col_character()
#> )
```

Now you can copy, paste, and tweak this, to create a more explicit readr
call that expresses the desired column types. Here we express that `sex`
should be a factor with levels `rooster` and `hen`, in that order, and
that `eggs_laid` should be integer.

``` r
chickens <- read_csv(
  readr_example("chickens.csv"),
  col_types = cols(
    chicken   = col_character(),
    sex       = col_factor(levels = c("rooster", "hen")),
    eggs_laid = col_integer(),
    motto     = col_character()
  )
)
chickens
#> # A tibble: 5 × 4
#>   chicken                 sex     eggs_laid motto                               
#>   <chr>                   <fct>       <int> <chr>                               
#> 1 Foghorn Leghorn         rooster         0 That's a joke, ah say, that's a jok…
#> 2 Chicken Little          hen             3 The sky is falling!                 
#> 3 Ginger                  hen            12 Listen. We'll either die free chick…
#> 4 Camilla the Chicken     hen             7 Bawk, buck, ba-gawk.                
#> 5 Ernie The Giant Chicken rooster         0 Put Captain Solo in the cargo hold.
```

`vignette("readr")` gives an expanded introduction to readr.

## Editions

readr got a new parsing engine in version 2.0.0 (released July 2021). In
this so-called second edition, readr calls `vroom::vroom()`, by default.

The parsing engine in readr versions prior to 2.0.0 is now called the
first edition. If you’re using readr \>= 2.0.0, you can still access
first edition parsing via the functions `with_edition(1, ...)` and
`local_edition(1)`. And, obviously, if you’re using readr \< 2.0.0, you
will get first edition parsing, by definition, because that’s all there
is.

We will continue to support the first edition for a number of releases,
but the overall goal is to make the second edition uniformly better than
the first. Therefore the plan is to eventually deprecate and then remove
the first edition code. New code and actively-maintained code should use
the second edition. The workarounds `with_edition(1, ...)` and
`local_edition(1)` are offered as a pragmatic way to patch up legacy
code or as a temporary solution for infelicities identified as the
second edition matures.

## Alternatives

There are two main alternatives to readr: base R and data.table’s
`fread()`. The most important differences are discussed below.

### Base R

Compared to the corresponding base functions, readr functions:

- Use a consistent naming scheme for the parameters (e.g. `col_names`
  and `col_types` not `header` and `colClasses`).

- Are generally much faster (up to 10x-100x) depending on the dataset.

- Leave strings as is by default, and automatically parse common
  date/time formats.

- Have a helpful progress bar if loading is going to take a while.

- All functions work exactly the same way regardless of the current
  locale. To override the US-centric defaults, use `locale()`.

### data.table and `fread()`

[data.table](https://github.com/Rdatatable/data.table) has a function
similar to `read_csv()` called `fread()`. Compared to `fread()`, readr
functions:

- Are sometimes slower, particularly on numeric heavy data.

- Can automatically guess some parameters, but basically encourage
  explicit specification of, e.g., the delimiter, skipped rows, and the
  header row.

- Follow tidyverse-wide conventions, such as returning a tibble, a
  standard approach for column name repair, and a common mini-language
  for column selection.

## Acknowledgements

Thanks to:

- [Joe Cheng](https://github.com/jcheng5) for showing me the beauty of
  deterministic finite automata for parsing, and for teaching me why I
  should write a tokenizer.

- [JJ Allaire](https://github.com/jjallaire) for helping me come up with
  a design that makes very few copies, and is easy to extend.

- [Dirk Eddelbuettel](http://dirk.eddelbuettel.com) for coming up with
  the name!

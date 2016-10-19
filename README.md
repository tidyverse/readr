# readr <img src="logo.png" align="right" />

[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/readr)](http://cran.r-project.org/package=readr)
[![Build Status](https://travis-ci.org/tidyverse/readr.png?branch=master)](https://travis-ci.org/tidyverse/readr)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/tidyverse/readr?branch=master&svg=true)](https://ci.appveyor.com/project/tidyverse/readr)
[![Coverage Status](http://codecov.io/github/tidyverse/readr/coverage.svg?branch=master)](http://codecov.io/tidyverse/hadley/readr?branch=master)

The goal of readr is to provide a fast and friendly way to read tabular data into R. The most important functions are:

* Read delimited files: `read_delim()`, `read_csv()`, `read_tsv()`, `read_csv2()`.
* Read fixed width files: `read_fwf()`, `read_table()`.
* Read lines: `read_lines()`.
* Read whole file: `read_file()`.
* Re-parse existing data frame: `type_convert()`.

## Installation

readr is now available from CRAN.
``` r
install.packages("readr")
```

You can try out the dev version with:
```R
# install.packages("devtools")
devtools::install_github("tidyverse/readr")
```

## Usage

```r
library(readr)
library(dplyr)

mtcars_path <- tempfile(fileext = ".csv")
write_csv(mtcars, mtcars_path)

# Read a csv file into a data frame
read_csv(mtcars_path)
# Read lines into a vector
read_lines(mtcars_path)
# Read whole file into a single string
read_file(mtcars_path)
```

See `vignette("column-types")` on how readr parses columns, and how you can override the defaults.

## Output

`read_csv()` produces a data frame with the following properties:

* Characters are never automatically converted to factors (i.e. no more 
  `stringsAsFactors = FALSE`).

* Valid column names are left as is, not munged into valid R identifiers
  (i.e. there is no `check.names = TRUE`). Missing column names are filled
  in with `X1`, `X2` etc, and duplicated column names are deduplicated.

* The data frame is given class `c("tbl_df", "tbl", "data.frame")` so 
  if you also use [dplyr](https://github.com/hadley/dplyr/) you'll get an 
  enhanced display.

* Row names are never set.

## Problems

If there are any problems parsing the file, the `read_` function will throw a warning telling you how many problems there are. You can then use the `problems()` function to access a data frame that gives information about each problem:

```R
df <- read_csv(col_types = "dd", col_names = c("x", "y"), skip = 1, "
1,2
a,b
")
#> Warning message: There were 2 problems. See problems(x) for more details
problems(df)
#>   row col expected actual
#> 1   2   1 a double      a
#> 2   2   2 a double      b
```

It's likely that there will be cases that you can never load without some manual regexp-based munging in R. Load those columns with `col_character()`, fix them up as needed, then use `convert_types()` to re-run the automated conversion on every character column in the data frame. Alternatively, you can use `parse_integer()`, `parse_numeric()`, `parse_date()` etc to parse a single character vector at a time.

## Compared to base functions

Compared to the corresponding base functions, readr functions:

* Use a consistent naming scheme for the parameters (e.g. `col_names` and 
 `col_types` not `header` and `colClasses`).
 
* Are much faster (up to 10x faster).

* Have a helpful progress bar if loading is going to take a while.

* All functions work exactly the same way regardless of the current locale.
  To override the US-centric defaults, use `locale()`.

## Compared to `fread()`

[data.table](https://github.com/Rdatatable/data.table) has a function similar to `read_csv()` called fread. Compared to fread, readr:

* Is slower (currently ~1.2-2x slower. If you want absolutely the best 
  performance, use `data.table::fread()`.
  
* Readr has a slightly more sophisticated parser, recognising both 
  doubled ("""") and backslash escapes ("\""). Readr allows you to read
  factors and date times directly from disk.
  
* `fread()` saves you work by automatically guessing the delimiter, whether
  or not the file has a header, how many lines to skip by default and 
  more. Readr forces you to supply these parameters.
  
* The underlying designs are quite different. Readr is designed to be
  general, and dealing with new types of rectangular data just requires 
  implementing a new tokenizer. `fread()` is designed to be as fast as 
  possible. `fread()` is pure C, readr is C++ (and Rcpp).

## Acknowledgements

Thanks to:

* [Joe Cheng](https://github.com/jcheng5) for showing me the beauty of
  deterministic finite automata for parsing, and for teaching me why I 
  should write a tokenizer.
  
* [JJ Allaire](https://github.com/jjallaire) for helping me come up with a
  design that makes very few copies, and is easy to extend.
  
* [Dirk Eddelbuettel](http://dirk.eddelbuettel.com) for coming up with the
  name!

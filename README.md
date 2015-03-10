# readr

[![Build Status](https://travis-ci.org/hadley/readr.png?branch=master)](https://travis-ci.org/hadley/readr)

The goal of readr is to provide a fast and friendly way to read data into R. It will eventually encompass the functionality provided by `read.csv()`, `read.table()`, `read.delim()` and `read.fwf()`.

## Installation

Currently, readr is not available from CRAN, but you can try out the dev version with:

```R
install_github("hadley/readr")
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

Other useful readers:

* `read_fwf()`: read a fixed width file
* `read_table()`: read tabular data separated by columns of whitespace

## Output

`read_csv()` produces a data frame with the following properties:

* Characters are never automatically converted to factors (i.e. no more 
  `stringsAsFactors = FALSE`).

* Column names are left as is, not munged into valid R identifiers.

* The data frame is given class `c("tbl_df", "tbl", "data.frame")` so 
  if you also use [dplyr](https://github.com/hadley/dplyr/) you'll get an 
  enhanced display.

* Row names are never set.

## Compared to base functions

Compared to the corresponding base functions, readr functions:

* Return "modern" data frames, as described above.

* Use a consistent naming scheme for the parameters (e.g. `col_names` and 
 `col_types` not `header` and `colClasses`).
 
* Are much faster (up to 10x faster).

## Compared to `fread()`

[data.table](https://github.com/Rdatatable/data.table) has a similar function called fread. Compared to fread, readr:

* Is slower. (It's currently much slower, but will always be at least 20% slower
  than fread.) If you want absolutely the best performance, use 
  `data.table::fread()`.
  
* readr has a slightly more sophisticated csv parser, and automatically 
  unescape doubled quotes (e.g. `"a""b"` is read in as `a"b`).
  
* `fread()` saves you work by automatically guessing the delimiter, whether
  or not the file has a header, how many lines to skip by default and 
  more. Readr always forces you to supply these parameters.
  
* The underlying designs are quite difference. Readr is designed to be fairly
  general so dealing with new types of rectangular data just requires 
  implementing a new tokenizer. fread is pure C, readr is C++ (and Rcpp).

## Acknowledgements

A big set of thanks to:

* [Joe Cheng](https://github.com/jcheng5) for showing me the beauty of
  deterministic finite automata for parsing, and for teaching me why I 
  should write a tokenizer.
  
* [JJ Allaire](https://github.com/jjallaire) for helping me come up with a
  design that makes very few copies.
  
* [Dirk Eddelbuettel](http://dirk.eddelbuettel.com) for coming up with the
  name!
  

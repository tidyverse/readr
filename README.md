# readr

[![Build Status](https://travis-ci.org/hadley/readr.png?branch=master)](https://travis-ci.org/hadley/readr)

The goal of readr is to provide a fast and friendly way to read data into R. It will eventually encompass the functionality provided by `read.csv()`, `read.table()`, `read.delim()` and `read.fwf()`.

## Installation

```R
install_github("RcppCore/Rcpp")
install_github("hadley/readr")
```

## Design principles

Fail early: readr functions fail early, as soon as they discover there is something wrong with the input. readr should make reasonable default guesses, but if it guesses wrong (e.g. a column turns out to be character, not integer) it will raise an error indicating what the problem is. You always know best about your data, so if a column type (or name) conflicts between the file and specification, then readr throws an error so that you can resolve the problem.

Fast: the goal of readr is to be fast. If adding a rarely used feature would result in a significant slowdown, we carefully consider if it's important. You can always fall back to the slow base functions if you need to parse an unusual format. readr aims to be competitive with the best file readers in other programming languages.

Sensible defaults: readr adopts sensible defaults for modern R coding. It never converts strings to factors (unless you explicitly ask for it), it never modifies column names, and it never creates row names.

Solid API: the readr API makes a clear distinction between figuring out what format a file is in, and parsing the file. 

## Data types

readr will automatically recognise and parse the following data types:

* doubles
* integers
* logicals
* ISO8601 date time (date + T + time + (optionally) time zone)
* ISO8601 dates (`YYYY-MM-DD`, `YYYYMMDD`)

If all else fails, it will leave the data as is, storing it in a character vector (never in a factor!). You can always override the default choices, and additionally use:

* factors
* inconsistently formatted dates and times

## Low-level functions

As well as high-level functions for very efficiently reading in complete files into data frames, readr also provides a number of lower-level functions. Combining these together won't be quite as efficient as using code that's bundled together at the C++ level (it will have to make a couple more copies of the data), but it gives you a lot of flexibility at the R level.

* `count_lines(file)`: count the number of lines in a file
* `parse_lines(file)`: parse a file into lines.
* `parse_delimited_fields(lines)`, `parse_fixed_fields(lines)`: parse lines into
  fields
* `parse_columns()`: parse fields into R columns

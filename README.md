fastread
========

[![Build Status](https://travis-ci.org/romainfrancois/fastread.png?branch=master)](https://travis-ci.org/romainfrancois/fastread)

The goal of fastread is to provide a fast and friendly way to read data into R. It will eventually encompass the functionality provided by `read.csv()`, `read.table()`, `read.delim()` and `read.fwf()`.

## Design principles

Fail early: fastread functions fail early, as soon as they discover there is something wrong with the input. fastread should make reasonable default guesses, but if it guesses wrong (e.g. a column turns out to be character, not integer) it will raise an error indicating what the problem is. The user always know best about their data, so if a column type (or name) conflicts between the file and specification, then we should throw an error so that the user can resolve the problem.

Fast: the goal of fastread is to be fast. If adding a rarely used feature would result in a significant slowdown, we should reconsider how important it is. Users can always fall back to the slow built in functions if they need to parse an unusual format. fastread should be competitive with the best file readers from other programming languages.

Sensible defaults: fastread adopts sensible defaults for modern R coding. It never converts strings to factors (unless you explicitly ask for it) and it leaves column names as is.

Clean separation between parsing and guessing parameters.

## Data types

fastread will automatically recognise and parse the following data types:

* double
* integer
* logical
* character
* ISO8601 date time (date + T + time + (optionally) time zone)
* ISO8601 dates (`YYYY-MM-DD`, `YYYYMMDD`)

Additionally, through use of custom parsers, you can parse:

* factors
* flexible date time parsing

## Low-level functions

As well as high-level functions for very efficiently reading in complete files into data frames, fastread also provides a number of lower-level functions. Combining these together won't be quite as efficient as using code that's bundled together at the C++ level (it will have to make a couple more copies of the data), but it gives you a lot of flexibility at the R level.

* `count_lines(file)`: count the number of lines in a file
* `read_lines(file)`: read each line of a file into a character vector

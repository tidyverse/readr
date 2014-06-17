fastread
========

[![Build Status](https://travis-ci.org/romainfrancois/fastread.png?branch=master)](https://travis-ci.org/romainfrancois/fastread)

The goal of fastread is to provide a fast and friendly way to read data into R. It will eventually encompass the functionality provided by `read.csv()`, `read.table()`, `read.delim()` and `read.fwf()`.

## Design principles

Fail early: fastread functions fail early, as soon as they discover there is something wrong with the input. fastread should make reasonable default guesses, but if it guesses wrong (e.g. a column turns out to be character, not integer) it will raise an error indicating what the problem is. The user always know best about their data, so if a column type (or name) conflicts between the file and specification, then we should throw an error so that the user can resolve the problem.

Fast: the goal of fastread is to be fast. If adding a rarely used feature would result in a significant slowdown, we should reconsider how important it is. Users can always fall back to the slow built in functions if they need to parse an unusual format. fastread should be competitive with the best file readers from other programming languages.

Sensible defaults: fastread adopts sensible defaults for modern R coding. It never converts strings to factors (unless you explicitly ask for it) and it leaves column names as is.

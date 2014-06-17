fastread
========

[![Build Status](https://travis-ci.org/romainfrancois/fastread.png?branch=master)](https://travis-ci.org/romainfrancois/fastread)

The goal of fastread is to provide a fast and friendly way to read data into R. It will eventually encompass the functionality provided by `read.csv()`, `read.table()`, `read.delim()` and `read.fwf()`.

fastread implements sensible defaults for modern R coding:

* strings are never converted to factors, unless explicitly asked for
* column names are left as is

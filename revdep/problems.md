# Setup

## Platform

|setting  |value                                  |
|:--------|:--------------------------------------|
|version  |R version 3.3.2 RC (2016-10-26 r71594) |
|system   |x86_64, darwin13.4.0                   |
|ui       |X11                                    |
|language |(EN)                                   |
|collate  |en_US.UTF-8                            |
|tz       |America/New_York                       |
|date     |2017-03-20                             |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.62.0-1   |2016-11-19 |cran (@1.62.0-)                  |
|covr      |   |2.2.2      |2017-01-05 |cran (@2.2.2)                    |
|curl      |   |2.3        |2016-11-24 |cran (@2.3)                      |
|hms       |   |0.3        |2016-11-22 |cran (@0.3)                      |
|knitr     |   |1.15.1     |2016-11-22 |cran (@1.15.1)                   |
|R6        |   |2.2.0      |2016-10-05 |cran (@2.2.0)                    |
|Rcpp      |   |0.12.10    |2017-03-20 |Github (RcppCore/Rcpp@5a71cf6)   |
|readr     |   |1.0.0.9000 |2017-03-20 |local (jimhester/readr@NA)       |
|rmarkdown |   |1.3        |2016-12-21 |cran (@1.3)                      |
|stringi   |   |1.1.2      |2016-10-01 |cran (@1.1.2)                    |
|testthat  |   |1.0.2.9000 |2017-03-03 |Github (hadley/testthat@b72a228) |
|tibble    |   |1.2        |2016-08-26 |cran (@1.2)                      |

# Check results
8 packages with problems

## biomartr (0.4.0)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/biomartr/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Packages required but not available: ‘biomaRt’ ‘Biostrings’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## farff (1.0)
Maintainer: Bernd Bischl <bernd_bischl@gmx.net>  
Bug reports: https://github.com/mlr-org/farff/issues

1 error  | 0 warnings | 1 note 

```
checking whether package ‘farff’ can be installed ... ERROR
Installation failed.
See ‘.../revdep/checks/farff.Rcheck/00install.out’ for details.

checking package dependencies ... NOTE
Packages suggested but not available for checking: ‘RWeka’ ‘OpenML’
```

## ggCompNet (0.1.0)
Maintainer: Sam Tyner <sctyner@iastate.edu>  
Bug reports: https://github.com/sctyner/ggCompNet/issues

0 errors | 1 warning  | 1 note 

```
checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...

Attaching package: 'dplyr'

The following objects are masked from 'package:stats':

    filter, lag

The following objects are masked from 'package:base':

    intersect, setdiff, setequal, union

Quitting from lines 102-115 (examples-from-paper.Rmd) 
Error: processing vignette 'examples-from-paper.Rmd' failed with diagnostics:
StatEdges was built with an incompatible version of ggproto.
Please reinstall the package that provides this extension.
Execution halted


checking installed package size ... NOTE
  installed size is  6.4Mb
  sub-directories of 1Mb or more:
    doc   6.1Mb
```

## gsheet (0.4.2)
Maintainer: Max Conway <conway.max1@gmail.com>  
Bug reports: https://github.com/maxconway/gsheet/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  1: gsheet2text("docs.google.com/spreadsheets/d/1I9mJsS5QnXF2TNNntTy-HrcdHmIF9wJ8ONYvEJTXSNo") at testthat/test-gsheet2text.R:5
  2: httr::GET(address) at .../revdep/checks/gsheet.Rcheck/00_pkg_src/gsheet/R/gsheet2text.R:26
  3: request_perform(req, hu$handle$handle)
  4: request_fetch(req$output, req$url, handle)
  5: request_fetch.write_memory(req$output, req$url, handle)
  6: curl::curl_fetch_memory(url, handle = handle)
  
  testthat results ================================================================
  OK: 4 SKIPPED: 0 FAILED: 1
  1. Error: Works correctly with and without sheet id (@test-gsheet2text.R#5) 
  
  Error: testthat unit tests failed
  Execution halted
```

## gutenbergr (0.1.2)
Maintainer: David Robinson <admiral.david@gmail.com>  
Bug reports: http://github.com/ropenscilabs/gutenbergr/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  testthat results ================================================================
  OK: 50 SKIPPED: 0 FAILED: 8
  1. Error: gutenberg_get_mirror works (@test-download.R#13) 
  2. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#22) 
  3. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#23) 
  4. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#31) 
  5. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#32) 
  6. Failure: Can download books from a data frame with gutenberg_id column (@test-download.R#43) 
  7. Failure: We can download a file that only has a -8 version (@test-download.R#50) 
  8. Failure: read_zip_url can download and read a zip file (@test-utils.R#7) 
  
  Error: testthat unit tests failed
  Execution halted
```

## myTAI (0.5.0)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/myTAI/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Package required but not available: ‘edgeR’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## tidyquant (0.4.0)
Maintainer: Matt Dancho <mdancho@business-science.io>  
Bug reports: https://github.com/mdancho84/tidyquant/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Package required but not available: ‘PerformanceAnalytics’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## tidytext (0.1.2)
Maintainer: Julia Silge <julia.silge@gmail.com>  
Bug reports: http://github.com/juliasilge/tidytext/issues

1 error  | 1 warning  | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  16: initialize(value, ...)
  17: callNextMethod()
  18: .nextMethod(.Object = .Object, ... = ...)
  19: validObject(.Object)
  20: stop(msg, ": ", errors, domain = NA)
  
  testthat results ================================================================
  OK: 129 SKIPPED: 0 FAILED: 2
  1. Error: Can cast tables into a sparse dfm (@test-sparse-casters.R#56) 
  2. Error: Can tidy dfm from quanteda (@test-sparse-tidiers.R#28) 
  
  Error: testthat unit tests failed
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Attaching package: 'dplyr'

The following objects are masked from 'package:stats':

    filter, lag

The following objects are masked from 'package:base':
... 8 lines ...

Attaching package: 'NLP'

The following object is masked from 'package:ggplot2':

    annotate

Quitting from lines 79-85 (tidying_casting.Rmd) 
Error: processing vignette 'tidying_casting.Rmd' failed with diagnostics:
invalid class "dfmSparse" object: superclass "replValueSp" not defined in the environment of the object's class
Execution halted
```


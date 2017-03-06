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
|date     |2017-03-03                             |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.62.0-1   |2016-11-19 |cran (@1.62.0-)                  |
|covr      |   |2.2.2      |2017-01-05 |cran (@2.2.2)                    |
|curl      |   |2.3        |2016-11-24 |cran (@2.3)                      |
|hms       |   |0.3        |2016-11-22 |cran (@0.3)                      |
|knitr     |   |1.15.1     |2016-11-22 |cran (@1.15.1)                   |
|R6        |   |2.2.0      |2016-10-05 |cran (@2.2.0)                    |
|Rcpp      |   |0.12.9.4   |2017-03-03 |Github (RcppCore/Rcpp@0566d7c)   |
|readr     |   |1.0.0.9000 |2017-03-03 |local (jimhester/readr@NA)       |
|rmarkdown |   |1.3        |2016-12-21 |cran (@1.3)                      |
|stringi   |   |1.1.2      |2016-10-01 |cran (@1.1.2)                    |
|testthat  |   |1.0.2.9000 |2017-03-03 |Github (hadley/testthat@b72a228) |
|tibble    |   |1.2        |2016-08-26 |cran (@1.2)                      |

# Check results
8 packages with problems

## biomartr (0.3.0)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/biomartr/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Packages required but not available: ‘biomaRt’ ‘Biostrings’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## eurostat (2.2.43)
Maintainer: Leo Lahti <louhos@googlegroups.com>  
Bug reports: https://github.com/ropengov/eurostat/issues

0 errors | 1 warning  | 0 notes

```
checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Loading required package: xml2
trying URL 'http://ec.europa.eu/eurostat/estat-navtree-portlet-prod/BulkDownloadListing?sort=1&file=data%2Ftsdtr210.tsv.gz'
Content type 'application/octet-stream;charset=UTF-8' length 4136 bytes
==================================================
downloaded 4136 bytes

Table tsdtr210 cached at /var/folders/dt/r5s12t392tb5sk181j3gs4zw0000gn/T//Rtmp13QYdB/eurostat/tsdtr210_num_code_TF.rds
trying URL 'http://ec.europa.eu/eurostat/estat-navtree-portlet-prod/BulkDownloadListing?sort=1&file=data%2Ftgs00026.tsv.gz'
Content type 'application/octet-stream;charset=UTF-8' length 5933 bytes
==================================================
downloaded 5933 bytes

Quitting from lines 305-321 (eurostat_tutorial.Rmd) 
Error: processing vignette 'eurostat_tutorial.Rmd' failed with diagnostics:
there is no package called 'Cairo'
Execution halted

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

## filesstrings (0.3.1)
Maintainer: Rory Nolan <rorynoolan@gmail.com>  
Bug reports: https://www.github.com/rorynolan/filesstrings/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  2. Failure: MergeTablesOnDisk works (@test_files.R#82) -------------------------
  readr::read_csv("merged.csv") not equal to tibble::tibble(x = c(1, 1), y = c(2, 29)).
  Incompatible type for column x: x integer, y numeric
  Incompatible type for column y: x integer, y numeric
  
  
  testthat results ================================================================
  OK: 145 SKIPPED: 0 FAILED: 2
  1. Failure: MergeTablesOnDisk works (@test_files.R#80) 
  2. Failure: MergeTablesOnDisk works (@test_files.R#82) 
  
  Error: testthat unit tests failed
  Execution halted
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

## myTAI (0.4.0)
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


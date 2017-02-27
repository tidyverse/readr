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
|date     |2017-02-24                             |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.62.0-1   |2016-11-19 |cran (@1.62.0-)                  |
|covr      |   |2.2.2      |2017-01-23 |Github (jimhester/covr@accef86)  |
|curl      |   |2.3        |2016-11-24 |cran (@2.3)                      |
|hms       |   |0.3        |2016-11-22 |cran (@0.3)                      |
|knitr     |   |1.15.1     |2016-11-22 |cran (@1.15.1)                   |
|R6        |   |2.2.0      |2016-10-05 |cran (@2.2.0)                    |
|Rcpp      |   |0.12.9.3   |2017-02-24 |Github (RcppCore/Rcpp@8bf15c0)   |
|readr     |   |1.0.0.9000 |2017-02-24 |local (jimhester/readr@NA)       |
|rmarkdown |   |1.3        |2016-12-21 |cran (@1.3)                      |
|stringi   |   |1.1.2      |2016-10-01 |cran (@1.1.2)                    |
|testthat  |   |1.0.2.9000 |2017-02-24 |Github (hadley/testthat@b72a228) |
|tibble    |   |1.2        |2016-08-26 |cran (@1.2)                      |

# Check results
9 packages with problems

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

Table tsdtr210 cached at /var/folders/dt/r5s12t392tb5sk181j3gs4zw0000gn/T//RtmpzoCu0y/eurostat/tsdtr210_num_code_TF.rds
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
See ‘/Users/jhester/Dropbox/projects/readr/revdep/checks/farff.Rcheck/00install.out’ for details.

checking package dependencies ... NOTE
Packages suggested but not available for checking: ‘RWeka’ ‘OpenML’
```

## filesstrings (0.3.1)
Maintainer: Rory Nolan <rorynoolan@gmail.com>  
Bug reports: https://www.github.com/rorynolan/filesstrings/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Package required but not available: ‘ore’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
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

## tidyquant (0.3.0)
Maintainer: Matt Dancho <mdancho@gmail.com>  
Bug reports: https://github.com/mdancho84/tidyquant/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
         AAPL %>% tq_mutate_(ohlc_fun = "close", mutate_fun = mutate_fun)
     }, paste0("fun = ", mutate_fun, " not a valid option.")) at testthat/test_tq_transform.R:141
  2: paste0("fun = ", mutate_fun, " not a valid option.") at /private/var/folders/dt/r5s12t392tb5sk181j3gs4zw0000gn/T/RtmpigKor6/devtoolsd627230754fb/hadley-testthat-b72a228/R/expect-output.R:147
  
  testthat results ================================================================
  OK: 144 SKIPPED: 1 FAILED: 4
  1. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_mutate.R#151) 
  2. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_mutate.R#169) 
  3. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_transform.R#123) 
  4. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_transform.R#141) 
  
  Error: testthat unit tests failed
  Execution halted
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


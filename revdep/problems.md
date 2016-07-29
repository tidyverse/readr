# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.3.0 (2016-05-03) |
|system   |x86_64, darwin13.4.0         |
|ui       |RStudio (0.99.1271)          |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |America/Chicago              |
|date     |2016-07-29                   |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.60.0-2   |2016-05-07 |CRAN (R 3.3.0)                   |
|covr      |   |2.1.0      |2016-06-21 |cran (@2.1.0)                    |
|curl      |   |1.1        |2016-07-26 |cran (@1.1)                      |
|hms       |   |0.2-1      |2016-07-19 |Github (rstats-db/hms@98d14cf)   |
|knitr     |   |1.13       |2016-05-09 |CRAN (R 3.3.0)                   |
|R6        |   |2.1.2      |2016-01-26 |CRAN (R 3.3.0)                   |
|Rcpp      |   |0.12.6     |2016-07-19 |cran (@0.12.6)                   |
|readr     |   |0.2.2.9000 |2016-07-29 |local (hadley/readr@8f8793a)     |
|rmarkdown |   |1.0        |2016-07-08 |cran (@1.0)                      |
|stringi   |   |1.1.1      |2016-05-27 |cran (@1.1.1)                    |
|testthat  |*  |1.0.2.9000 |2016-07-19 |Github (hadley/testthat@46d15da) |
|tibble    |   |1.1-2      |2016-07-29 |Github (hadley/tibble@8c12ace)   |

# Check results
4 packages with problems

## biomartr (0.0.3)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/biomartr/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Packages required but not available: ‘biomaRt’ ‘Biostrings’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## ddpcr (1.4)
Maintainer: Dean Attali <daattali@gmail.com>  
Bug reports: https://github.com/daattali/ddpcr/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  )
  Parsed with column specification:
  cols(
    `Assay1 Amplitude` = col_double(),
    `Assay2 Amplitude` = col_double(),
    Cluster = col_integer()
  )
  testthat results ================================================================
  OK: 261 SKIPPED: 0 FAILED: 1
  1. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) 
  
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

## rgho (0.1.0)
Maintainer: Antoine Filipovic-Pierucci <pierucci@gmail.com>  
Bug reports: https://github.com/pierucci/rgho/issues

1 error  | 1 warning  | 0 notes

```
checking examples ... ERROR
Running examples in ‘rgho-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: get_gho_data_
> ### Title: Returns GHO Data
> ### Aliases: get_gho_data get_gho_data_
> 
> ### ** Examples
> 
> 
> result <- get_gho_data(
+   dimension = "GHO",
+   code = "MDG_0000000001"
+ )
Error in `_f`(url = url, debug = debug, max_try = max_try) : 
  Server error: (500) Internal Server Error
Calls: get_gho_data ... %>% -> eval -> eval -> get_gho -> withVisible -> _f
Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Quitting from lines 74-80 (intro.Rmd) 
Error: processing vignette 'intro.Rmd' failed with diagnostics:
Server error: (500) Internal Server Error
Execution halted

```


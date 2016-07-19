# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.3.0 (2016-05-03) |
|system   |x86_64, darwin13.4.0         |
|ui       |RStudio (0.99.1261)          |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |America/Chicago              |
|date     |2016-07-19                   |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.60.0-2   |2016-05-07 |CRAN (R 3.3.0)                   |
|covr      |   |2.1.0      |2016-06-21 |cran (@2.1.0)                    |
|curl      |   |0.9.7      |2016-04-10 |CRAN (R 3.3.0)                   |
|hms       |   |0.2-1      |2016-07-19 |Github (rstats-db/hms@98d14cf)   |
|knitr     |   |1.13       |2016-05-09 |CRAN (R 3.3.0)                   |
|Rcpp      |   |0.12.5     |2016-05-14 |CRAN (R 3.3.0)                   |
|readr     |   |0.2.2.9000 |2016-07-19 |local (hadley/readr@6e7b437)     |
|rmarkdown |   |1.0        |2016-07-08 |cran (@1.0)                      |
|stringi   |   |1.1.1      |2016-05-27 |cran (@1.1.1)                    |
|testthat  |*  |1.0.2.9000 |2016-07-19 |Github (hadley/testthat@46d15da) |
|tibble    |   |1.1        |2016-07-19 |Github (hadley/tibble@725e61a)   |

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
  > 
  > test_check("ddpcr")
  1. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) ---------
  get_filled_drops(plate, "A05") not identical to readr::read_csv(file.path(dir, "A05_filled.csv")).
  Objects equal but not identical
  
  
  testthat results ================================================================
  OK: 261 SKIPPED: 0 FAILED: 1
  1. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) 
  
  Error: testthat unit tests failed
  Execution halted
```

## elpatron (0.0.2)
Maintainer: Jordan Mackie <jmackie@protonmail.com>

1 error  | 1 warning  | 0 notes

```
checking examples ... ERROR
Running examples in ‘elpatron-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: clean_bikedata
> ### Title: Clean raw cycling device data.
> ### Aliases: clean_bikedata
> 
> ### ** Examples
> 
> ride_file <- system.file("extdata/lufbra.fit", package = "elpatron")
> 
> parsed_ride <- import_ride(ride_file, make_laps = TRUE)
Error: Length of logical index vector must be 1 or 18, got: 17
Execution halted

checking Rd cross-references ... WARNING
Missing link or links in documentation object 'pipe.Rd':
  ‘[dplyr]{chain}’

See section 'Cross-references' in the 'Writing R Extensions' manual.

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


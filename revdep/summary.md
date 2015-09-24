# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.2.1 (2015-06-18) |
|system   |x86_64, darwin13.4.0         |
|ui       |RStudio (0.99.674)           |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |America/Chicago              |
|date     |2015-09-24                   |

## Packages

|package    |*  |version  |date       |source         |
|:----------|:--|:--------|:----------|:--------------|
|BH         |   |1.58.0-1 |2015-05-21 |CRAN (R 3.2.0) |
|curl       |   |0.9.3    |2015-08-25 |CRAN (R 3.2.0) |
|DiagrammeR |   |0.7      |2015-06-11 |CRAN (R 3.2.0) |
|knitr      |   |1.10.5   |2015-05-06 |CRAN (R 3.2.0) |
|Rcpp       |   |0.12.1   |2015-09-10 |CRAN (R 3.2.0) |
|rmarkdown  |   |0.7      |2015-06-13 |CRAN (R 3.2.0) |
|stringi    |   |0.5-5    |2015-06-29 |CRAN (R 3.2.0) |
|testthat   |*  |0.10.0   |2015-05-22 |CRAN (R 3.2.0) |

# Check results
6 checked out of 7 dependencies 

## abbyyR (0.2)
Maintainer: Gaurav Sood <gsood07@gmail.com>  
Bug reports: http://github.com/soodoku/abbyyR/issues

__OK__

## dataonderivatives (0.2.0)
Maintainer: Imanuel Costigan <i.costigan@me.com>  
Bug reports: https://github.com/imanuelcostigan/dataonderivatives/issues

```
checking package dependencies ... ERROR
Packages required and available but unsuitable versions: ‘utils’ ‘stats’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```
```
DONE
Status: 1 ERROR
```

## IalsaSynthesis (0.1.6)
Maintainer: Will Beasley <wibeasley@hotmail.com>  
Bug reports: https://github.com/IALSA/IalsaSynthesis/issues

__OK__

## mosaic (0.11)
Maintainer: Randall Pruim <rpruim@calvin.edu>

__OK__

## stationaRy (0.3)
Maintainer: Richard Iannone <riannone@me.com>

__OK__

## webreadr (0.3.0)
Maintainer: Oliver Keyes <ironholds@gmail.com>

```
checking package dependencies ... NOTE
Package suggested but not available for checking: ‘iptools’
```
```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  121 - 1 == 120
  
  testthat results ================================================================
  OK: 12 SKIPPED: 0 FAILED: 6
  1. Failure (at test_readers.R#6): Common Log Format files can be read, and split_clf can split the requests 
  2. Failure (at test_readers.R#10): Common Log Format files can be read, and split_clf can split the requests 
  3. Failure (at test_readers.R#16): Combined Log Format files can be read, and split_clf can split the requests 
  4. Failure (at test_readers.R#20): Combined Log Format files can be read, and split_clf can split the requests 
  5. Failure (at test_readers.R#27): Combined Log Format files can be read 
  6. Failure (at test_readers.R#31): Combined Log Format files can be read 
  
  Error: testthat unit tests failed
  Execution halted
```
```
DONE
Status: 1 ERROR, 1 NOTE
```


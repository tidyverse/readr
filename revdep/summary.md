# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.2.1 (2015-06-18) |
|system   |x86_64, darwin13.4.0         |
|ui       |RStudio (0.99.720)           |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |America/Chicago              |
|date     |2015-10-19                   |

## Packages

|package   |*  |version  |date       |source         |
|:---------|:--|:--------|:----------|:--------------|
|BH        |   |1.58.0-1 |2015-05-21 |CRAN (R 3.2.0) |
|curl      |   |0.9.3    |2015-08-25 |CRAN (R 3.2.0) |
|knitr     |   |1.10.5   |2015-05-06 |CRAN (R 3.2.0) |
|Rcpp      |   |0.12.1   |2015-09-10 |CRAN (R 3.2.0) |
|rmarkdown |   |0.7      |2015-06-13 |CRAN (R 3.2.0) |
|stringi   |   |0.5-5    |2015-06-29 |CRAN (R 3.2.0) |
|testthat  |*  |0.11.0   |2015-10-14 |CRAN (R 3.2.0) |

# Check results
6 checked out of 7 dependencies 

## abbyyR (0.2)
Maintainer: Gaurav Sood <gsood07@gmail.com>  
Bug reports: http://github.com/soodoku/abbyyR/issues

__OK__

## dataonderivatives (0.2.1)
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

## mosaic (0.12)
Maintainer: Randall Pruim <rpruim@calvin.edu>

```
checking installed package size ... NOTE
  installed size is  5.2Mb
  sub-directories of 1Mb or more:
    R     1.8Mb
    doc   2.8Mb
```
```
DONE
Status: 1 NOTE
```

## stationaRy (0.4)
Maintainer: Richard Iannone <riannone@me.com>

```
checking installed package size ... NOTE
  installed size is  8.1Mb
```
```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  1 710040 99999 CYPRESS BOWL FREESTYLE      CA       49.400 -123.2   969  2007
  2 715620 99999 CYPRESS BOWL SNOWBOARD      CA       49.383 -123.2  1180  2010
  3 716930 99999     CYPRESS BOWL SOUTH      CA       49.383 -123.2   886  2007
  Variables not shown: end (dbl), gmt_offset (dbl), time_zone_id (chr),
    country_name (chr), country_code (chr), iso3166_2_subd (chr), fips10_4_subd
    (chr)
  testthat results ================================================================
  OK: 30 SKIPPED: 0 FAILED: 2
  1. Error: get_isd_station_data returns correct number of columns 
  2. Error: error messages are provided in certain situations 
  
  Error: testthat unit tests failed
  Execution halted
```
```
DONE
Status: 1 ERROR, 1 NOTE
```

## webreadr (0.3.0)
Maintainer: Oliver Keyes <ironholds@gmail.com>

```
checking package dependencies ... NOTE
Package suggested but not available for checking: ‘iptools’
```
```
DONE
Status: 1 NOTE
```


# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.3.2 (2016-10-31) |
|system   |x86_64, linux-gnu            |
|ui       |X11                          |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |Zulu                         |
|date     |2017-01-13                   |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.62.0-1   |2016-11-19 |cran (@1.62.0-)                  |
|covr      |   |2.2.2      |2017-01-05 |cran (@2.2.2)                    |
|curl      |   |2.3        |2016-11-24 |cran (@2.3)                      |
|hms       |   |0.3        |2016-11-22 |cran (@0.3)                      |
|knitr     |   |1.15.1     |2016-11-22 |cran (@1.15.1)                   |
|R6        |   |2.2.0      |2016-10-05 |cran (@2.2.0)                    |
|Rcpp      |   |0.12.8     |2016-11-17 |cran (@0.12.8)                   |
|readr     |   |1.0.0      |2016-08-03 |cran (@1.0.0)                    |
|rmarkdown |   |1.3        |2016-12-21 |cran (@1.3)                      |
|stringi   |   |1.1.2      |2016-10-01 |cran (@1.1.2)                    |
|testthat  |   |1.0.2.9000 |2016-12-24 |Github (hadley/testthat@3b2f225) |
|tibble    |   |1.2        |2016-08-26 |cran (@1.2)                      |

# Check results

8 packages with problems

|package           |version | errors| warnings| notes|
|:-----------------|:-------|------:|--------:|-----:|
|geojsonio         |0.2.0   |      1|        0|     0|
|ggCompNet         |0.1.0   |      0|        1|     1|
|jpmesh            |0.3.0   |      1|        0|     0|
|jpndistrict       |0.1.0   |      1|        0|     0|
|photobiologyInOut |0.4.12  |      1|        0|     0|
|rmapshaper        |0.1.0   |      2|        1|     0|
|stplanr           |0.1.7-3 |      1|        0|     1|
|tidyquant         |0.2.0   |      1|        0|     0|

## geojsonio (0.2.0)
Maintainer: Scott Chamberlain <myrmecocystus@gmail.com>  
Bug reports: http://www.github.com/ropensci/geojsonio/issues

1 error  | 0 warnings | 0 notes

```
checking whether package ‘geojsonio’ can be installed ... ERROR
Installation failed.
See ‘/home/muelleki/git/R/readr/revdep/checks/geojsonio.Rcheck/00install.out’ for details.
```

## ggCompNet (0.1.0)
Maintainer: Sam Tyner <sctyner@iastate.edu>  
Bug reports: https://github.com/sctyner/ggCompNet/issues

0 errors | 1 warning  | 1 note 

```
checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Warning in engine$weave(file, quiet = quiet, encoding = enc) :
  Pandoc (>= 1.12.3) and/or pandoc-citeproc not available. Falling back to R Markdown v1.

Attaching package: 'dplyr'

The following objects are masked from 'package:stats':

    filter, lag

The following objects are masked from 'package:base':

    intersect, setdiff, setequal, union

Warning in engine$weave(file, quiet = quiet, encoding = enc) :
  Pandoc (>= 1.12.3) and/or pandoc-citeproc not available. Falling back to R Markdown v1.
Warning: Removed 8 rows containing missing values (geom_segment).
Quitting from lines 617-629 (examples-from-paper.Rmd) 
Error: processing vignette 'examples-from-paper.Rmd' failed with diagnostics:
GeomRasterAnn was built with an incompatible version of ggproto.
Please reinstall the package that provides this extension.
Execution halted


checking installed package size ... NOTE
  installed size is  6.4Mb
  sub-directories of 1Mb or more:
    doc   6.1Mb
```

## jpmesh (0.3.0)
Maintainer: Shinya Uryu <suika1127@gmail.com>  
Bug reports: https://github.com/uribo/jpmesh/issues

1 error  | 0 warnings | 0 notes

```
checking whether package ‘jpmesh’ can be installed ... ERROR
Installation failed.
See ‘/home/muelleki/git/R/readr/revdep/checks/jpmesh.Rcheck/00install.out’ for details.
```

## jpndistrict (0.1.0)
Maintainer: Shinya Uryu <suika1127@gmail.com>  
Bug reports: https://github.com/uribo/jpndistrict/issues

1 error  | 0 warnings | 0 notes

```
checking whether package ‘jpndistrict’ can be installed ... ERROR
Installation failed.
See ‘/home/muelleki/git/R/readr/revdep/checks/jpndistrict.Rcheck/00install.out’ for details.
```

## photobiologyInOut (0.4.12)
Maintainer: Pedro J. Aphalo <pedro.aphalo@helsinki.fi>  
Bug reports: https://bitbucket.org/aphalo/photobiologyinout/

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  as.numeric(getWhenMeasured(ss.spct), tz = "CET") not equal to as.numeric(ymd_hms("2013-05-06 15:13:40", tz = "CET"), tz = "CET").
  1/1 mismatches
  [1] 1.37e+09 - 1.37e+09 == 3450400
  
  
  Read 4 items
  testthat results ================================================================
  OK: 214 SKIPPED: 0 FAILED: 2
  1. Failure: SpectraSuite (@test-oo.R#76) 
  2. Failure: SpectraSuite (@test-oo.R#158) 
  
  Error: testthat unit tests failed
  Execution halted
```

## rmapshaper (0.1.0)
Maintainer: Andy Teucher <andy.teucher@gmail.com>  
Bug reports: http://www.github.com/ateucher/rmapshaper/issues

2 errors | 1 warning  | 0 notes

```
checking examples ... ERROR
Running examples in ‘rmapshaper-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: ms_clip
> ### Title: Remove features or portions of features that fall outside a
> ###   clipping area.
> ### Aliases: ms_clip
> 
> ### ** Examples
> 
> library(geojsonio, quietly = TRUE)
Error in dyn.load(file, DLLpath = DLLpath, ...) : 
  unable to load shared object '/home/muelleki/R/x86_64-pc-linux-gnu-library/3.3/rgdal/libs/rgdal.so':
  libgdal.so.1: cannot open shared object file: No such file or directory
Error: package or namespace load failed for ‘geojsonio’
Execution halted

checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  Type 'q()' to quit R.
  
  > library(testthat)
  > library(rmapshaper)
  > 
  > test_check("rmapshaper")
  Error in dyn.load(file, DLLpath = DLLpath, ...) : 
    unable to load shared object '/home/muelleki/R/x86_64-pc-linux-gnu-library/3.3/rgdal/libs/rgdal.so':
    libgdal.so.1: cannot open shared object file: No such file or directory
  Error: package or namespace load failed for 'geojsonio'
  testthat results ================================================================
  OK: 0 SKIPPED: 0 FAILED: 0
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Warning in engine$weave(file, quiet = quiet, encoding = enc) :
  Pandoc (>= 1.12.3) and/or pandoc-citeproc not available. Falling back to R Markdown v1.
Error in dyn.load(file, DLLpath = DLLpath, ...) : 
  unable to load shared object '/home/muelleki/R/x86_64-pc-linux-gnu-library/3.3/rgdal/libs/rgdal.so':
  libgdal.so.1: cannot open shared object file: No such file or directory
Quitting from lines 41-46 (rmapshaper.Rmd) 
Error: processing vignette 'rmapshaper.Rmd' failed with diagnostics:
package or namespace load failed for 'geojsonio'
Execution halted

```

## stplanr (0.1.7-3)
Maintainer: Robin Lovelace <rob00x@gmail.com>  
Bug reports: https://github.com/ropensci/stplanr/issues

1 error  | 0 warnings | 1 note 

```
checking whether package ‘stplanr’ can be installed ... ERROR
Installation failed.
See ‘/home/muelleki/git/R/readr/revdep/checks/stplanr.Rcheck/00install.out’ for details.

checking package dependencies ... NOTE
Packages suggested but not available for checking:
  ‘tmap’ ‘tmaptools’ ‘OpenStreetMap’
```

## tidyquant (0.2.0)
Maintainer: Matt Dancho <mdancho@gmail.com>  
Bug reports: https://github.com/mdancho84/tidyquant/issues

1 error  | 0 warnings | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
         AAPL %>% tq_mutate_(ohlc_fun = "close", mutate_fun = mutate_fun)
     }, paste0("fun = ", mutate_fun, " not a valid option.")) at testthat/test_tq_transform.R:118
  2: paste0("fun = ", mutate_fun, " not a valid option.") at /tmp/RtmpGs2f8Q/devtools11166987ba25/hadley-testthat-3b2f225/R/expect-output.R:147
  
  testthat results ================================================================
  OK: 133 SKIPPED: 1 FAILED: 4
  1. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_mutate.R#133) 
  2. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_mutate.R#151) 
  3. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_transform.R#100) 
  4. Error: Test error on invalid ohlc_fun, x and y inputs. (@test_tq_transform.R#118) 
  
  Error: testthat unit tests failed
  Execution halted
```


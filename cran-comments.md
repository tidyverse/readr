## Test environments
* local OS X install, R 3.2.2
* ubuntu 12.04 (on travis-ci), R 3.2.2
* win-builder (devel and release)

## R CMD check results
There were no ERRORs or WARNINGs. 

## Reverse dependencies

* I ran R CMD check on all 7 reverse dependencies on Sep 25 and again today.
  Latest results at https://github.com/hadley/readr/blob/master/revdep/summary.md

* There is one new failure: stationaRy. I have contacted the author with 
  a fix and they will submit to CRAN in the next day or two.
  
  

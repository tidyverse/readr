## Test environments
* local OS X install, R 3.2.3
* ubuntu 12.04 (on travis-ci), R 3.2.3
* win-builder (devel and release)

## R CMD check results
There were no ERRORs, WARNINGs, or NOTEs.

There are still UBSAN and ASAN warnings. Unfortunately these come from `localtime.c` which was included (with attribution) from base R. I think this code never triggers ABSAN/UBSAN warnings for base R because it is only run on windows.

## Reverse dependencies

* I ran R CMD check on all 40 reverse dependencies on Sep 25 and again today.
  Results at https://github.com/hadley/readr/blob/master/revdep/
  
* There were four failures:

  * ddpcr: checking tests ... ERROR.
    Fixed in the dev version of ddpcr. Will be re-submitted shortly
  
  * rgho: checking examples ... ERROR
    Fails with "Server error: (500) Internal Server Error", so I don't think
    it's due to a change in readr.

  * biomartr, myTAI: I couldn't automatically install dependencies.
  
* I notified all authors on July 19, and again today.

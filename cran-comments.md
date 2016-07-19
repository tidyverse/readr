# Release summary

This version should fix the UBSAN problems (and hopefully the crash on OSX which I couldn't replicate locally). Sorry for the multiple releases :(

## Test environments
* local OS X install, R 3.2.2
* ubuntu 12.04 (on travis-ci), R 3.2.2
* win-builder (devel and release)

## R CMD check results
There were no ERRORs, WARNINGs, or NOTEs.

## Reverse dependencies

* I ran R CMD check on all 38 reverse dependencies on Sep 25 and again today.
  Results at https://github.com/hadley/readr/blob/master/revdep/
  
* I notified all authors on July 19.

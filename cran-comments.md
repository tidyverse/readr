## Test environments
* local OS X install, R 3.5.1.
* Ubuntu 12.04 (on travis-ci), R-oldrel, R-release, R-devel
* Windows Server 2012 R2 (x64), R 3.5.1
* Win-builder
* Rhub - solaris

## R CMD check results
There were no ERRORs, WARNINGs

There was 1 NOTEs:

* GNU make is a SystemRequirements.

## Downstream dependencies
I ran `R CMD check` on 297 reverse dependencies on CRAN and Bioconductor
(https://github.com/tidyverse/readr/tree/master/revdep#readme). There were 6 errors
related to changes in readr.

I have submitted fixes to the 6 packages which allow them to pass checks
with readr 1.3.0

* fastqcr
  https://github.com/kassambara/fastqcr/pull/11

* jstor
  https://github.com/ropensci/jstor/pull/76

* photobiologyInOut
  https://bitbucket.org/aphalo/photobiologyinout/pull-requests/3

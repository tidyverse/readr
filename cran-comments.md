## Test environments
* local OS X install, R 3.4.3.
* Ubuntu 12.04 (on travis-ci), R-oldrel, R-release, R-devel
* Windows Server 2012 R2 (x64), R 3.4.3
* Rhub

## R CMD check results

I ran `R CMD check` on 189 reverse dependencies
(https://github.com/tidyverse/readr/tree/master/revdep#readme). There were 3 errors
related to changes in readr.

I have submitted fixes to the three packages which allow them to pass checks
with readr 1.2.0

* ddpcr
  https://github.com/daattali/ddpcr/pull/21

* fastqcr
  https://github.com/kassambara/fastqcr/pull/7

* readODS
  https://github.com/chainsawriot/readODS/pull/44

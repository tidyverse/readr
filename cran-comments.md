## Test environments
* local OS X install, R 3.3.1.
* Ubuntu 12.04 (on travis-ci), R-oldrel, R-release, R-devel
* Windows Server 2012 R2 (x64), R 3.3.0
* Rhub
  * Windows Server 2008 R2 SP1, R-devel, 32/64 bit
  * Debian Linux, R-devel, GCC ASAN/UBSAN
  * Fedora Linux, R-devel, clang, gfortran
  * Ubuntu Linux 16.04 LTS, R-release, GCC

## R CMD check results
There were no ERRORs, WARNINGs, or NOTEs.

There were no warnings from UBSAN and ASAN run on R-hub
(https://builder.r-hub.io/status/readr_1.0.0.9000.tar.gz-7308f26232304b308e6f3949f0e69d75).

## Reverse dependencies

* I ran R CMD check on all 84 reverse dependencies
  Results at https://github.com/tidyverse/readr/blob/master/revdep/

* There were 8 failures:

  * ggCompNet: There was an error building the vignette, I looked into it but
    it seems to be unrelated to readr changes.

  * gsheet: Network failure when trying to retrieve a external resource.

  * gutenbergr: Network failure when trying to retrieve a external resource, duplicated on CRAN checks.

  * biomartr, farff, myTAI, tidyquant: I couldn't automatically install dependencies.

  * tidytext: Looked into failures, seem un-releated to readr.

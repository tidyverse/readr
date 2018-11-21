## Test environments
* local OS X install, R 3.4.3.
* Ubuntu 12.04 (on travis-ci), R-oldrel, R-release, R-devel
* Windows Server 2012 R2 (x64), R 3.4.3
* Rhub

## R CMD check results
There were no ERRORs or WARNINGs.

There was 1 NOTEs:

* checking compiled code ...NOTE
   File ‘readr/libs/readr.so’:
     Found non-API calls to R: ‘R_GetConnection’, ‘R_WriteConnection’

* The xml2 package uses the connections API to read and write files to R
connections. I don't believe there is an alternative other than using the
connections API, and the connections code in readr has existed on CRAN since
version 1.1.0, released on March 22nd, 2017.

## Downstream dependencies
I ran `R CMD check` on 189 reverse dependencies
(https://github.com/tidyverse/readr/tree/master/revdep#readme). There were 8 errors
related to changes in readr.

I have submitted fixes to the three packages which allow them to pass checks
with readr 1.2.0

* ddpcr
  https://github.com/daattali/ddpcr/pull/21

* fastqcr
  https://github.com/kassambara/fastqcr/pull/7

* jstor
  https://github.com/ropensci/jstor/pull/75

* mudata2
  https://github.com/paleolimbot/mudata/pull/31

* photobiologyInOut
  https://bitbucket.org/aphalo/photobiologyinout/pull-requests/2/

* readODS
  https://github.com/chainsawriot/readODS/pull/44

* rdflib
  https://github.com/ropensci/rdflib/pull/30

* visdat
  https://github.com/ropensci/visdat/pull/103

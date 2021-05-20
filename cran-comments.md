This release should fix the test errors on R-devel

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

- auk - https://github.com/CornellLabofOrnithology/auk/pull/55
- blaise - https://github.com/tidyverse/readr/issues/1211
- dataRetrieval - https://github.com/USGS-R/dataRetrieval/pull/571
- DSSAT - https://github.com/palderman/DSSAT/pull/27
- esmisc - Fixed
- eyelinker - https://github.com/a-hurst/eyelinker/pull/2
- fgeo.tool - https://github.com/forestgeo/fgeo.tool/pull/189
- fitzRoy - This seems spurious, tests work locally
- genius - https://github.com/JosiahParry/genius/pull/55
- radous - https://github.com/feddelegrand7/radous/pull/2
- rglobi - https://github.com/ropensci/rglobi/pull/37
- valr - https://github.com/rnabioco/valr/pull/374
- rhmmer - TODO: ???
- truthiness - https://github.com/dalejbarr/truthiness/pull/5
- vroom - Just need to submit the new version before readr
- xpose - https://github.com/UUPharmacometrics/xpose/pull/194

## R CMD check results
There were no ERRORs, WARNINGs

There were 0 NOTEs:

## Revdepcheck results

We checked reverse dependency checks and proposed the following changes where need to fix reverse dependencies prior to releasing readr.


- chronicle, dccvalidator, esmisc, rbedrock, rgeopat2, tidytuesdayR - These all seem like sporadic errors or unrelated to readr.
  They also did not appear in the previous submissions revdep check results, so I think they are false positives.

I had already sent code changes for the remaining issues found.

- blaise - https://github.com/sophof/blaise/pull/5
- DSSAT - https://github.com/palderman/DSSAT/pull/27
- frenchdata - https://github.com/nareal/frenchdata/pull/1
- genius - https://github.com/JosiahParry/genius/pull/55
- geobr - https://github.com/ipeaGIT/geobr/pull/257
- geometr - https://github.com/EhrmannS/geometr/pull/6
- jstor - https://github.com/ropensci/jstor/pull/85
- rhmmer - https://github.com/arendsee/rhmmer/pull/1

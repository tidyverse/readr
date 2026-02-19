## revdepcheck results

We checked 911 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 8 new problems
 * We failed to check 2 packages

Issues with CRAN packages are summarised below.

### New problems

I opened issues and, in most cases, pull requests about these deprecations in late November 2025.

#### read_table2 removed

* readit
* rubias
* skater
* tidypopgen

#### `quoted_na` argument not usable in `read_csv()` with edition 2

* MIMSunit

#### `quote_escape` argument removed

* params

#### `path` argument removed

* suddengains

#### unclear but suspect unrelated to readr

* myTAI: The vignette code chunk that is failing has been set to `eval = FALSE` now on GitHub.

### Failed to check

* BayesPET  (NA) Seems to have an undeclared dependency on rstantools. Appears unrelated to readr.
* eyelinker (NA) Another read_table2 issue that actually prevents installation.

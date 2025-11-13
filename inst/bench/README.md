# readr First Edition Benchmark

This benchmark measures the performance impact of removing non-API C calls (`SETLENGTH`, `SET_TRUELENGTH`, `SET_GROWABLE_BIT`) from readr's first edition parser.

## Quick Start

```r
# 1. Download test data
Rscript inst/bench/download-data.R

# 2. Run benchmark on AFTER version (current branch, without non-API calls)
R CMD INSTALL .
Rscript inst/bench/run-bench.R

# 3. Run benchmark on BEFORE version (with non-API calls)
git checkout main -- src/Collector.h
R CMD INSTALL .
Rscript inst/bench/run-bench.R

# 4. Restore Collector.h and compare results
git checkout HEAD -- src/Collector.h
Rscript inst/bench/compare-results.R
```

## Files

- `download-data.R`: Downloads NYC taxi trip_fare data (January 2013, ~2GB)
- `run-bench.R`: Runs benchmark on readr first edition
- `compare-results.R`: Compares before/after benchmark results
- `README.md`: This file

## Data

The benchmark uses NYC taxi trip fare data from January 2013:
- Source: https://archive.org/details/nycTaxiTripData2013
- File: `trip_fare_1.csv` (~1.6GB, 14+ million rows)
- Location: `~/tmp/nyc-taxi-data/trip_fare_1.csv`

## What's Being Tested

The benchmark specifically tests readr **first edition** (the C++ parser), since that's the only code affected by removing the non-API calls. The benchmark forces first edition usage with `with_edition(1, ...)`.

Readr second edition (the default) delegates to vroom and is not affected by these changes.

## Expected Impact

The removed optimization avoided memory allocation when shrinking vectors during parsing. Replacing it with the official `Rf_lengthgets()` API may cause a small performance regression, but this is necessary for C API compliance.

## Actual results

Here's what I saw when I ran the benchmark:

```
~/work/readr % Rscript inst/bench/compare-results.R
Found 4 benchmark result files:
 - bench_results_20251113_111935_after.rds 
 - bench_results_20251113_112432_before.rds 
 - bench_results_20251113_121649_after.rds 
 - bench_results_20251113_121855_before.rds 

Performance Comparison
=====================

BEFORE (with non-API calls):
  Median time: 13.5s
  Min time:    13.4s
  Memory:      2.56GB

AFTER (without non-API calls):
  Median time: 14.2s
  Min time:    13.8s
  Memory:      2.56GB

CHANGE:
  Median time: +4.87%
  Min time:    +3.00%
  Memory:      +0.00%

Performance impact is minimal (< 5%).
```

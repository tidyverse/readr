#!/usr/bin/env Rscript

# first crack made by claude code, based on vroom benchmark inspiration
# then I tweaked to make it less cringey
# I regard this as disposable code that just needs to do the right thing

# Compare benchmark results from before and after removing non-API calls

library(bench)
suppressPackageStartupMessages(library(tidyverse))

# Find all benchmark result files
result_files <- list.files(
  "inst/bench",
  pattern = "^bench_results_.*\\.rds$",
  full.names = TRUE
)

if (length(result_files) < 2) {
  stop(
    "Need at least 2 benchmark results to compare.\n",
    "Run run-bench.R on both the before and after versions."
  )
}

cat("Found", length(result_files), "benchmark result files:\n")
for (f in result_files) {
  cat(" -", basename(f), "\n")
}
cat("\n")

# Read all results
results_list <- lapply(result_files, readRDS)

dat <- results_list |>
  bind_rows() |>
  select(version = version_label, timestamp, everything()) |>
  select(-c(n_itr, result, memory, time, gc, expression))

# Keep only the most recent run for each version
dat <- dat |>
  arrange(desc(timestamp)) |>
  group_by(version) |>
  slice(1) |>
  ungroup() |>
  arrange(desc(version)) |>
  select(-timestamp)

# dat

# Calculate percentage change if we have both before and after
if (all(c("before", "after") %in% dat$version)) {
  before_idx <- which(dat$version == "before")
  after_idx <- which(dat$version == "after")

  cat("Performance Comparison\n")
  cat("=====================\n\n")

  cat("BEFORE (with non-API calls):\n")
  cat(
    "  Median time: ",
    format(as_bench_time(dat$median[before_idx])),
    "\n",
    sep = ""
  )
  cat(
    "  Min time:    ",
    format(dat$min[before_idx]),
    "\n",
    sep = ""
  )
  cat(
    "  Memory:      ",
    format(as_bench_bytes(dat$mem_alloc[before_idx])),
    "\n\n",
    sep = ""
  )

  cat("AFTER (without non-API calls):\n")
  cat(
    "  Median time: ",
    format(dat$median[after_idx]),
    "\n",
    sep = ""
  )
  cat(
    "  Min time:    ",
    format(dat$min[after_idx]),
    "\n",
    sep = ""
  )
  cat(
    "  Memory:      ",
    format(dat$mem_alloc[after_idx]),
    "\n\n",
    sep = ""
  )

  median_pct_change <- (dat$median[after_idx] -
    dat$median[before_idx]) /
    dat$median[before_idx] *
    100
  min_pct_change <- (dat$min[after_idx] -
    dat$min[before_idx]) /
    dat$min[before_idx] *
    100
  mem_pct_change <- (dat$mem_alloc[after_idx] -
    dat$mem_alloc[before_idx]) /
    dat$mem_alloc[before_idx] *
    100

  cat("CHANGE:\n")
  cat(sprintf("  Median time: %+.2f%%\n", median_pct_change))
  cat(sprintf("  Min time:    %+.2f%%\n", min_pct_change))
  cat(sprintf("  Memory:      %+.2f%%\n", mem_pct_change))
  cat("\n")

  if (abs(median_pct_change) < 5) {
    cat("Performance impact is minimal (< 5%).\n")
  } else if (median_pct_change > 0) {
    cat("Performance decreased by", round(median_pct_change, 1), "%\n")
  } else {
    cat("Performance improved by", round(abs(median_pct_change), 1), "%\n")
  }
} else {
  cat("Full comparison table:\n\n")
  print(dat)
}

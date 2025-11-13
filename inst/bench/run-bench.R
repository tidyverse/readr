#!/usr/bin/env Rscript

# first crack made by claude code, based on vroom benchmark inspiration
# then I tweaked to make it less cringey
# I regard this as disposable code that just needs to do the right thing

# Benchmark readr first edition to measure performance impact of
# removing non-API calls (SETLENGTH, SET_TRUELENGTH, SET_GROWABLE_BIT)
#
# This script should be run twice:
# 1. Before the changes (main branch)
# 2. After the changes (current branch)

library(readr)
library(bench)
library(fs)

# Configuration
data_file <- path("~/tmp/nyc-taxi-data", "trip_fare_1.csv")

if (!file_exists(data_file)) {
  stop(
    "Data file not found. Run download-data.R first:\n",
    "  Rscript inst/bench/download-data.R"
  )
}

# Determine if this is before or after by checking for SETLENGTH in Collector.h
collector_h <- path("src/Collector.h")
collector_contents <- paste(readLines(collector_h), collapse = "\n")
has_setlength <- grepl("SETLENGTH", collector_contents)
version_label <- if (has_setlength) {
  "BEFORE (with non-API calls)"
} else {
  "AFTER (without non-API calls)"
}

cat("Benchmarking readr first edition\n")
cat("=================================\n\n")
cat("Version:", version_label, "\n")
cat("Data file:", data_file, "\n")
cat("File size:", format(file_size(data_file)), "\n\n")

# Run benchmark using first edition
cat("Running benchmark (this may take a minute)...\n\n")

results <- bench::mark(
  read_csv_ed1 = with_edition(
    1,
    read_csv(
      data_file,
      col_types = c(pickup_datetime = "c"),
      progress = FALSE
    )
  ),
  iterations = 5,
  check = FALSE,
  memory = TRUE
)

# Print results
print(results[, c("expression", "min", "median", "mem_alloc")])

# Also save results with more detail
results$version_label <- if (has_setlength) "before" else "after"
results$timestamp <- Sys.time()

# Save results
output_file <- sprintf(
  "bench_results_%s_%s.rds",
  format(Sys.time(), "%Y%m%d_%H%M%S"),
  results$version_label
)
output_path <- path("inst/bench", output_file)
saveRDS(results, output_path)

cat("\nResults saved to:", output_path, "\n")

invisible(results)

#!/usr/bin/env Rscript

# first crack made by claude code, based on vroom benchmark inspiration
# then I tweaked to make it less cringey
# I regard this as disposable code that just needs to do the right thing

# Download NYC taxi trip_fare data for benchmarking
# Downloads the 7z archive and extracts all 12 months (same approach as vroom benchmark)

library(fs)

data_dir <- dir_create("~/tmp/nyc-taxi-data")
archive_file <- path(data_dir, "trip_fare.7z")

# Check if data has already been extracted
existing_csvs <- dir_ls(data_dir, regexp = "trip_fare.*\\.csv$")

if (length(existing_csvs) > 0) {
  cat("Data already exists:\n")
  for (csv in existing_csvs) {
    cat(" -", path_file(csv), ":", format(file_size(csv)), "\n")
  }
} else {
  cat("Downloading NYC taxi data archive...\n")
  cat("This will take several minutes (~1.6GB download)\n\n")

  # Download 7z archive (same as vroom benchmark)
  url <- "https://archive.org/download/nycTaxiTripData2013/trip_fare.7z"

  if (!file_exists(archive_file)) {
    # Set longer timeout for large file (1.6GB)
    old_timeout <- getOption("timeout")
    options(timeout = 600) # 10 minutes
    on.exit(options(timeout = old_timeout))

    download.file(url, archive_file, mode = "wb")
    cat("Download complete\n\n")
  } else {
    cat("Archive already downloaded\n\n")
  }

  cat("Extracting archive...\n")
  cat("(This will extract all 12 months of data)\n")

  # Check if 7z is available
  seven_z <- Sys.which("7z")
  if (seven_z == "") {
    seven_z <- Sys.which("7za")
  }

  if (seven_z == "") {
    stop(
      "7z utility not found. Please install it:\n",
      "  macOS: brew install p7zip\n",
      "  Linux: sudo apt install p7zip-full\n",
      "  Windows: Install from https://www.7-zip.org/"
    )
  }

  # Extract in the data directory
  system2(seven_z, c("x", archive_file, sprintf("-o%s", data_dir)))

  # Fix trailing space in header for all extracted files
  cat("\nFixing headers...\n")
  csv_files <- dir_ls(data_dir, regexp = "trip_fare.*\\.csv$")

  for (csv_file in csv_files) {
    header <- readLines(csv_file, n = 1)
    fixed_header <- gsub(", ", ",", header)
    if (header != fixed_header) {
      all_lines <- readLines(csv_file)
      all_lines[1] <- fixed_header
      writeLines(all_lines, csv_file)
    }
  }

  cat("Headers fixed for", length(csv_files), "files\n\n")
  cat("Done! Extracted", length(csv_files), "CSV files\n")
}

# Print summary
cat("\nAvailable data files:\n")
csv_files <- dir_ls(data_dir, regexp = "trip_fare.*\\.csv$")
for (csv in csv_files) {
  cat(" -", path_file(csv), ":", format(file_size(csv)), "\n")
}

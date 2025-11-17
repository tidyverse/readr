# readr: Read Rectangular Text Data

## Package Overview

readr provides a fast and friendly way to read rectangular text data from delimited files (CSV, TSV, etc.), fixed-width files, and log files. The package is designed to flexibly parse many types of data found in the wild while cleanly failing when data unexpectedly changes. Part of the core tidyverse.

## Essential Commands

Always use `R --no-save --no-restore-data` when running R from the console.

Always run `air format .` after generating or modifying code. The binary of air is probably not on the PATH but is typically found inside the Air extension used by Positron, e.g. something like `~/.positron/extensions/posit.air-vscode-0.18.0/bundled/bin/air`.

## Development Workflow

**Testing**
Place tests in `tests/testthat/test-{name}.R` alongside corresponding source files. Run tests with `devtools::test()` or `devtools::test_file("tests/testthat/test-{name}.R")`. Do NOT use `test_active_file()`. All new code requires accompanying tests.

**Documentation**
After modifying roxygen2 comments, run `devtools::document()` to regenerate documentation. Export all user-facing functions with proper roxygen2 documentation. Add new function topics to the appropriate section in `_pkgdown.yml`. Use sentence case for documentation headings.

**Code Style**
Follow tidyverse style guide conventions. Use `cli::cli_abort()` for error messages with informative formatting. Organize code with "newspaper style"—main logic first, helper functions below.

## Key Technical Details

**Architecture**
- Edition 2 (default since v2.0.0): Delegates to `vroom::vroom()` for multi-threaded, lazy parsing
- Edition 1 (legacy): Single-threaded eager parser in C++, accessible via `with_edition(1, ...)` or `local_edition(1)`
- C++ code uses cpp11 interface (in `src/`) for performance-critical operations
- Main R code in `R/` provides user-facing API and column specification system

**Core Functions**
- Reading: `read_delim()`, `read_csv()`, `read_tsv()`, `read_csv2()`, `read_fwf()`, `read_table()`, `read_log()`
- Writing: `write_csv()`, `write_tsv()`, `write_delim()`, `format_csv()`
- Low-level: `read_lines()`, `read_file()`, `read_rds()`, `count_fields()`, `guess_encoding()`

**Column Type System**
- Automatic type guessing from sample of rows (controlled by `guess_max`)
- Explicit specification via `cols()`, `cols_only()`, or compact string notation
- Column parsers: `col_character()`, `col_integer()`, `col_double()`, `col_number()`, `col_date()`, `col_datetime()`, `col_time()`, `col_factor()`, `col_logical()`, `col_skip()`, `col_guess()`
- Parse functions: `parse_character()`, `parse_number()`, `parse_datetime()`, etc.
- Problems tracking: `problems()` function to inspect parsing issues

**Locale Support**
- `locale()` object controls region-specific settings: decimal mark, grouping mark, date/time formats, encoding, timezone
- Defaults to US-centric locale but fully customizable via `date_names()` and `date_names_langs()`

**Performance & Parsing**
- Edition 2 uses vroom for fast multi-threaded parsing and ALTREP lazy evaluation
- Progress bars for long operations (controlled by `readr.show_progress` option)
- `num_threads` parameter to control parallelism
- `lazy` parameter to control ALTREP lazy reading (default FALSE for safety)

**Key Dependencies**
- vroom (≥ 1.6.0): Powers Edition 2 parsing
- cli (≥ 3.2.0): Error messages and formatting
- tibble: Output format
- tzdb (≥ 0.1.1): Timezone database for datetime parsing

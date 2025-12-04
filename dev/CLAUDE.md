# readr: Read Rectangular Text Data

## Package Overview

readr provides a fast and friendly way to read rectangular text data
from delimited files (CSV, TSV, etc.), fixed-width files, and log files.
The package is designed to flexibly parse many types of data found in
the wild while cleanly failing when data unexpectedly changes. Part of
the core tidyverse.

## Essential Commands

Always use `R --no-save --no-restore-data` when running R from the
console.

Always run `air format .` after generating or modifying code. The binary
of air is probably not on the PATH but is typically found inside the Air
extension used by Positron, e.g. something like
`~/.positron/extensions/posit.air-vscode-0.18.0/bundled/bin/air`.

## Development Workflow

**Testing** Place tests in `tests/testthat/test-{name}.R` alongside
corresponding source files. Run tests with `devtools::test()` or
`devtools::test_file("tests/testthat/test-{name}.R")`. Do NOT use
`test_active_file()`. All new code requires accompanying tests.

**Documentation** After modifying roxygen2 comments, run
`devtools::document()` to regenerate documentation. Export all
user-facing functions with proper roxygen2 documentation. Add new
function topics to the appropriate section in `_pkgdown.yml`. Use
sentence case for documentation headings.

**Code Style** Follow tidyverse style guide conventions. Use
[`cli::cli_abort()`](https://cli.r-lib.org/reference/cli_abort.html) for
error messages with informative formatting. Organize code with
“newspaper style”—main logic first, helper functions below.

## Key Technical Details

**Architecture** - Edition 2 (default since v2.0.0): Delegates to
[`vroom::vroom()`](https://vroom.tidyverse.org/reference/vroom.html) for
multi-threaded, lazy parsing - Edition 1 (legacy): Single-threaded eager
parser in C++, accessible via `with_edition(1, ...)` or
`local_edition(1)` - C++ code uses cpp11 interface (in `src/`) for
performance-critical operations - Main R code in `R/` provides
user-facing API and column specification system

**Core Functions** - Reading:
[`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
[`read_csv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
[`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
[`read_csv2()`](https://readr.tidyverse.org/dev/reference/read_delim.md),
[`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md),
[`read_table()`](https://readr.tidyverse.org/dev/reference/read_table.md),
[`read_log()`](https://readr.tidyverse.org/dev/reference/read_log.md) -
Writing:
[`write_csv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
[`write_tsv()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
[`write_delim()`](https://readr.tidyverse.org/dev/reference/write_delim.md),
[`format_csv()`](https://readr.tidyverse.org/dev/reference/format_delim.md) -
Low-level:
[`read_lines()`](https://readr.tidyverse.org/dev/reference/read_lines.md),
[`read_file()`](https://readr.tidyverse.org/dev/reference/read_file.md),
[`read_rds()`](https://readr.tidyverse.org/dev/reference/read_rds.md),
[`count_fields()`](https://readr.tidyverse.org/dev/reference/count_fields.md),
[`guess_encoding()`](https://readr.tidyverse.org/dev/reference/encoding.md)

**Column Type System** - Automatic type guessing from sample of rows
(controlled by `guess_max`) - Explicit specification via
[`cols()`](https://readr.tidyverse.org/dev/reference/cols.md),
[`cols_only()`](https://readr.tidyverse.org/dev/reference/cols.md), or
compact string notation - Column parsers:
[`col_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`col_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`col_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`col_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md),
[`col_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`col_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`col_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`col_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md),
[`col_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`col_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md) -
Parse functions:
[`parse_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
etc. - Problems tracking:
[`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)
function to inspect parsing issues

**Locale Support** -
[`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) object
controls region-specific settings: decimal mark, grouping mark,
date/time formats, encoding, timezone - Defaults to US-centric locale
but fully customizable via
[`date_names()`](https://readr.tidyverse.org/dev/reference/date_names.md)
and
[`date_names_langs()`](https://readr.tidyverse.org/dev/reference/date_names.md)

**Performance & Parsing** - Edition 2 uses vroom for fast multi-threaded
parsing and ALTREP lazy evaluation - Progress bars for long operations
(controlled by `readr.show_progress` option) - `num_threads` parameter
to control parallelism - `lazy` parameter to control ALTREP lazy reading
(default FALSE for safety)

**Key Dependencies** - vroom (≥ 1.6.0): Powers Edition 2 parsing - cli
(≥ 3.2.0): Error messages and formatting - tibble: Output format - tzdb
(≥ 0.1.1): Timezone database for datetime parsing

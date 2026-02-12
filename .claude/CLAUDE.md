# readr: Read Rectangular Text Data

## Package Overview

readr provides a fast and friendly way to read rectangular text data from delimited files (CSV, TSV, etc.), fixed-width files, and log files. The package is designed to flexibly parse many types of data found in the wild while cleanly failing when data unexpectedly changes. Part of the core tidyverse.

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
- vroom: Powers Edition 2 parsing
- cli: Error messages and formatting
- tibble: Output format
- tzdb: Timezone database for datetime parsing

# R package development

## Key commands

```
# To run code
Rscript -e "devtools::load_all(); code"

# To run all tests
Rscript -e "devtools::test()"

# To run all tests for files starting with {name}
Rscript -e "devtools::test(filter = '^{name}')"

# To run all tests for R/{name}.R
Rscript -e "devtools::test_active_file('R/{name}.R')"

# To run a single test "blah" for R/{name}.R
Rscript -e "devtools::test_active_file('R/{name}.R', desc = 'blah')"

# To redocument the package
Rscript -e "devtools::document()"

# To check pkgdown documentation
Rscript -e "pkgdown::check_pkgdown()"

# To check the package with R CMD check
Rscript -e "devtools::check()"

# To format code
air format .
```

## Coding

* Always run `air format .` after generating code. If the binary of air is not on the PATH, you can probably find it inside the Air extension used by Positron, e.g. something like `~/.positron/extensions/posit.air-vscode-X.Y.Z/bundled/bin/air`.
* Use the base pipe operator (`|>`) not the magrittr pipe (`%>%`)
* Don't use `_$x` or `_$[["x"]]` since this package must work on R 4.1.
* Use `\() ...` for single-line anonymous functions. For all other cases, use `function() {...}` 

## Testing

- Tests for `R/{name}.R` go in `tests/testthat/test-{name}.R`. 
- All new code should have an accompanying test.
- If there are existing tests, place new tests next to similar existing tests.
- Strive to keep your tests minimal with few comments.

## Documentation

- Every user-facing function should be exported and have roxygen2 documentation.
- Wrap roxygen comments at 80 characters.
- Internal functions should not have roxygen documentation.
- Whenever you add a new (non-internal) documentation topic, also add the topic to `_pkgdown.yml`. 
- Always re-document the package after changing a roxygen2 comment.
- Use `pkgdown::check_pkgdown()` to check that all topics are included in the reference index.

## `NEWS.md`

- Every user-facing change should be given a bullet in `NEWS.md`. Do not add bullets for small documentation changes or internal refactorings.
- Each bullet should briefly describe the change to the end user and mention the related issue in parentheses.
- A bullet can consist of multiple sentences but should not contain any new lines (i.e. DO NOT line wrap).
- If the change is related to a function, put the name of the function early in the bullet.
- Order bullets alphabetically by function name. Put all bullets that don't mention function names at the beginning.

## GitHub

- If you use `gh` to retrieve information about an issue, always use `--comments` to read all the comments.

## Writing

- Use sentence case for headings.
- Use US English.

## Proofreading

If the user asks you to proofread a file, act as an expert proofreader and editor with a deep understanding of clear, engaging, and well-structured writing. 

Work paragraph by paragraph, always starting by making a TODO list that includes individual items for each top-level heading. 

Fix spelling, grammar, and other minor problems without asking the user. Label any unclear, confusing, or ambiguous sentences with a FIXME comment.

Only report what you have changed.

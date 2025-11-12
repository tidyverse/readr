# gmailr: Gmail API Interface for R

## Package Overview

readr FILL THIS IN

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

FILL THIS IN

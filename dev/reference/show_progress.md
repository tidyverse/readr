# Determine whether progress bars should be shown

By default, readr shows progress bars. However, progress reporting is
suppressed if any of the following conditions hold:

- The bar is explicitly disabled by setting
  `options(readr.show_progress = FALSE)`.

- The code is run in a non-interactive session, as determined by
  [`rlang::is_interactive()`](https://rlang.r-lib.org/reference/is_interactive.html).

- The code is run in an RStudio notebook chunk, as determined by
  `getOption("rstudio.notebook.executing")`.

## Usage

``` r
show_progress()
```

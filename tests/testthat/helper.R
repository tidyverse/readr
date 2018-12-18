# Provide helper overriding tibble::all.equal.tbl_df as it requires dplyr
# https://github.com/tidyverse/readr/pull/577
# Using this helper allows us to avoid Suggesting dplyr
all.equal.tbl_df <- function(target, current, ..., check.attributes = FALSE) {
  all.equal.list(target, current, ..., check.attributes = check.attributes)
}

is_bz2_file <- function(x) {

  # Magic number for bz2 is "BZh" in ASCII
  # https://en.wikipedia.org/wiki/Bzip2#File_format
  identical(charToRaw("BZh"), readBin(x, n = 3, what = "raw"))
}

encoded <- function(x, encoding) {
  Encoding(x) <- encoding
  x
}

skip_if_no_clipboard <- function() {
  if (!clipr::clipr_available()) {
    testthat::skip("System clipboard is not available - skipping test.")
  }
  return(invisible(TRUE))
}

with_crayon <- function(expr) {

  old <- options(crayon.enabled = TRUE, crayon.colors = 16)
  crayon::num_colors(forget = TRUE)
  on.exit({
    options(old)
    crayon::num_colors(forget = TRUE)
  })

  force(expr)
}

# Silence R CMD check note
#' @importFrom tibble tibble
NULL

isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

`%||%` <- function(a, b) if (is.null(a)) b else a

is_syntactic <- function(x) make.names(x) == x

#' Determine progress bars should be shown
#'
#' Progress bars are shown _unless_ one of the following is `TRUE`
#' - The bar is explicitly disabled by setting `options(readr.show_progress = FALSE)`
#' - The code is run in a non-interactive session (`interactive()` is `FALSE`).
#' - The code is run in an RStudio notebook chunk.
#' - The code is run by knitr / rmarkdown.
#' @export
show_progress <- function() {
  isTRUE(getOption("readr.show_progress")) && # user disables progress bar
  interactive() && # an interactive session
  !isTRUE(getOption("rstudio.notebook.executing")) && # Not running in an RStudio notebook chunk
  !isTRUE(getOption("knitr.in.progress")) # Not actively knitting a document
}

deparse2 <- function(expr, ..., sep = "\n") {
  paste(deparse(expr, ...), collapse = sep)
}

is_integerish <- function(x) {
  floor(x) == x
}

#' @export
`[.spec_tbl_df` <- function(x, ...) {
  attr(x, "spec") <- NULL
  class(x) <- setdiff(class(x), "spec_tbl_df")
  NextMethod(`[`)
}

#' @importFrom methods setOldClass
setOldClass(c("spec_tbl_df", "tbl_df", "tbl", "data.frame"))

# @export
compare.tbl_df <- function(x, y, ...) {
  attr(x, "spec") <- NULL
  attr(y, "spec") <- NULL

  NextMethod("compare")
}

# @export
compare.col_spec <- function(x, y, ...) {
  x[["skip"]] <- NULL
  y[["skip"]] <- NULL

  NextMethod("compare")
}

is_named <- function(x) {
  nms <- names(x)

  if (is.null(nms)) {
    return(FALSE)
  }

  all(nms != "" & !is.na(nms))
}

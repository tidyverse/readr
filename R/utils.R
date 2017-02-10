# Silence R CMD check note
#' @importFrom tibble tibble
NULL

isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

`%||%` <- function(a, b) if (is.null(a)) b else a

is_syntactic <- function(x) make.names(x) == x

show_progress <- function() {
  isTRUE(getOption("readr.show_progress")) && # user disables progress bar
  interactive() && # an interactive session
  is.null(getOption("knitr.in.progress")) # Not actively knitting a document
}

deparse2 <- function(expr, ..., sep = "\n") {
  paste(deparse(expr, ...), collapse = sep)
}

is_integerish <- function(x) {
  floor(x) == x
}

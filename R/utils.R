# Silence R CMD check note
#' @importFrom tibble tibble
NULL

isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

`%||%` <- function(a, b) if (is.null(a)) b else a

empty_file <- function(x) {
  return(is.character(x) && file.exists(x) && file.info(x, extra_cols = FALSE)$size == 0)
}

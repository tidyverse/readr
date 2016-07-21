# Silence R CMD check note
#' @importFrom tibble tibble
NULL

isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

`%||%` <- function(a, b) if (is.null(a)) b else a

is_syntactic <- function(x) make.names(x) == x

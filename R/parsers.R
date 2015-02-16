parser <- function(type, ...) {
  structure(list(type = type, ...), class = "parser")
}

#' @export
print.parser <- function(x, ...) {
  cat("<", x$type, "_parser>\n", sep = "")
}

find_parser <- function(name) {
  get(paste0(name, "_parser"), envir = asNamespace("fastread"))()
}

#' Define how to parse each column
#'
#' @name parser
NULL

#' @param trim If \code{TRUE}, will trim off any leading or trailing whitespace.
#' @rdname parser
#' @export
character_parser <- function(trim = TRUE) {
  parser("character", trim = trim)
}

#' @rdname parser
#' @export
integer_parser <- function() {
  parser("integer")
}

#' @rdname parser
#' @export
double_parser <- function() {
  parser("double")
}

#' @rdname parser
#' @export
logical_parser <- function() {
  parser("logical")
}

#' @rdname parser
#' @param levels A character vector listing all valid levels of the factor.
#' @param ordered Create an ordered factor?
#' @export
factor_parser <- function(levels, ordered = FALSE) {
  parser("factor", levels = levels, ordered = ordered)
}

#' @rdname parser
#' @export
skip_parser <- function() {
  parser("skip")
}


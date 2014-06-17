parser <- function(type, ...) {
  structure(list(type = type, params = list(...)), class = "parser")
}

#' Define how to parse each column
#'
#' @objname parser
NULL

#' @param trim If \code{TRUE}, will trim off any leading or trailing whitespace.
#' @rdname parser
#' @export
character_parser <- function(trim = FALSE) {
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
#' @export
factor_parser <- function(levels, ordered = FALSE) {
  parser("factor", levels = levels, ordered = ordered)
}

#' @rdname parser
#' @export
skip_parser <- function() {
  parser("skip")
}


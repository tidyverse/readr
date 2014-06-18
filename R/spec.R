#' Generate a spec object.
#'
#' A spec defines how a file will be read from disk. In most cases, you will
#' not define yourself, but instead you will use \code{\link{guess_spec}} to
#' guess from the contents of the file.
#'
#' @param parsers A list of parsers used to control how each column is turned
#'   into an R data frame. If \code{NULL}, \code{\link{guess_parsers}()} will
#'   do its best to print the correct format.
#'
#'   Optionally, \code{parsers} can be a named list. If \code{header = TRUE},
#'   then parsers will be matched to column names, and any unmatched columns
#'   will not be included in the output. If \code{header = FALSE}, the names
#'   be used to name the output columns, and there must be one parser per
#'   column.
#' @param header Does the first line of the file specify column names?
#'   If \code{TRUE}, the first row will be used to define column
#'   names. If \code{FALSE}, columns will be named given names X1-Xn, unless
#'   \code{parsers} is a named list.
#' @param field_delim The delimiter between fields. Either a character vector
#'   or \code{\link{whitespace}()} meaning to split on any whitespace.
#' @param comment_char If not \code{NULL}, any lines that start with this
#'   string will be skipped.
#' @param na_strings A character vector of providing strings which should be
#'   converted to NA in R.
#' @param skip Skip this many lines before beginning parsing.
#' @export
spec <- function(parsers, header = TRUE, field_delim = ",",
                 comment_char = NULL, na_strings = "NA",
                 skip = 0) {

  structure(
    list(
      parsers = parsers,
      header = header,
      field_delim = field_delim,
      comment_char = comment_char,
      na_strings = na_strings,
      skip = skip
    ),
    class = "spec"
  )
}

#' @export
#' @rdname spec
whitespace <- function() list("whitespace")

#' Generate a spec object.
#'
#' A spec defines how a file will be read from disk. In most cases, you will
#' not define yourself, but instead you will use \code{\link{guess_spec}} to
#' guess from the contents of the file.
#'
#' @param col_parsers A list of vector parsers describing to how to
#'   parser each individual column
#' @param header If \code{TRUE}, the first row will be used to define column
#'   names. If \code{FALSE}, columns will be given names X1-Xn.
#' @param line_delim The delimiter between lines, usually \code{"\n"}
#' @param field_delim The delimiter between fields. Either a character vector
#'   or XXX meaning to split on any whitespace.
#' @param na_string A character vector of strings which should be converted to
#'   NA in R.
#' @param comment_char Any lines starting with this character will be not be
#'   processed.
#' @param skip Skip this many lines before beginning parsing.
#' @export
spec <- function(col_parsers, header = TRUE, line_delim = "\n",
                 field_delim = ",", comment_char = "#", na_string = "NA",
                 skip = 0) {

  structure(
    list(
      col_parsers = col_parsers,
      header = header,
      line_delim = line_delim,
      field_delim = field_delim,
      na_string = na_string,
      comment_char = comment_char,
      skip = skip
    ),
    class = "spec"
  )
}

#' File parsing specification.
#'
#' Parsing a delimited file is naturally composed of three pieces:
#' parsing a file into lines, parsing each line in to fields, then
#' converting each field into an R vector, forming the columns of a data frame.
#' Parsing a fixed width file does not decompose in this way, because while
#' a delimted file is ragged on disk, a fixed width file is a 2d grid.
#'
#' @param line,field,column Line, field and column specification as created by
#'   \code{\link{line_spec}}, \code{\link{field_spec}} and \code{column_spec}.
#' @name file_spec
NULL

#' @export
#' @rdname file_spec
delim_spec <- function(line, field, column) {
  structure(
    list(
      line = line,
      field = field,
      column = column
    ),
    class = c("delim_spec", "file_spec", "spec")
  )
}

#' @rdname file_spec
#' @param widths,start,end Either specify the column positions with their
#'   widths, or by providing start and ending positions.
#' @export
fwf_spec <- function(widths = NULL, start = NULL, end = NULL, column = NULL) {
  ok <- !is.null(widths) && is.null(start) && is.null(end) ||
        is.null(widths) && !is.null(start) && !is.null(end)
  if (!ok) {
    stop("Must supply either widths or both start and end", call. = FALSE)
  }
  if (is.null(starts)) {
    pos <- cumsum(c(0, widths))
    start <- pos[1]
    end <- pos[-length(pos)] - 1
  }

  structure(
    list(
      start = start,
      end = end,
      column = column
    ),
    class = c("fwf_spec", "file_spec", "spec")
  )
}

#' Line parsing specification
#'
#' @param skip Skip this many lines before beginning parsing.
#' @param comment_char If not \code{""}, all content after this character
#'   is ignored.
#' @param delim Delimiter between lines.
#' @export
line_spec <- function(skip = 0, comment = "", delim = "\n") {
  structure(
    list(
      delim = delim,
      skip = skip,
      comment = comment
    ),
    class = c("line_spec", "spec")
  )
}

#' Field parsing specification for delimited files.
#'
#' @param delim Delimiter between fields
#' @param quote Quoting character. Quotes are not preserved in the output.
#' @param collapse Collapse multiple delimiters into one. (Mostly useful when
#'   the delimiter is a space).
#' @param backslash_escape Do backslashes escape the following character?
#' @param double_escape Does doubling the quoting character escape it?
#' @param strict If \code{TRUE}, will throw an error if there are any
#'   unterminated strings or quotes.
#' @export
delimited_field_spec <- function(delim, quote = '"', collapse = FALSE,
                                 backslash_escape = FALSE,
                                 double_escape = FALSE,
                                 strict = FALSE) {
  structure(
    list(
      delim = delim,
      quote = quote,
      collapse = collapse,
      backslash_escape = backslash_escape,
      double_escape = double_escape,
      strict = strict
    ),
    class = c("delimited_field_spec", "field_spec", "spec")
  )
}

#' Column parsign specification.
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
#' @param na_strings A character vector of providing strings which should be
#'   converted to NA in R.
#' @export
column_spec <- function(parsers, header = TRUE, na_strings = "NA") {
  structure(
    list(
      parsers = parsers,
      header = header,
      field_delim = field_delim,
      comment_char = comment_char,
      na_strings = na_strings,
      skip = skip
    ),
    class = c("column_spec", "spec")
  )
}

#' @export
#' @rdname spec
whitespace <- function() list("whitespace")

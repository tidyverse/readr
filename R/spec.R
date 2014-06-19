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
#' @param n If not 0, parse at most this many lines from the file.
#' @param comment If not \code{""}, all content after this character
#'   is ignored.
#' @param delim Delimiter between lines.
#' @export
line_spec <- function(skip = 0, n = 0, comment = "", delim = "\n") {
  structure(
    list(
      delim = delim,
      skip = skip,
      n = n,
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
field_spec <- function(delim, quote = '"', collapse = FALSE,
                       backslash_escape = FALSE, double_escape = FALSE,
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
#'   into an R data frame. The elements of \code{parsers} can be named to match
#'   the columns. Any columns not included will not be included in the output
#'   data frame.
#' @param col_names A character vector naming the columns.
#' @param na_strings A character vector of providing strings which should be
#'   converted to NA in R.
#' @return A list:
#' \item{parsers}{A list of parsers, in the same order as col_names}
#' \item{col_names}{}
#' \item{na_strings}{}
#' @export
column_spec <- function(parsers, col_names, na_strings = "NA") {
  if (is.null(names(parsers))) {
    if (length(parsers) != length(col_names)) {
      stop("Unnamed parsers must have the same length as col_names",
        call. = FALSE)
    }
  } else {
    bad_names <- setdiff(names(parsers), col_names)
    if (length(bad_names) > 0) {
      stop("The following named parsers don't match the column names: ",
        paste0(bad_names, collapse = ", "), call. = FALSE)
    }

    skip <- setdiff(col_names, names(parsers))
    parsers[skip] <- rep(list("skip"), length(skip))

    parsers <- parsers[match(names(parsers), col_names)]
  }

  structure(
    list(
      parsers = parsers,
      col_names = col_names,
      na_strings = na_strings
    ),
    class = c("column_spec", "spec")
  )
}

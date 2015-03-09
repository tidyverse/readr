fwf_spec <- function(widths = NULL, start = NULL, end = NULL, column = NULL) {
  ok <- !is.null(widths) && is.null(start) && is.null(end) ||
        is.null(widths) && !is.null(start) && !is.null(end)
  if (!ok) {
    stop("Must supply either widths or both start and end", call. = FALSE)
  }
  if (is.null(start)) {
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

#' Describe column types.
#'
#' @param col_types A list of types used to control how each column is turned
#'   into an R data frame. The elements of \code{col_types} can be named to match
#'   the columns. Any columns not included will not be included in the output
#'   data frame.
#'
#'   Alternatively, you can use string where each character represents
#'   one column. c = character, d = double, i = integer, l = logical and
#'   \code{_} skips the column.
#' @param col_names A character vector naming the columns.
#' @return A list:
#' \item{parsers}{A list of parsers, in the same order as col_names}
#' \item{col_names}{}
#' @export
#' @examples
#' columns("ccd", c("a", "b", "c"))
columns <- function(col_types, col_names) {
  if (is.character(col_types)) {
    col_types <- parse_parser_string(col_types)
  }

  stopifnot(is.list(col_types))
  is_parser <- vapply(col_types, inherits, "collector", FUN.VALUE = logical(1))
  if (any(!is_parser)) {
    stop("Some parsers are not S3 parser objects: ",
      paste(which(!is_parser), collapse = ", "), call. = FALSE)
  }

  if (is.null(names(col_types))) {
    if (length(col_types) != length(col_names)) {
      stop("Unnamed parsers must have the same length as col_names",
        call. = FALSE)
    }
  } else {
    bad_names <- setdiff(names(col_types), col_names)
    if (length(bad_names) > 0) {
      stop("The following named parsers don't match the column names: ",
        paste0(bad_names, collapse = ", "), call. = FALSE)
    }

    skip <- setdiff(col_names, names(col_types))
    col_types[skip] <- rep(list(col_skip()), length(skip))

    col_types <- col_types[match(names(col_types), col_names)]
  }

  structure(
    list(
      col_types = col_types,
      col_names = col_names
    ),
    class = c("column_spec", "spec")
  )
}


parse_parser_string <- function(x) {
  letters <- strsplit(x, "")[[1]]
  lookup <- list(
    c = col_character(),
    d = col_double(),
    i = col_integer(),
    l = col_logical(),
    "_" = col_skip()
  )

  bad <- setdiff(letters, names(lookup))
  if (length(bad) > 0) {
    stop("Unknown shortcuts: ", paste(unique(bad), collapse = ", "))
  }

  unname(lookup[letters])
}

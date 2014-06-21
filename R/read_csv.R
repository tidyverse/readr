#' Read a delimited file.
#'
#' \code{read_delim} is usually 5-15x faster than \code{\link{read.delim}}, and
#' provides substantially more feedback about what's going on. It produces a
#' data frame inline with modern R usage: col names are left as is, factors
#' are never created by default, and row names are never used. \code{read_csv}
#' is a version of \code{read_delim} where \code{delim} is set to ",".
#'
#' @param file Path to a file, or a connection object.
#' @param delim Field delimiter.
#' @inheritParams column_spec
#' @param ... Other parameters passed on to \code{\link{build_delim_spec}}.
#'   These are not normally necessary, but maybe be useful if you have
#'   an unusually formatted file.
#' @export
#' @return A data frame with additional class \code{"tbl_df"}.
read_delim <- function(file, delim, parsers = NULL, col_names = TRUE, ...,
                       na_strings = "NA") {
  spec <- build_delim_spec(file, parsers, col_names = col_names,
    na_strings = na_strings, ...)

  if (is.character(file)) {
    path <- normalizePath(file)
    read_csv_from_file(path, spec$column$parsers, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  } else {
    read_csv_from_connection(file, spec$column$parsers, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  }
}

#' @rdname read_delim
read_csv <- function(file, parsers = NULL, col_names = TRUE, ...,
                     na_strings = "NA") {

  read_delim(file, ",", parsers = parser, col_names = col_names, ...,
    na_strings = na_strings)
}

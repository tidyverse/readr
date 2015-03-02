#' Read a delimited file.
#'
#' \code{read_delim} is usually 5-15x faster than \code{\link{read.delim}}, and
#' provides substantially more feedback about what's going on. It produces a
#' data frame in line with modern R usage: col names are left as is, factors
#' are never created by default, and row names are never used. \code{read_csv}
#' is a version of \code{read_delim} where \code{delim} is set to ",".
#'
#' @param file Path to a file, or a connection object.
#' @param delim the field delimiter to use, such as "," for a comma-separated file,
#'   or "\\t" for a tab-separated file.
#' @inheritParams column_spec
#' @param ... Other parameters passed on to \code{\link{build_delim_spec}}.
#'   These are not normally necessary, but maybe be useful if you have
#'   an unusually formatted file.
#' @export
#' @return A data frame with the additional class \code{"tbl_df"}.
read_delim <- function(file, delim = NULL, parsers = NULL, col_names = TRUE,
                       ..., na_strings = "NA") {
  file <- check_file(file)
  spec <- build_delim_spec(file, delim = delim, parsers = parsers,
    col_names = col_names, na_strings = na_strings, ...)

  if (is.character(file)) {
    read_csv_from_file(file, spec$column$parsers, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  } else {
    read_csv_from_connection(file, spec$column$parsers, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  }
}

#' @rdname read_delim
#' @export
read_csv <- function(file, parsers = NULL, col_names = TRUE, ...,
                     na_strings = "NA") {

  read_delim(file, ",", parsers = parsers, col_names = col_names, ...,
    na_strings = na_strings)
}

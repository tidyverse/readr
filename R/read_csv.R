#' Read a csv file.
#'
#' \code{read_csv} is usually 5-15x faster than \code{\link{read.csv}}, and
#' provides substantially more feedback about what's going on. It produces a
#' data frame inline with modern R usage: col names are left as is, factors
#' are never created by default, and row names are never used.
#'
#' @param file Path to a file, or a connection object.
#' @inheritParams column_spec
#' @param ... Other parameters passed on to \code{\link{build_csv_spec}}.
#'   These are not normally necessary, but maybe be useful if you have
#'   an unusually formatted csv file.
#' @export
#' @return A data frame with additional class \code{"tbl_df"}.
read_csv <- function(file, parsers = NULL, col_names = TRUE,
                     na_strings = "NA", ...) {
  spec <- build_csv_spec(file, parsers, col_names = col_names,
    na_strings = na_strings, ...)

  classes <- vpluck(spec$column$parsers, 1)

  if (is.character(file)) {
    path <- normalizePath(file)
    read_csv_from_file(path, classes, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  } else {
    read_csv_from_connection(file, classes, spec$column$col_names,
      n = as.integer(spec$line$n), skip = as.integer(spec$line$skip))
  }
}

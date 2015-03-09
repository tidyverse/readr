#' Standardise column names
#'
#' @param col_names Either \code{TRUE}, \code{FALSE} or a character vector
#'   of column names.
#'
#'   If \code{TRUE}, the first row of the input will be used as the column
#'   names, and will not be included in the data frame. If \code{FALSE}, column
#'   names will be generated automatically: X1, X2, X3 etc.
#'
#'   If \code{col_names} is a character vector, the values will be used as the
#'   names of the columns, and the first row of the input will be read into
#'   the first row of the output data frame.
#' @export
#' @keywords internal
col_names_standardise <- function(col_names, header) {
  if (isTRUE(col_names)) {
    header
  } else if (isFALSE(col_names)) {
    paste0("X", seq_along(header))
  } else {
    if (!is.character(col_names)) {
      stop("`col_names` must be TRUE, FALSE or a character vector", call. = FALSE)
    }
    col_names
  }
}

read_csv <- function(input, classes, n = 0, header = TRUE, filter_pattern = NULL){

  if( is.null(filter_pattern) ){
    read_csv_impl( input, classes, n, header )
  } else {
    assert_that( is.logical(filter_pattern) )
    read_csv_impl_filter_pattern( input, classes, n, header, filter_pattern )
  }

}

#' Read a csv file
#'
#' Compared to \code{\link{read.csv}} this function is considerably faster.
#'
#' @param file Path to a file, or a connection object.
#' @inheritParams column_spec
#' @param ... Other parameters passed on to \code{\link{build_csv_spec}}.
#'   These are not normally necessary, but you may need them if you have
#'   an unusually formatted csv file.
#' @export
#' @return A data frame with additionanl class \code{"tbl_df"}.
read_csv <- function(file, parsers = NULL, col_names = TRUE,
                     na_strings = "NA", ...) {
  spec <- build_csv_spec(file, parsers, col_names = col_names,
    na_strings = na_strings, ...)

  spec
}

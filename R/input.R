#' Read a file into a string.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @export
#' @examples
#' read_file(file.path(R.home(), "COPYING"))
read_file <- function(file, locale = default_locale()) {
  ds <- datasource(file)
  read_file_(ds, locale)
}

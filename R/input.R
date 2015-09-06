#' Read a file into a string.
#'
#' @inheritParams datasource
#' @export
#' @examples
#' read_file(file.path(R.home(), "COPYING"))
read_file <- function(file, skip = 0) {
  ds <- datasource(file, skip = skip)
  read_file_(ds)
}

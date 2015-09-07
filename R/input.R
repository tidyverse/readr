#' Read a file into a string.
#'
#' @inheritParams datasource
#' @export
#' @examples
#' read_file(file.path(R.home(), "COPYING"))
read_file <- function(file) {
  ds <- datasource(file)
  read_file_(ds)
}

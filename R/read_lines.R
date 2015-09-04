#' Read lines from a file or string.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @param n_max Number of lines to read. If \code{n} is -1, all lines in
#'   file will be read.
#' @return A character vector with one element for each line.
#' @export
#' @examples
#' read_lines(system.file("extdata/mtcars.csv", package = "readr"))
#' read_lines("1\n\n2")
#' read_lines("\n")
read_lines <- function(file, n_max = -1L, progress = interactive()) {
  ds <- datasource(file)
  read_lines_(ds, n_max = n_max, progress = progress)
}

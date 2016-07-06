#' Read lines from a file or string.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @param n_max Number of lines to read. If \code{n_max} is -1, all lines in
#'   file will be read.
#' @return \code{read_lines}: A character vector with one element for each line.
#'   \code{read_lines_raw}: A list containing a raw vector for each line.
#' @export
#' @examples
#' read_lines(system.file("extdata/mtcars.csv", package = "readr"))
#' read_lines("1\n\n2")
#' read_lines("\n")
#'
#' read_lines_raw(system.file("extdata/mtcars.csv", package = "readr"))
read_lines <- function(file, skip = 0, n_max = -1L,
                       locale = default_locale(),
                       progress = interactive()) {
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)
  read_lines_(ds, locale_ = locale, n_max = n_max, progress = progress)
}

#' @export
#' @rdname read_lines
read_lines_raw <- function(file, skip = 0, n_max = -1L, progress = interactive()) {
  if (empty_file(file)) {
    return(list())
  }
  ds <- datasource(file, skip = skip)
  read_lines_raw_(ds, n_max = n_max, progress = progress)
}

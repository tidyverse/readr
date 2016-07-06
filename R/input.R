#' Read a file into a string.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @return \code{read_file}: A length 1 character vector with the entire file contents.
#'   \code{read_lines_raw}: A raw vector with the entire file contents.
#' @export
#' @examples
#' read_file(file.path(R.home(), "COPYING"))
#'
#' read_lines_raw(system.file("extdata/mtcars.csv", package = "readr"))
read_file <- function(file, locale = default_locale()) {
  if (empty_file(file)) {
    return("")
  }

  ds <- datasource(file)
  read_file_(ds, locale)
}

#' @export
#' @rdname read_file
read_file_raw <- function(file) {
  if (empty_file(file)) {
    return("")
  }

  ds <- datasource(file)
  read_file_raw_(ds)
}

#' Read a file into a string or raw vector
#'
#' Reads a complete file into a single object: either a character vector of
#' length one, or a raw vector. Raw vectors are useful when dealing with
#' binary data, or if you have text data with unknown encoding.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @return
#'   \code{read_file}: A length 1 character vector.
#'   \code{read_lines_raw}: A raw vector.
#' @export
#' @examples
#' read_file(file.path(R.home("doc"), "AUTHORS"))
#' read_file_raw(file.path(R.home("doc"), "AUTHORS"))
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
    return(raw())
  }

  ds <- datasource(file)
  read_file_raw_(ds)
}

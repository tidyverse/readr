#' Read/write a complete file
#'
#' `read_file()` reads a complete file into a single object: either a
#' character vector of length one, or a raw vector. `write_file()` takes a
#' single string, or a raw vector, and writes it exactly as is.  Raw vectors
#' are useful when dealing with binary data, or if you have text data with
#' unknown encoding.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @return
#'   `read_file`: A length 1 character vector.
#'   `read_lines_raw`: A raw vector.
#' @export
#' @examples
#' read_file(file.path(R.home("doc"), "AUTHORS"))
#' read_file_raw(file.path(R.home("doc"), "AUTHORS"))
#'
#' tmp <- tempfile()
#'
#' x <- format_csv(mtcars[1:6, ])
#' write_file(x, tmp)
#' identical(x, read_file(tmp))
#'
#' read_lines(x)
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

#' @inherit write_lines
#' @rdname read_file
#' @export
write_file <- function(x, path, append = FALSE) {
  path <- normalizePath(path, mustWork = FALSE)

  if (is.raw(x)) {
    write_file_raw_(x, path, append = append)
  } else if (is.character(x)) {
    write_file_(x, path, append = append)
  } else {
    stop("`x` must be a raw or character vector", call. = FALSE)
  }

  invisible(x)
}

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
#' @param x A single string, or a raw vector to write to disk.
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

  ds <- datasource(file, skip_empty_rows = FALSE)
  read_file_(ds, locale)
}

#' @export
#' @rdname read_file
read_file_raw <- function(file) {
  if (empty_file(file)) {
    return(raw())
  }

  ds <- datasource(file, skip_empty_rows = FALSE)
  read_file_raw_(ds)
}

#' @inherit write_lines
#' @rdname read_file
#' @export
write_file <- function(x, path, append = FALSE) {
  path <- standardise_path(path, input = FALSE)
  if (!isOpen(path)) {
    on.exit(close(path), add = TRUE)
    if (isTRUE(append)) {
      open(path, "ab")
    } else {
      open(path, "wb")
    }
  }
  if (is.raw(x)) {
    write_file_raw_(x, path)
  } else {
    write_file_(x, path)
  }

  invisible(x)
}

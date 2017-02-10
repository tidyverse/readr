#' Read/write lines to/from a file
#'
#' `read_lines()` reads up to `n_max` lines from a file. New lines are
#' not included in the output. `read_lines_raw()` produces a list of raw
#' vectors, and is useful for handling data with unknown encoding.
#' `write_lines()` takes a character vector or list of raw vectors, appending a
#' new line after each entry.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @param n_max Number of lines to read. If `n_max` is -1, all lines in
#'   file will be read.
#' @return `read_lines()`: A character vector with one element for each line.
#'   `read_lines_raw()`: A list containing a raw vector for each line.
#' @export
#' @examples
#' read_lines(file.path(R.home("doc"), "AUTHORS"), n_max = 10)
#' read_lines_raw(file.path(R.home("doc"), "AUTHORS"), n_max = 10)
#'
#' tmp <- tempfile()
#'
#' write_lines(rownames(mtcars), tmp)
#' read_lines(tmp)
#' read_file(tmp) # note trailing \n
#'
#' write_lines(airquality$Ozone, tmp, na = "-1")
#' read_lines(tmp)
read_lines <- function(file, skip = 0, n_max = -1L,
                       locale = default_locale(),
                       na = character(),
                       progress = show_progress()) {
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)
  read_lines_(ds, locale_ = locale, na = na, n_max = n_max, progress = progress)
}

#' @export
#' @rdname read_lines
read_lines_raw <- function(file, skip = 0, n_max = -1L, progress = show_progress()) {
  if (empty_file(file)) {
    return(list())
  }
  ds <- datasource(file, skip = skip)
  read_lines_raw_(ds, n_max = n_max, progress = progress)
}

#' @inheritParams write_delim
#' @return `write_lines()` returns `x`, invisibly.
#' @export
#' @rdname read_lines
write_lines <- function(x, path, na = "NA", append = FALSE) {
  path <- normalizePath(path, mustWork = FALSE)
  if (is.list(x) && all(vapply(x, inherits, logical(1), "raw"))) {
    write_lines_raw_(x, path, append)
  } else {
    x <- as.character(x)
    write_lines_(x, path, na, append)
  }

  invisible(x)
}


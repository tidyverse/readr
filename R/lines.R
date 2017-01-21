#' Read/write lines to/from a file
#'
#' \code{read_lines} reads up to \code{n_max} lines from a file. New lines are
#' not included in the output. \code{read_lines_raw} produces a list of raw
#' vectors, and is useful for handling data with unknown encoding.
#' \code{write_lines} takes a character vector, appending a new line
#' after each entry.
#'
#' @inheritParams datasource
#' @inheritParams read_delim
#' @param n_max Number of lines to read. If \code{n_max} is -1, all lines in
#'   file will be read.
#' @return \code{read_lines}: A character vector with one element for each line.
#'   \code{read_lines_raw}: A list containing a raw vector for each line.
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
                       progress = NULL) {
  progress <- progress %||% progress_defaults()
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)
  read_lines_(ds, locale_ = locale, na = na, n_max = n_max, progress = progress)
}

#' @export
#' @rdname read_lines
read_lines_raw <- function(file, skip = 0, n_max = -1L, progress = NULL) {
  if (empty_file(file)) {
    return(list())
  }
progress <- progress %||% progress_defaults()
  ds <- datasource(file, skip = skip)
  read_lines_raw_(ds, n_max = n_max, progress = progress)
}

#' @inheritParams write_delim
#' @return \code{write_lines} returns \code{x}, invisibly.
#' @export
#' @rdname read_lines
write_lines <- function(x, path, na = "NA", append = FALSE) {
  x <- as.character(x)

  path <- normalizePath(path, mustWork = FALSE)

  write_lines_(x, path, na, append)

  invisible(x)
}


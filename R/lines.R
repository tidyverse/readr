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
#' @param x A character vector or list of raw vectors to write to disk.
#' @param sep The line separator. Defaults to `\\n`, commonly used on POSIX
#' systems like macOS and linux. For native windows (CRLF) separators use
#' `\\r\\n`.
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
read_lines <- function(file, skip = 0, skip_empty_rows = FALSE, n_max = Inf,
                       locale = default_locale(),
                       na = character(),
                       progress = show_progress()) {
  if (edition_first()) {
    if (is.infinite(n_max)) {
      n_max = -1L
    }
    if (empty_file(file)) {
      return(character())
    }
    ds <- datasource(file, skip = skip, skip_empty_rows = skip_empty_rows, skip_quote = FALSE)
    return(read_lines_(ds, skip_empty_rows = skip_empty_rows, locale_ = locale, na = na, n_max = n_max, progress = progress))
  }

  if (!missing(skip_empty_rows)) {
    lifecycle::deprecate_soft("2.0.0", "read_lines(skip_empty_rows = )")
  }

  if (!missing(na)) {
    lifecycle::deprecate_soft("2.0.0", "read_lines(na = )")
  }

  vroom::vroom_lines(file, skip = skip, locale = locale, n_max = n_max, progress = progress)
}

#' @export
#' @rdname read_lines
read_lines_raw <- function(file, skip = 0,
                           n_max = -1L, progress = show_progress()) {
  if (empty_file(file)) {
    return(list())
  }
  ds <- datasource(file, skip = skip, skip_empty_rows = FALSE, skip_quote = FALSE)
  read_lines_raw_(ds, n_max = n_max, progress = progress)
}

#' @inheritParams write_delim
#' @param path \Sexpr[results=rd, stage=render]{lifecycle::badge("deprecated")}
#' @return `write_lines()` returns `x`, invisibly.
#' @export
#' @rdname read_lines
write_lines <- function(x, file, sep = "\n", na = "NA", append = FALSE, path = deprecated()) {
  if (is_present(path)) {
    deprecate_warn("1.4.0", "write_lines(path = )", "write_lines(file = )")
    file <- path
  }

  is_raw <- is.list(x) && inherits(x[[1]], "raw")
  if (!is_raw) {
    x <- as.character(x)
  }

  file <- standardise_path(file, input = FALSE)
  if (!isOpen(file)) {
    on.exit(close(file), add = TRUE)
    open(file, if (isTRUE(append)) "ab" else "wb")
  }
  if (is_raw) {
    write_lines_raw_(x, file, sep)
  } else {
    write_lines_(x, file, na, sep)
  }

  invisible(x)
}

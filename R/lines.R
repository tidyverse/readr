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
#' read_lines(tmp, lazy = FALSE)
#' read_file(tmp) # note trailing \n
#'
#' write_lines(airquality$Ozone, tmp, na = "-1")
#' read_lines(tmp)
read_lines <- function(
  file,
  skip = 0,
  skip_empty_rows = FALSE,
  n_max = Inf,
  locale = default_locale(),
  na = character(),
  lazy = should_read_lazy(),
  num_threads = readr_threads(),
  progress = show_progress()
) {
  if (edition_first()) {
    if (is.infinite(n_max)) {
      n_max <- -1L
    }
    if (empty_file(file)) {
      return(character())
    }
    ds <- datasource(
      file,
      skip = skip,
      skip_empty_rows = skip_empty_rows,
      skip_quote = FALSE
    )
    return(read_lines_(
      ds,
      skip_empty_rows = skip_empty_rows,
      locale_ = locale,
      na = na,
      n_max = n_max,
      progress = progress
    ))
  }

  vroom::vroom_lines(
    file,
    skip = skip,
    locale = locale,
    n_max = n_max,
    progress = progress,
    altrep = lazy,
    skip_empty_rows = skip_empty_rows,
    na = na,
    num_threads = num_threads
  )
}

#' @export
#' @rdname read_lines
read_lines_raw <- function(
  file,
  skip = 0,
  n_max = -1L,
  num_threads = readr_threads(),
  progress = show_progress()
) {
  if (empty_file(file)) {
    return(list())
  }
  ds <- datasource(
    file,
    skip = skip,
    skip_empty_rows = FALSE,
    skip_quote = FALSE
  )
  read_lines_raw_(ds, n_max = n_max, progress = progress)
}

#' @inheritParams write_delim
#' @return `write_lines()` returns `x`, invisibly.
#' @export
#' @rdname read_lines
write_lines <- function(
  x,
  file,
  sep = "\n",
  na = "NA",
  append = FALSE,
  num_threads = readr_threads()
) {
  is_raw <- is.list(x) && inherits(x[[1]], "raw")

  if (is_raw || edition_first()) {
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

    return(invisible(x))
  }

  vroom::vroom_write_lines(
    as.character(x),
    file,
    eol = sep,
    na = na,
    append = append,
    num_threads = num_threads
  )

  invisible(x)
}

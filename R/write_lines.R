#' Write line to a file or string.
#'
#' @inheritParams write_delim
#' @return returns the input \code{x} invisibly.
#' @export
#' @examples
#' tmp <- tempfile()
#' write_lines(rownames(mtcars), tmp)
#'
#' write_lines(airquality$Ozone, tmp, na = "-1")
write_lines <- function(x, path, na = "NA", append = FALSE) {
  x <- as.character(x)

  path <- normalizePath(path, mustWork = FALSE)

  write_lines_(x, path, na, append)

  invisible(x)
}


#' @rdname write_lines
#' @export
write_file <- function(x, path, append = FALSE) {
  path <- normalizePath(path, mustWork = FALSE)

  if (is.raw(x)) {
    write_file_raw_(x, path, append = append)
  } else {
    stopifnot(is.character(x))

    write_file_(x, path, append = append)
  }

  invisible(x)
}

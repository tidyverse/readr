#' Write lines/ a file
#'
#' \code{write_lines} takes a character vector, appending a new line
#' after entry. \code{write_file} takes a single string, or a raw vector,
#' and writes it exactly as is.
#'
#' @inheritParams write_delim
#' @return The input \code{x}, invisibly.
#' @export
#' @examples
#' tmp <- tempfile()
#'
#' write_lines(rownames(mtcars), tmp)
#' read_lines(tmp)
#' read_file(tmp) # note trailing \n
#'
#' write_lines(airquality$Ozone, tmp, na = "-1")
#' read_lines(tmp)
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
  } else if (is.character(x)) {
    write_file_(x, path, append = append)
  } else {
    stop("`x` must be a raw or character vector", call. = FALSE)
  }

  invisible(x)
}

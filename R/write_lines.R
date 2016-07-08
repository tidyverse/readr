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

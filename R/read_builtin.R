#' Read built-in object from package
#'
#' Consistent wrapper around [data()] that forces the promise. This is also a
#' stronger parallel to loading data from a file.
#'
#' @param x Name (character string) of data set to read.
#' @param package Name of package from which to find data set. By default, all
#' attached packages are searched and then the 'data' subdirectory (if present)
#' of the current working directory.
#'
#' @return An object of the built-in class of `x`.
#' @export
#' @examples
#' read_builtin("starwars", "dplyr")
#'
#' read_builtin("storms", "dplyr")
#'
read_builtin <- function(x, package = NULL) {
  x <- data(list = list(x), package = package, envir = environment())
  get(x[[1]], envir = environment())
}

#' @param x R object to write to serialise.
#' @param compress Compression method to use: "none", "gz" ,"bz", or "xz".
#' @param ... Additional arguments to connection function. For example, control
#'   the space-time trade-off of different compression methods with
#'   `compression`. See [connections()] for more details.
#' @return `write_rds()` returns `x`, invisibly.
#' @rdname read_rds
#' @export
write_rds <- function(x, path, compress = c("none", "gz", "bz2", "xz"), ...) {

  compress <- match.arg(compress)
  con <- switch(compress,
         none = file(path, ...),
         gz   = gzfile(path, ...),
         bz2  = bzfile(path, ...),
         xz   = xzfile(path, ...))
  on.exit(close(con), add = TRUE)
  saveRDS(x, con)

  invisible(x)
}

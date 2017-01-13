#' Read/write RDS files.
#'
#' Consistent wrapper around [saveRDS()] and [readRDS()].
#' `write_rds()` does not compress by default as space is generally cheaper
#' than time.
#'
#' @param path Path to read from/write to.
#' @keywords internal
#' @export
#' @examples
#' temp <- tempfile()
#' write_rds(mtcars, temp)
#' read_rds(temp)
#'
#' \dontrun{
#' write_rds(mtcars, "compressed_mtc.rds", "xz", compression = 9L)
#' }
read_rds <- function(path) {
  readRDS(path)
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

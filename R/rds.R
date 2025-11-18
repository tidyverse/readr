#' Read/write RDS files.
#'
#' Consistent wrapper around [saveRDS()] and [readRDS()].
#' `write_rds()` does not compress by default as space is generally cheaper
#' than time.
#'
#' @param file The file path to read from/write to.
#' @param refhook A function to handle reference objects.
#' @export
#' @examples
#' temp <- tempfile()
#' write_rds(mtcars, temp)
#' read_rds(temp)
#' \dontrun{
#' write_rds(mtcars, "compressed_mtc.rds", "xz", compression = 9L)
#' }
read_rds <- function(file, refhook = NULL) {
  con <- file(file)
  on.exit(close(con))

  readRDS(con, refhook = refhook)
}


#' @param x R object to write to serialise.
#' @param compress Compression method to use: "none", "gz" ,"bz", or "xz".
#' @param version Serialization format version to be used. The default value is 2
#'    as it's compatible for R versions prior to 3.5.0. See [base::saveRDS()]
#'    for more details.
#' @param ... Additional arguments to connection function. For example, control
#'   the space-time trade-off of different compression methods with
#'   `compression`. See [connections()] for more details.
#' @param text If `TRUE` a text representation is used, otherwise a binary representation is used.
#' @return `write_rds()` returns `x`, invisibly.
#' @rdname read_rds
#' @export
write_rds <- function(
  x,
  file,
  compress = c("none", "gz", "bz2", "xz"),
  version = 2,
  refhook = NULL,
  text = FALSE,
  ...
) {
  compress <- match.arg(compress)
  con <- switch(
    compress,
    none = file(file, ...),
    gz = gzfile(file, ...),
    bz2 = bzfile(file, ...),
    xz = xzfile(file, ...)
  )
  on.exit(close(con), add = TRUE)
  saveRDS(x, con, version = version, refhook = refhook, ascii = text)

  invisible(x)
}

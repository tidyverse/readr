#' Save a data frame to a delimited file.
#'
#' This is about twice as fast as \code{\link{write.csv}}, and never
#' writes row names. \code{output_column} is a generic method used to coerce
#' columns to suitable output.
#'
#' @section Output:
#' Factors are coerced to character. Doubles are coerced to character to
#' take advantage of R's nice output for doubles. POSIXct's are formatted
#' as ISO8601.
#'
#' All columns are encoded as UTF-8.
#'
#' Values are only quoted if needed: if they contain a comma, quote or newline.
#'
#' @param x A data frame to write to disk
#' @param path Path to write to. If \code{""} will return the csv file as
#'   a string.
#' @param append If \code{FALSE}, will create a new file. If \code{TRUE},
#'   will append to an existing file.
#' @param col_names Write columns names at the top of the file?
#' @param delim Delimiter used to seperate values. Defaults to \code{" "}. Must be
#'   a single character.
#' @export
#' @examples
#' cat(write_delim(head(mtcars), "", "_"))
#' cat(write_delim(head(iris), "", ";"))
#'
#' df <- data.frame(x = c("a", '"', ",", "\n"))
#' read_delim(write_delim(df, "", "_"), "_")
write_delim <- function(x, path, delim = " ", append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))
  path <- normalizePath(path, mustWork = FALSE)

  x <- lapply(x, output_column)

  out <- stream_delim(x, path, delim = ',', col_names = col_names, append = append)
  if (path == "") out else invisible()
}

#' @rdname write_delim
#' @export
#' @examples
#' cat(write_csv(head(mtcars), ""))
#' cat(write_csv(head(iris), ""))
#'
#' df <- data.frame(x = c("a", '"', ",", "\n"))
#' read_csv(write_csv(df, ""))
write_csv <- function(x, path, append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))
  path <- normalizePath(path, mustWork = FALSE)

  x <- lapply(x, output_column)

  out <- stream_delim(x, path, delim = ',', col_names = col_names, append = append)
  if (path == "") out else invisible()
}

#' @rdname write_delim
#' @export
#' @examples
#' cat(write_tsv(head(mtcars), ""))
#' cat(write_tsv(head(iris), ""))
#'
#' df <- data.frame(x = c("a", '"', ",", "\n"))
#' read_tsv(write_tsv(df, ""))
write_tsv <- function(x, path, append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))
  path <- normalizePath(path, mustWork = FALSE)

  x <- lapply(x, output_column)

  out <- stream_delim(x, path, delim = '\t', col_names = col_names, append = append)
  if (path == "") out else invisible()
}

#' @rdname write_delim
#' @export
output_column <- function(x) {
  UseMethod("output_column")
}

#' @export
output_column.default <- function(x) {
  if (!is.object(x)) return(x)
  as.character(x)
}

#' @export
output_column.double <- function(x) {
  as.character(x)
}

#' @export
output_column.POSIXt <- function(x) {
  format(x, "%Y-%m-%dT%H:%M:%OSZ", tz = "UTC")
}

#' Write a single R object to file
#'
#' Light wrappers around \code{\link{saveRDS}} with explicit naming. \code{write_rds}
#' never compresses output for speed. \code{write_compressed_rds} tries to guess
#' the best type of compression for your object to obtain the smallest file size.
#'
#' @section guess compression:
#' N.B. this is not yet implemented but there some empirical testing is taking
#' place to come up with something useful.
#' @param x R object to write to serialise.
#' @param path Path to write to.
#' @param compress_fun Compression method to use one of \code{guess},
#' \code{xzfile}, \code{bzfile}, \code{gzfile}.
#' @param compress_amount Level of compression must be in 0:9L
#' @param ... dots
#' @name write_rds
NULL

#' @rdname write_rds
#' @export
#' @examples
#' ## write_rds(mtcars, "mtcars.rds")
write_rds <- function(x, path) {
  saveRDS(x, path, ascii = FALSE, version = NULL, compress = FALSE, refhook = NULL)
}

#' @rdname write_rds
#' @export
#' @examples
#' ## write_compressed_rds(mtcars, "mtcars.rds", compress_fun = gzfile)
write_compressed_rds <- function(x, path, compress_fun = xzfile, compress_amount = 9L, ...) {
  bool <- deparse(substitute(compress_fun)) == c("xzfile", "bzfile", "gzfile")
  if(sum(bool) != 1) stop("compress_fun not found")
  stopifnot(compress_amount >= 0, compress_amount <= 9)

  con <- compress_fun(path, compression = compress_amount, ...)
  saveRDS(x, con)
  on.exit(close(con))
}

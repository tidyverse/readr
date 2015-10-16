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
#' @param path Path to write to.
#' @param append If \code{FALSE}, will overwrite existing file. If \code{TRUE},
#'   will append to existing file. In both cases, if file does not exist a new
#'   file is created.
#' @param col_names Write columns names at the top of the file?
#' @param delim Delimiter used to seperate values. Defaults to \code{" "}. Must be
#'   a single character.
#' @param na String used for missing values. Defaults to NA. Missing values
#'   will never be quoted; strings with the same value as \code{na} will
#'   always be quoted.
#' @return \code{write_*} returns in the input \code{x} invisibily,
#'   \code{format_*} returns a string.
#' @export
#' @examples
#' tmp <- tempfile()
#' write_csv(mtcars, tmp)
#' head(read_csv(tmp))
#'
#' # format_* is useful for testing and reprexes
#' cat(format_csv(head(mtcars)))
#' cat(format_tsv(head(mtcars)))
#' cat(format_delim(head(mtcars), ";"))
#'
#' df <- data.frame(x = c(1, 2, NA))
#' format_csv(df, na = ".")
#'
#' # Quotes are automatically as needed
#' df <- data.frame(x = c("a", '"', ",", "\n"))
#' cat(format_csv(df))
write_delim <- function(x, path, delim = " ", na = "NA", append = FALSE,
                        col_names = !append) {
  stopifnot(is.data.frame(x))
  path <- normalizePath(path, mustWork = FALSE)

  x <- lapply(x, output_column)

  out <- stream_delim(x, path, delim, col_names = col_names, append = append,
    na = na)
  if (path == "") out else invisible()
}

#' @rdname write_delim
#' @export
write_csv <- function(x, path, na = "NA", append = FALSE, col_names = !append) {
  if (identical(path, "")) {
    stop("Please use format_csv instead.", call. = FALSE)
  }

  write_delim(x, path, delim = ',', na = na,append = append,
    col_names = col_names)
  invisible(path)
}


#' @rdname write_delim
#' @export
write_tsv <- function(x, path, na = "NA", append = FALSE, col_names = !append) {
  write_delim(x, path, delim = '\t', na = na, append, col_names)
}

#' @export
#' @rdname write_delim
format_csv <- function(x, na = "NA", append = FALSE, col_names = !append) {
  format_delim(x, delim = ",", na = na, append = append, col_names = col_names)
}

#' @export
#' @rdname write_delim
format_tsv <- function(x, na = "NA", append = FALSE, col_names = !append) {
  format_delim(x, delim = "\t", na = na, append = append, col_names = col_names)
}

#' @export
#' @rdname write_delim
format_delim <- function(x, delim, na = "NA", append = FALSE, col_names = !append) {
  write_delim(x, "", delim = delim, na = na, append = append, col_names = col_names)
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
#' Consistent wrapper around \code{\link{saveRDS}}. \code{write_rds} does not
#' compress by default as space is generally cheaper than time.
#'
#' @param x R object to write to serialise.
#' @param path Path to write to.
#' @param compress Compression method to use: "none", "gz" ,"bz", or "xz".
#' @param ... Additional arguments to connection function. For example, control
#'   the space-time trade-off of different compression methods with
#'   \code{compression}. See \code{\link{connections}} for more details.
#' @export
#' @return The input \code{x}, invisibly.
#' @examples
#' \dontrun{
#' write_rds(mtcars, "mtcars.rds")
#' write_rds(mtcars, "compressed_mtc.rds", "xz", compression = 9L)
#' }
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

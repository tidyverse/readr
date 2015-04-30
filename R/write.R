#' Save a data frame to a csv file.
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

#' @rdname write_csv
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


#' Save a data frame to a csv file.
#'
#' This is about twice as fast as \code{\link{write.csv}}, and never
#' writes row names. Non-atomic vectors are coerced to character vectors
#' with \code{as.character}. All columns are encoded as UTF-8.
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
write_csv <- function(x, path, append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))

  is_object <- vapply(x, is.object, logical(1))
  x[is_object] <- lapply(x[is_object], as.character)

  path <- normalizePath(path, mustWork = FALSE)

  out <- stream_csv(x, path, col_names = col_names, append = append)
  if (path == "") out else invisible()
}


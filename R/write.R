#' Save a data frame to a csv file.
#'
#' This is about twice as fast as \code{\link{write.csv}}, and never
#' writes row names. Non-atomic vectors are coerced to character vectors
#' with \code{as.character}.
#'
#' @param x A data frame to write to disk
#' @param path Path to write to.
#' @param append If \code{FALSE}, will create a new file. If \code{TRUE},
#'   will append to an existing file.
#' @param col_names Write columns names at the top of the file?
#' @export
write_csv <- function(x, path, append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))

  is_object <- vapply(x, is.object, logical(1))
  x[is_object] <- lapply(x[is_object], as.character)

  path <- normalizePath(path, mustWork = FALSE)
  stream_csv(x, path, col_names = col_names, append = append)
}

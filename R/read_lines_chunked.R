#' Read lines from a file or string by chunk.
#'
#' @inheritParams datasource
#' @inheritParams read_delim_chunked
#' @export
read_lines_chunked <- function(file, callback, chunk_size = 10000, skip = 0,
  locale = default_locale(), na = character(), progress = interactive()) {
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)

  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  read_lines_chunked_(ds, locale, na, chunk_size, callback, progress)

  return(callback$result())
}


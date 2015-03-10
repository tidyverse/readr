#' Create a source object.
#'
#' @param file Either a path to a file, a url, a connection, or literal data
#'    (either a single string or a raw vector). Connections and urls are saved
#'    to a temporary file before being read.
#'
#'    Literal data is most useful for examples and tests. It must contain at
#'    least one new line to be recognised as data (instead of a path).
#' @param skip Number of lines to skip before reading data.
#' @keywords internal
#' @export
#' @examples
#' # Literal csv
#' datasource("a,b,c\n1,2,3")
#' datasource(charToRaw("a,b,c\n1,2,3"))
#'
#' # Local path
#' datasource(system.file("extdata/mtcars.csv", package = "readr"))
#'
#' # Connection
#' datasource(rawConnection(charToRaw("abc\n123")))
datasource <- function(file, skip = 0) {
  if (inherits(file, "source")) {
    file
  } else if (inherits(file, "connection")) {
    datasource_file(cache_con(file), skip)
  } else if (is.raw(file)) {
    datasource_raw(file, skip)
  } else if (is.character(file)) {
    if (grepl("\n", file)) {
      datasource_string(file, skip)
    } else if (grepl("^(http|ftp|https)://", file)) {
      tmp <- tempfile()
      download.file(file, tmp, quiet = TRUE, mode = "wb")
      datasource_file(tmp, skip)
    } else {
      datasource_file(file, skip)
    }
  } else {
    stop("`file` must be a string, raw vector or a connection.", call. = FALSE)
  }
}

new_datasource <- function(type, x, skip, ...) {
  structure(list(x, skip = skip, ...),
    class = c(paste0("source_", type), "source"))
}

datasource_string <- function(text, skip) {
  new_datasource("string", text, skip = skip)
}

datasource_file <- function(path, skip) {
  path <- check_file(path)
  new_datasource("file", path, skip = skip)
}

datasource_raw <- function(text, skip) {
  new_datasource("text", text, skip = skip)
}



cache_con <- function(con) {
  tmp <- tempfile()
  tmpcon <- file(tmp, "w+b")
  on.exit(close(tmpcon), add = TRUE)

  if (!isOpen(con)) {
    open(con, "rb")
    on.exit(close(con), add = TRUE)
  }

  while(length(buf <- readBin(con, raw(), 32 * 1024)))
    writeBin(buf, tmpcon)

  return(tmp)
}

check_file <- function(path) {
  if (!file.exists(path)) {
    stop("'", path, "' does not exist",
      if (!is_absolute_path(path)) paste0(" in current working directory ('",
        getwd(), "')"),
      ".",
      call. = FALSE)
  }

  normalizePath(path, "/", mustWork = FALSE)
}


#' Create a source object.
#'
#' @param path Either a path to a file, or a connection. Reading directly
#'   from a file is most efficient.
#' @param text A character or raw vector. If a character vector, only the
#'   first element is used.
#' @param skip Number of lines to skip before reading data.
#' @keywords internal
new_source <- function(path, text, skip = 0) {
  if (!xor(missing(path), missing(text))) {
    stop("Specificy only one of path and text", call. = FALSE)
  }

  if (!missing(text)) {
    if (is.character(text)) {
      structure(list(text, skip = skip), class = "source_string")
    } else if (is.raw(text)) {
      structure(list(text, skip = skip), class = "source_raw")
    } else {
      stop("Text must be a character or raw vector", call. = FALSE)
    }
  } else {
    if (inherits(path, "connection")) {
      stop("Not supported")
      x <- readBin(path, n = 1e6)
      structure(list(x, skip = skip), class = "source_raw")
    } else if (is.character(path)) {
      path <- check_file(path)
      structure(list(path, skip = skip), class = "source_file")
    } else {
      stop("Path must be a character vector or connection", call. = FALSE)
    }
  }

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


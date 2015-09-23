#' Create a source object.
#'
#' @param file Either a path to a file, a connection, or literal data
#'    (either a single string or a raw vector).
#'
#'    Files ending in \code{.gz}, \code{.bz2}, \code{.xz}, or \code{.zip} will
#'    be automatically uncompressed. Files starting with \code{http://},
#'    \code{https://}, \code{ftp://}, or \code{ftps://} will be automatically
#'    downloaded. Remote gz files can also be automatically downloaded &
#'    decompressed.
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
#' # Strings
#' datasource(system.file("extdata/mtcars.csv", package = "readr"))
#' datasource(system.file("extdata/mtcars.csv.bz2", package = "readr"))
#' datasource(system.file("extdata/mtcars.csv.zip", package = "readr"))
#' datasource("https://github.com/hadley/readr/raw/master/inst/extdata/mtcars.csv")
#'
#' # Connection
#' datasource(rawConnection(charToRaw("abc\n123")))
datasource <- function(file, skip = 0) {
  if (inherits(file, "source")) {
    file
  } else if (is.connection(file)) {
    datasource_connection(file, skip)
  } else if (is.raw(file)) {
    datasource_raw(file, skip)
  } else if (is.character(file)) {
    if (grepl("\n", file)) {
      datasource_string(file, skip)
    } else {
      file <- standardise_path(file)
      if (is.connection(file)) {
        datasource_connection(file, skip)
      } else {
        datasource_file(file, skip)
      }
    }
  } else {
    stop("`file` must be a string, raw vector or a connection.", call. = FALSE)
  }
}

# Constructors -----------------------------------------------------------------

new_datasource <- function(type, x, skip, ...) {
  structure(list(x, skip = skip, ...),
    class = c(paste0("source_", type), "source"))
}

datasource_string <- function(text, skip) {
  new_datasource("string", text, skip = skip)
}

datasource_file <- function(path, skip) {
  path <- check_path(path)
  new_datasource("file", path, skip = skip)
}

datasource_connection <- function(path, skip) {
  datasource_raw(read_connection(path), skip)
}

datasource_raw <- function(text, skip) {
  new_datasource("raw", text, skip = skip)
}

# Helpers ----------------------------------------------------------------------

read_connection <- function(con) {
  stopifnot(is.connection(con))

  if (!isOpen(con)) {
    open(con, "rb")
    on.exit(close(con), add = TRUE)
  }

  read_connection_(con)
}

standardise_path <- function(path) {
  if (!is.character(path))
    return(path)

  if (grepl("\n", path))
    return(path)

  if (is_url(path)) {
    if (identical(tools::file_ext(path), "gz")) {
      return(gzcon(curl::curl(path)))
    } else {
      return(curl::curl(path))
    }
  }

  path <- check_path(path)
  switch(tools::file_ext(path),
    gz = gzfile(path, ""),
    bz2 = bzfile(path, ""),
    xz = xzfile(path, ""),
    zip = zipfile(path, ""),
    path
  )
}

source_name <- function(x) {
  if (is.connection(x)) {
    "<connection>"
  } else if (is.raw(x)) {
    "<raw vector>"
  } else if (is.character(x)) {
    if (grepl("\n", x)) {
      "literal data"
    } else {
      paste0("'", x, "'")
    }
  } else {
    "???"
  }
}

is_url <- function(path) {
  grepl("^(http|ftp)s?://", path)
}

check_path <- function(path) {
  if (file.exists(path))
    return(normalizePath(path, "/", mustWork = FALSE))

  stop("'", path, "' does not exist",
    if (!is_absolute_path(path))
      paste0(" in current working directory ('", getwd(), "')"),
    ".",
    call. = FALSE
  )
}

is_absolute_path <- function(path) {
  grepl("^(/|[A-Za-z]:|\\\\|~)", path)
}

zipfile <- function(path, open = "r") {
  files <- utils::unzip(path, list = TRUE)
  file <- files$Name[[1]]

  if (nrow(files) > 1) {
    message("Multiple files in zip: reading '", file, "'")
  }

  unz(path, file, open = open)
}

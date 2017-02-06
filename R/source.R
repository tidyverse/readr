#' Create a source object.
#'
#' @param file Either a path to a file, a connection, or literal data
#'    (either a single string or a raw vector).
#'
#'    Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will
#'    be automatically uncompressed. Files starting with `http://`,
#'    `https://`, `ftp://`, or `ftps://` will be automatically
#'    downloaded. Remote gz files can also be automatically downloaded and
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
#' datasource(readr_example("mtcars.csv"))
#' datasource(readr_example("mtcars.csv.bz2"))
#' datasource(readr_example("mtcars.csv.zip"))
#' \dontrun{
#' datasource("https://github.com/tidyverse/readr/raw/master/inst/extdata/mtcars.csv")
#' }
#'
#' # Connection
#' con <- rawConnection(charToRaw("abc\n123"))
#' datasource(con)
#' close(con)
datasource <- function(file, skip = 0, comment = "") {
  if (inherits(file, "source")) {
    if (!missing(skip)) { file$skip <- skip }
    if (!missing(comment)) { file$comment <- comment }
    file
  } else if (is.connection(file)) {
    datasource_connection(file, skip, comment)
  } else if (is.raw(file)) {
    datasource_raw(file, skip, comment)
  } else if (is.character(file)) {
    if (grepl("\n", file)) {
      datasource_string(file, skip, comment)
    } else {
      file <- standardise_path(file)
      if (is.connection(file)) {
        datasource_connection(file, skip, comment)
      } else {
        datasource_file(file, skip, comment)
      }
    }
  } else {
    stop("`file` must be a string, raw vector or a connection.", call. = FALSE)
  }
}

# Constructors -----------------------------------------------------------------

new_datasource <- function(type, x, skip, comment = "", ...) {
  structure(list(x, skip = skip, comment = comment, ...),
    class = c(paste0("source_", type), "source"))
}

datasource_string <- function(text, skip, comment = "") {
  new_datasource("string", text, skip = skip, comment = comment)
}

datasource_file <- function(path, skip, comment = "") {
  path <- check_path(path)
  new_datasource("file", path, skip = skip, comment = comment)
}

datasource_connection <- function(path, skip, comment = "") {
  datasource_raw(read_connection(path), skip, comment = comment)
}

datasource_raw <- function(text, skip, comment) {
  new_datasource("raw", text, skip = skip, comment = comment)
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

empty_file <- function(x) {
  is.character(x) && file.exists(x) && file.info(x, extra_cols = FALSE)$size == 0
}

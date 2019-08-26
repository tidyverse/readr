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
#'    least one new line to be recognised as data (instead of a path) or be a
#'    vector of greater than length 1.
#'
#'    Using a value of [clipboard()] will read from the system clipboard.
#'
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
datasource <- function(file, skip = 0, skip_empty_rows = FALSE, comment = "") {
  if (inherits(file, "source")) {

    # If `skip` and `comment` arguments are expliictly passed, we want to use
    # those even if `file` is already a source
    if (!missing(skip)) {
      file$skip <- skip
    }

    if (!missing(comment)) {
      file$comment <- comment
    }

    file
  } else if (is.connection(file)) {
    datasource_connection(file, skip, skip_empty_rows, comment)
  } else if (is.raw(file)) {
    datasource_raw(file, skip, skip_empty_rows, comment)
  } else if (is.character(file)) {
    if (length(file) > 1) {
      datasource_string(paste(file, collapse = "\n"), skip, skip_empty_rows, comment)
    } else if (grepl("\n", file)) {
      datasource_string(file, skip, skip_empty_rows, comment)
    } else {
      file <- standardise_path(file)
      if (is.connection(file)) {
        datasource_connection(file, skip, skip_empty_rows, comment)
      } else {
        datasource_file(file, skip, skip_empty_rows, comment)
      }
    }
  } else {
    stop("`file` must be a string, raw vector or a connection.", call. = FALSE)
  }
}

# Constructors -----------------------------------------------------------------

new_datasource <- function(type, x, skip, skip_empty_rows = TRUE, comment = "", ...) {
  structure(list(x, skip = skip, skip_empty_rows = skip_empty_rows, comment = comment, ...),
    class = c(paste0("source_", type), "source"))
}

datasource_string <- function(text, skip, skip_empty_rows = TRUE, comment = "") {
  new_datasource("string", text, skip = skip, skip_empty_rows = skip_empty_rows, comment = comment)
}

datasource_file <- function(path, skip, skip_empty_rows = TRUE, comment = "", ...) {
  path <- check_path(path)
  new_datasource("file", path, skip = skip, skip_empty_rows = skip_empty_rows, comment = comment, ...)
}

datasource_connection <- function(path, skip, skip_empty_rows = TRUE, comment = "") {
  # We read the connection to a temporary file, then register a finalizer to
  # cleanup the temp file after the datasource object is removed.

  file <- read_connection(path)
  env <- new.env(parent = emptyenv())
  reg.finalizer(env, function(env) unlink(file))
  datasource_file(file, skip, skip_empty_rows = skip_empty_rows, comment = comment, env = env)
}

datasource_raw <- function(text, skip, skip_empty_rows, comment) {
  new_datasource("raw", text, skip = skip, skip_empty_rows = skip_empty_rows, comment = comment)
}

# Helpers ----------------------------------------------------------------------

read_connection <- function(con) {
  stopifnot(is.connection(con))

  if (!isOpen(con)) {
    open(con, "rb")
    on.exit(close(con), add = TRUE)
  }

  read_connection_(con, tempfile())
}

standardise_path <- function(path, input = TRUE) {
  if (!is.character(path))
    return(path)

  if (length(path) > 1) {
    return(paste(path, collapse = "\n"))
  }

  if (grepl("\n", path))
    return(path)

  if (is_url(path)) {
    if (is_github_url(path)) {
      path <- convert_github_url(path)
    }

    if (requireNamespace("curl", quietly = TRUE)) {
      con <- curl::curl(path)
    } else {
      message("`curl` package not installed, falling back to using `url()`")
      con <- url(path)
    }
    ext <- tolower(tools::file_ext(path))
    return(
      switch(ext,
        bz2 = ,
        xz = {
          close(con)
          stop("Reading from remote `", ext, "` compressed files is not supported,\n",
            "  download the files locally first.", call. = FALSE)
        },
        gz = gzcon(con),
        con
      )
    )
  }

  if (isTRUE(input)) {
    path <- check_path(path)
  }
  switch(tolower(tools::file_ext(path)),
    gz = gzfile(path, ""),
    bz2 = bzfile(path, ""),
    xz = xzfile(path, ""),
    zip = zipfile(path, ""),

    # Use a file connection for output
    if (!isTRUE(input)) {
      file(path, "")
    } else {
      path
    })
}

source_name <- function(x) {
  if (is.connection(x)) {
    "<connection>"
  } else if (is.raw(x)) {
    "<raw vector>"
  } else if (is.character(x)) {
    if (length(x) > 1 || grepl("\n", x)) {
      "literal data"
    } else {
      paste0("'", x, "'")
    }
  } else {
    "???"
  }
}

is_url <- function(path) {
  grepl("^((http|ftp)s?|sftp)://", path)
}

is_github_url <- function(path) {
  grepl("^https?://(?:www[.])?github[.]com", path)
}

convert_github_url <- function(path) {
  sub("https://(?:www[.])?github.com/([^/]+)/([^/]+)/blob/([^/]+)/([^/]+)", "https://raw.githubusercontent.com/\\1/\\2/\\3/\\4", path)
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

#' Returns values from the clipboard
#'
#' This is useful in the [read_delim()] functions to read from the clipboard.
#' @seealso read_delim
#' @export
clipboard <- function() {
  clipr::read_clip()
}

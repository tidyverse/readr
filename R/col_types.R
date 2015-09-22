#' Create column specification
#'
#' @param ... Either column objects created by \code{col_*}, or their
#'   abbreviated character names. If you're only overriding a few columns,
#'   it's best to refer to columns by name. If not named, the column types
#'   must match the column names exactly.
#' @param .default Any named columns not explicitly overridden in \code{...}
#'   will be read with this column type.
#' @export
#' @examples
#' cols(a = col_integer())
#' cols_only(a = col_integer())
#'
#' # You can also use the standard abreviations
#' cols(a = "i")
#' cols(a = "i", b = "d", c = "_")
cols <- function(..., .default = col_guess()) {
  col_types <- list(...)
  is_character <- vapply(col_types, is.character, logical(1))
  col_types[is_character] <- lapply(col_types[is_character], col_concise)

  if (is.character(.default)) {
    .default <- col_concise(.default)
  }

  col_spec(col_types, .default)
}

#' @export
#' @rdname cols
cols_only <- function(...) {
  cols(..., .default = col_skip())
}


# col_spec ----------------------------------------------------------------

col_spec <- function(col_types, default = col_guess()) {
  stopifnot(is.list(col_types))
  stopifnot(is.collector(default))

  is_collector <- vapply(col_types, is.collector, logical(1))
  if (any(!is_collector)) {
    stop("Some `col_types` are not S3 collector objects: ",
      paste(which(!is_collector), collapse = ", "), call. = FALSE)
  }

  structure(
    list(
      cols = col_types,
      default = default
    ),
    class = "col_spec"
  )
}

is.col_spec <- function(x) inherits(x, "col_spec")

#' @export
print.col_spec <- function(x, ...) {
  cat("<col_spec>\n")

  col_class <- function(x) gsub("collector_", "", class(x)[[1]])

  cols <- x$cols
  class <- vapply(cols, col_class, character(1))
  if (length(cols) > 0) {
    if (is.null(names(cols))) {
      cat(paste0("* ", class, collapse = "\n"), "\n", sep = "")
    } else {
      cat(paste0("* ", names(cols), ": ", class, collapse = "\n"), "\n", sep = "")
    }
  }
  cat("* default: ", col_class(x$default), "\n", sep = "")
}

as.col_spec <- function(x) UseMethod("as.col_spec")
#' @export
as.col_spec.character <- function(x) {
  letters <- strsplit(x, "")[[1]]
  col_spec(lapply(letters, col_concise), col_guess())
}
#' @export
as.col_spec.list <- function(x) {
  col_spec(x)
}
#' @export
as.col_spec.col_spec <- function(x) x
#' @export
as.col_spec.default <- function(x) {
  stop("`col_types` must be NULL, a list or a string", call. = FALSE)
}

col_guess <- function() {
  collector("guess")
}

col_concise <- function(x) {
  switch(x,
    c = col_character(),
    d = col_double(),
    e = col_euro_double(),
    D = col_date(),
    T = col_datetime(),
    t = col_time(),
    i = col_integer(),
    l = col_logical(),
    "_" = ,
    "-" = col_skip(),
    n = col_number(),
    "?" = col_guess(),
    stop("Unknown shortcut: ", x, call. = FALSE)
  )
}

#' Standardise column types.
#'
#' @param col_types One of \code{NULL}, a \code{\link{cols}}, specification of
#'   a string. See \code{vignette("column-types")} for more details.
#'
#'   If \code{NULL}, all column types will be imputed from the first 1000 rows
#'   on the input. This is convenient (and fast), but not robust. If the
#'   imputation fails, you'll need to supply the correct types yourself.
#'
#'   If a column specification created by \code{\link{cols}}, it must contain
#'   one "\code{\link{collector}}" for each column. If you only want to read a
#'   subset of the columns, use \code{\link{cols_only}}.
#'
#'   Alternatively, you can use a compact string representation where each
#'   character represents one column: c = character, d = double, i = integer,
#'   l = logical, ? = guess, or \code{_}/\code{-} to skip the column.
#' @param col_names A character vector naming the columns.
#' @param rows A data frame containing the first few rows, parsed as
#'   character vectors.
#' @export
#' @keywords internal
#' @examples
#' col_spec_standardise("ii", c("a", "b"))
col_spec_standardise <- function(col_types, col_names, guessed_types) {
  if (is.null(col_types)) {
    col_types <- rep(list(col_guess()), length(col_names))
  }

  spec <- as.col_spec(col_types)
  type_names <- names(spec$cols)

  if (is.null(type_names)) {
    if (length(spec$cols) != length(col_names)) {
      stop("Unnamed `col_types` must have the same length as `col_names`.",
        call. = FALSE)
    }
    names(spec$cols) <- col_names
  } else {
    bad_types <- !(type_names %in% col_names)
    if (any(bad_types)) {
      warning("The following named parsers don't match the column names: ",
        paste0(type_names[bad_types], collapse = ", "), call. = FALSE)
      spec$cols <- spec$cols[!bad_types]
      type_names <- type_names[!bad_types]
    }

    default_types <- !(col_names %in% type_names)
    if (any(default_types)) {
      defaults <- rep(list(spec$default), sum(default_types))
      names(defaults) <- col_names[default_types]
      spec$cols[names(defaults)] <- defaults
    }

    spec$cols <- spec$cols[col_names]
  }

  is_guess <- vapply(spec$cols, function(x) inherits(x, "collector_guess"), logical(1))
  if (any(is_guess)) {
    spec$cols[is_guess] <- lapply(guessed_types[is_guess], collector_find)
  }

  spec$cols
}

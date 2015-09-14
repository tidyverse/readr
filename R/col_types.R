#' Standardise column types.
#'
#' @param col_types One of \code{NULL}, a list, a named list or a string.
#'   See \code{vignette("column-types")} for more details.
#'
#'   If \code{NULL}, the column type will be imputed from the first 1000 rows
#'   on the input. This is convenient (and fast), but not robust. If the
#'   imputation fails, you'll need to supply the correct types yourself.
#'
#'   If a list, it must contain one "\code{\link{collector}}" for each column.
#'   If you only want to read a subset of the columns, you can use a named list
#'   (where the names give the column names). If a column is not mentioned by
#'   name, it will be parsed with the default collector (as determined by
#'   reading the first 1000 rows).
#'
#'   Alternatively, you can use a compact string representation where each
#'   character represents one column: c = character, d = double, i = integer,
#'   l = logical, ? = guess, or \code{_}/\code{-} to skip the column.
#' @param col_names A character vector naming the columns.
#' @param rows A data frame containing the first few rows, parsed as
#'   character vectors.
#' @export
#' @keywords internal
col_types_standardise <- function(col_types, col_names, guessed_types) {
  if (is.null(col_types)) {
    lapply(guessed_types, collector_find)
  } else if (is.character(col_types) && length(col_types) == 1) {
    col_types_concise(col_types, guessed_types)
  } else if (is.list(col_types)) {
    col_types_full(col_types, col_names, guessed_types)
  } else {
    stop("`col_types` must be NULL, a list or a string", call. = FALSE)
  }
}


col_types_concise <- function(x, guessed_types) { 
  letters <- strsplit(x, "")[[1]]

  # after col_euro_double is removed from the package so can the following check
  # for `e` in the concise string.
  euros <- grep("e", letters)
  if (length(euros) > 0) { 
    warning("col_euro_double() has been deprecated.  Please set locale.  Substituting `d` for `e`.")
    letters[euros] <- "d"
  }

  lookup <- list(
    c = col_character(),
    d = col_double(),
    D = col_date(),
    T = col_datetime(),
    i = col_integer(),
    l = col_logical(),
    "_" = col_skip(),
    "-" = col_skip(),
    n = col_number(),
    "?" = NULL
  )

  bad <- setdiff(letters, names(lookup))
  if (length(bad) > 0) {
    stop("Unknown shortcuts: ", paste(unique(bad), collapse = ", "))
  }

  collectors <- unname(lookup[letters])

  is_guess <- vapply(collectors, is.null, logical(1))
  collectors[is_guess] <- lapply(guessed_types[is_guess], collector_find)

  collectors
}

col_types_full <- function(col_types, col_names, guessed_types) {
  is_collector <- vapply(col_types, inherits, "collector", FUN.VALUE = logical(1))
  if (any(!is_collector)) {
    stop("Some col_types are not S3 collector objects: ",
      paste(which(!is_collector), collapse = ", "), call. = FALSE)
  }


  if (is.null(names(col_types))) {
    if (length(col_types) != length(col_names)) {
      stop("Unnamed columns must have the same length as col_names",
        call. = FALSE)
    }

    col_types
  } else {
    unmatched_names <- setdiff(names(col_types), col_names)
    if (length(unmatched_names) > 0) {
      warning("The following named parsers don't match the column names: ",
        paste0(unmatched_names, collapse = ", "), call. = FALSE)
    }

    skip <- setdiff(col_names, names(col_types))
    if (length(skip) > 0) {
      names(guessed_types) <- col_names
      col_types[skip] <- lapply(guessed_types[skip], collector_find)
    }

    col_types[match(col_names, names(col_types))]
  }
}

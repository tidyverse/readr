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
as.col_spec.NULL <- function(x) {
  col_spec(list())
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

col_concise <- function(x) {
  switch(x,
    "_" = ,
    "-" = col_skip(),
    "?" = col_guess(),
    c = col_character(),
    D = col_date(),
    d = col_double(),
    e = col_euro_double(),
    i = col_integer(),
    l = col_logical(),
    n = col_number(),
    T = col_datetime(),
    t = col_time(),
    stop("Unknown shortcut: ", x, call. = FALSE)
  )
}

col_spec_standardise <- function(file, col_names = TRUE, col_types = NULL,
                                 guessed_types = NULL,
                                 comment = "", skip = 0, n_max = -1,
                                 tokenizer = tokenizer_csv(),
                                 locale = default_locale()) {

  # Figure out the column names -----------------------------------------------
  if (is.logical(col_names) && length(col_names) == 1) {
    ds_header <- datasource(file, skip = skip, comment = comment)
    if (col_names) {
      col_names <- guess_header(ds_header, tokenizer, locale)
    } else {
      n <- length(guess_header(ds_header, tokenizer, locale))
      col_names <- paste0("X", seq_len(n))
    }
    guessed_names <- TRUE
    skip <- skip + 1
  } else if (is.character(col_names)) {
    guessed_names <- FALSE
  } else {
    stop("`col_names` must be TRUE, FALSE or a character vector", call. = FALSE)
  }

  # Figure out column types ----------------------------------------------------

  spec <- as.col_spec(col_types)
  type_names <- names(spec$cols)

  if (length(spec$cols) == 0) {
    # no types specified so use defaults

    spec$cols <- rep(list(spec$default), length(col_names))
    names(spec$cols) <- col_names
  } else if (is.null(type_names) && guessed_names) {
    # unnamed types & names guessed from header: match exactly

    if (length(spec$cols) != length(col_names)) {
      warning("Unnamed `col_types` should have the same length as `col_names`. ",
        "Using smaller of the two.", call. = FALSE)
      n <- min(length(col_names), length(col_types))
      spec$cols <- spec$cols[seq_len(n)]
      col_names <- col_names[seq_len(n)]
    }

    names(spec$cols) <- col_names
  } else if (is.null(type_names) && !guessed_names) {
    # unnamed types & names supplied: match non-skipped columns
    skipped <- vapply(spec$cols, inherits, "collector_skip",
      FUN.VALUE = logical(1))
    n_read <- sum(!skipped)
    n_names <- length(col_names)

    n_new <- abs(n_names - n_read)
    if (n_read < n_names) {
      warning("Insufficient `col_types`. Guessing ", n_new, " columns.",
        call. = FALSE)
      spec$cols <- c(spec$cols, list(rep(col_guess(), n_new)))
    } else if (n_read > n_names) {
      warning("Insufficient `col_names`. Adding ", n_new, " names.",
        call. = FALSE)
      col_names <- c(col_names, paste0("X", seq_len(n_new) + n_read - 1))
    } else {
      col_names2 <- rep("", length(spec$cols))
      col_names2[!skipped] <- col_names
      col_names <- col_names2
    }
    names(spec$cols) <- col_names
  } else {
    # names types

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

  # Guess any types that need to be guessed ------------------------------------

  is_guess <- vapply(spec$cols, function(x) inherits(x, "collector_guess"), logical(1))
  if (any(is_guess)) {
    if (is.null(guessed_types)) {
      ds <- datasource(file, skip = skip, comment = comment)
      guessed_types <- guess_types(ds, tokenizer, locale, n_max = n_max)
    }

    # Need to be careful here: there might be more guesses than types/names
    guesses <- guessed_types[seq_along(spec$cols)][is_guess]
    spec$cols[is_guess] <- lapply(guesses, collector_find)
  }

  spec$cols
}

guess_types <- function(datasource, tokenizer, locale, n = 1000, n_max = -1) {
  if (n_max > 0) {
    n <- min(n, n_max)
  }
  guess_types_(datasource, tokenizer, locale, n = n)
}

guess_header <- function(datasource, tokenizer, locale = default_locale()) {
  guess_header_(datasource, tokenizer, locale)
}

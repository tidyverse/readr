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

#' @export
print.col_spec <- function(x, n = Inf, ...) {
  if (inherits(x$default, "collector_guess")) {
    fun_type <- "cols(\n  "
  } else if (inherits(x$default, "collector_skip")) {
    fun_type <- "cols_only(\n  "
  } else {
    type <- sub("^collector_", "", class(x$default)[[1]])
    fun_type <- paste0("cols(.default = col_", type, "(),\n  ")
  }

  cols <- x$cols[seq_len(min(length(x$cols), n))]
  cat(fun_type,
    paste(collapse = ",\n  ",
    vapply(seq_along(cols),
      function(i) {
        col_names <- names(cols)[[i]]
        col_funs <- sub("^collector_", "col_", class(cols[[i]])[[1]])
        args <- vapply(cols[[i]], deparse, character(1))
        args <- paste(names(args), args, sep = " = ", collapse = ", ")

        # Need to special case skipped columns without names
        named <- col_names != ""
        out <- paste0(col_names, " = ", col_funs, "(", args, ")")
        out[!named] <- paste0(col_funs, "(", args, ")")
        out
      },
      character(1)
    )), sep = "")

  if (length(x$cols) >= n) {
    cat("\n  # ... with", length(x$cols) - n, "more columns\n")
  }
  cat(")\n")

  invisible(x)
}

#' Extract the column specification from an data frame
#'
#' @param x The data frame object to extract from
#' @return The col_spec object used for that data frame.
#' @export
spec <- function(x) {
  stopifnot(inherits(x, "tbl_df"))
  attr(x, "spec")
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
                                 comment = "", skip = 0, n = 1000,
                                 tokenizer = tokenizer_csv(),
                                 locale = default_locale()) {

  # Figure out the column names -----------------------------------------------
  if (is.logical(col_names) && length(col_names) == 1) {
    ds_header <- datasource(file, skip = skip, comment = comment)
    if (col_names) {
      col_names <- guess_header(ds_header, tokenizer, locale)
      skip <- skip + 1
    } else {
      n <- length(guess_header(ds_header, tokenizer, locale))
      col_names <- paste0("X", seq_len(n))
    }
    guessed_names <- TRUE
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
      n <- min(length(col_names), length(spec$cols))
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

      col_names2 <- rep("", length(spec$cols))
      col_names2[!skipped] <- c(col_names, paste0("X", seq_len(n_new) + n_names))
      col_names <- col_names2
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
      guessed_types <- guess_types(ds, tokenizer, locale, n = n)
    }

    # Need to be careful here: there might be more guesses than types/names
    guesses <- guessed_types[seq_along(spec$cols)][is_guess]
    spec$cols[is_guess] <- lapply(guesses, collector_find)
  }

  spec
}

guess_types <- function(datasource, tokenizer, locale, n = 1000) {
  guess_types_(datasource, tokenizer, locale, n = n)
}

guess_header <- function(datasource, tokenizer, locale = default_locale()) {
  guess_header_(datasource, tokenizer, locale)
}

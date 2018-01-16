#' Create column specification
#'
#' @param ... Either column objects created by `col_*()`, or their
#'   abbreviated character names. If you're only overriding a few columns,
#'   it's best to refer to columns by name. If not named, the column types
#'   must match the column names exactly.
#' @param .default Any named columns not explicitly overridden in `...`
#'   will be read with this column type.
#' @export
#' @examples
#' cols(a = col_integer())
#' cols_only(a = col_integer())
#'
#' # You can also use the standard abreviations
#' cols(a = "i")
#' cols(a = "i", b = "d", c = "_")
#'
#' # You can also use multiple sets of column definitions by combining
#' # them like so:
#'
#' t1 <- cols(
#'   column_one = col_integer(),
#'   column_two = col_number())
#'
#' t2 <- cols(
#'  column_three = col_character())
#'
#' t3 <- t1
#' t3$cols <- c(t1$cols, t2$cols)
#' t3

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
  do.call(cols, x)
}
#' @export
as.col_spec.col_spec <- function(x) x

#' @export
as.col_spec.default <- function(x) {
  stop("`col_types` must be NULL, a list or a string", call. = FALSE)
}

#' @export
print.col_spec <- function(x, n = Inf, condense = NULL, ...) {
  cat(format.col_spec(x, n = n, condense = condense, ...))

  invisible(x)
}

#' @description
#' `cols_condense()` takes a spec object and condenses its definition by setting
#' the default column type to the most frequent type and only listing columns
#' with a different type.
#' @rdname spec
#' @export
cols_condense <- function(x) {
  types <- vapply(x$cols, function(xx) class(xx)[[1]], character(1))
  counts <- table(types)
  most_common <- names(counts)[counts == max(counts)][[1]]

  x$default <- x$cols[types == most_common][[1]]
  x$cols <- x$cols[types != most_common]
  x
}

#' @export
format.col_spec <- function(x, n = Inf, condense = NULL, ...) {

  if (n == 0) {
    return("")
  }

  # condense if cols >= n
  condense <- condense %||% (length(x$cols) >= n)
  if (isTRUE(condense)) {
    x <- cols_condense(x)
  }

  # truncate to minumum of n or length
  cols <- x$cols[seq_len(min(length(x$cols), n))]

  default <- NULL
  if (inherits(x$default, "collector_guess")) {
    fun_type <- "cols"
  } else if (inherits(x$default, "collector_skip")) {
    fun_type <- "cols_only"
  } else {
    fun_type <- "cols"
    type <- sub("^collector_", "", class(x$default)[[1]])
    default <- paste0(".default = col_", type, "()")
  }

  cols_args <- c(default,
    vapply(seq_along(cols),
      function(i) {
        col_funs <- sub("^collector_", "col_", class(cols[[i]])[[1]])
        args <- vapply(cols[[i]], deparse2, character(1), sep = "\n    ")
        args <- paste(names(args), args, sep = " = ", collapse = ", ")

        col_names <- names(cols)[[i]]

        # Need to handle unnamed columns and columns with non-syntactic names
        named <- col_names != ""

        non_syntactic <- !is_syntactic(col_names) & named
        col_names[non_syntactic] <- paste0("`", gsub("`", "\\\\`", col_names[non_syntactic]), "`")

        out <- paste0(col_names, " = ", col_funs, "(", args, ")")
        out[!named] <- paste0(col_funs, "(", args, ")")
        out
      },
      character(1)
    )
  )
  if (length(x$cols) == 0 && length(cols_args) == 0) {
    return(paste0(fun_type, "()\n"))
  }


  out <- paste0(fun_type, "(\n  ", paste(collapse = ",\n  ", cols_args))

  if (length(x$cols) > n) {
    out <- paste0(out, "\n  # ... with ", length(x$cols) - n, " more columns")
  }
  out <- paste0(out, "\n)\n")

  out
}

# Used in read_delim(), read_fwf() and type_convert()
show_cols_spec <- function(spec, n = getOption("readr.num_columns", 20)) {
  if (n > 0) {
    message("Parsed with column specification:\n",
      format(spec, n = n, condense = NULL), appendLF = FALSE)
    if (length(spec$cols) >= n) {
      message("See spec(...) for full column specifications.")
    }
  }
}

# This allows str() on a tibble object to print a little nicer.
#' @export
str.col_spec <- function(object, ..., indent.str = "") {

  # Split the formatted column spec into strings
  specs <- strsplit(format(object), "\n")[[1]]
  cat(sep = "",
    "\n",

    # Append the current indentation string to the specs
    paste(indent.str, specs, collapse = "\n"),

    "\n")
}


#' Examine the column specifications for a data frame
#'
#' `spec()` extracts the full column specification from a tibble
#' created by readr.
#'
#' @param x The data frame object to extract from
#' @return A col_spec object.
#' @export
#' @examples
#' df <- read_csv(readr_example("mtcars.csv"))
#' s <- spec(df)
#' s
#'
#' cols_condense(s)
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
                                 comment = "", skip = 0, guess_max = 1000,
                                 tokenizer = tokenizer_csv(),
                                 locale = default_locale(),
                                 drop_skipped_names = FALSE) {

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

  missing_names <- is.na(col_names)
  if (any(missing_names)) {
    new_names <- paste0("X", seq_along(col_names)[missing_names])
    col_names[missing_names] <- new_names
    warning(
      "Missing column names filled in: ",
      paste0(
        encodeString(new_names, quote = "'"),
        " [", which(missing_names), "]",
        collapse = ", "
      ), call. = FALSE
    )
  }

  if (anyDuplicated(col_names)) {
    dups <- duplicated(col_names)

    old_names <- col_names
    col_names <- make.unique(col_names, sep = "_")

    warning(
      "Duplicated column names deduplicated: ",
      paste0(
        encodeString(old_names[dups], quote = "'"),
        " => ",
        encodeString(col_names[dups], quote = "'"),
        " [", which(dups), "]",
        collapse = ", "
      ), call. = FALSE
    )
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

    # Needed for read_fwf() because width generator functions have name for
    # every column, even those that are skipped. Not need for read_delim()
    if (drop_skipped_names) {
      col_names <- col_names[!skipped]
    }

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
      guessed_types <- guess_types(ds, tokenizer, locale, guess_max = guess_max)
    }

    # Need to be careful here: there might be more guesses than types/names
    guesses <- guessed_types[seq_along(spec$cols)][is_guess]
    spec$cols[is_guess] <- lapply(guesses, collector_find)
  }

  spec
}


check_guess_max <- function(guess_max, max_limit = .Machine$integer.max %/% 100) {

  if (length(guess_max) != 1 || !is.numeric(guess_max) || !is_integerish(guess_max) ||
      is.na(guess_max) || guess_max < 0) {
    stop("`guess_max` must be a positive integer", call. = FALSE)
  }

  if (guess_max > max_limit) {
    warning("`guess_max` is a very large value, setting to `", max_limit,
      "` to avoid exhausting memory", call. = FALSE)
    guess_max <- max_limit
  }
  guess_max
}

guess_types <- function(datasource, tokenizer, locale, guess_max = 1000,
  max_limit = .Machine$integer.max %/% 100) {

  guess_max <- check_guess_max(guess_max, max_limit)

  guess_types_(datasource, tokenizer, locale, n = guess_max)
}

guess_header <- function(datasource, tokenizer, locale = default_locale()) {
  guess_header_(datasource, tokenizer, locale)
}

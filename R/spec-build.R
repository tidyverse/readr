#' Build a spec from a csv file.
#'
#' Builds a complete specification to parse a csv file, including guessing
#' the column parsers if they're not suppled.
#'
#' @keywords internal
#' @export
#' @inheritParams line_spec
#' @inheritParams field_spec
#' @inheritParams column_spec
build_delim_spec <- function(file, delim = NULL, parsers = NULL,
                             col_names = TRUE, quote = '"', na_strings = "NA",
                             n = 0, skip = 0, comment_char = "",
                             double_escape = FALSE, backslash_escape = FALSE) {

  if (is.null(delim)) {
    delim <- guess_delim(file, skip = skip,
      quote = quote, backslash_escape = backslash_escape,
      double_escape = double_escape, comment_char = comment_char)
  }

  if (is.null(parsers) || isTRUE(col_names) || isFALSE(col_names)) {
    path <- normalizePath(file)
    lines <- parse_lines_from_file(path, skip = skip, n = 30)
    if (length(lines) == 0) stop("No lines found in ", file, call. = FALSE)
    fields <- lapply(lines, parse_delimited_fields, delim = delim)
    col_spec <- guess_column_spec(fields, parsers = parsers,
      col_names = col_names, na_strings = na_strings)
  } else {
    col_spec <- column_spec(parsers, col_names = col_names,
      na_strings = na_strings)
  }

  delim_spec(
    line_spec(skip = skip + isTRUE(col_names), n = n, comment = comment_char),
    field_spec(delim = ",", quote = quote, double_escape = double_escape,
      backslash_escape = backslash_escape),
    col_spec
  )
}

#' Guess which parsers are needed.
#'
#' This operation is relatively expensive, so it's only done on a small
#' sample of the total data frame. This makes it prone to error if your
#' data formats vary, but since the individual parsers are strict (once
#' identified) you'll quickly find out about it, and you can specify the
#' parsers exactly yourself.
#'
#' @param fields List of character vectors: each vector represents one
#'   lines worth of fields.
#' @export
#' @keywords internal
guess_column_spec <- function(fields, parsers = NULL, col_names = TRUE,
                              na_strings = "NA", ignore_whitespace = TRUE) {

  message("Guessing column specification from first ", length(fields),
    " lines of data")

  nfields <- unique(vapply(fields, length, integer(1)))
  if (length(nfields) != 1) {
    stop("Lines do not have the same number of fields: ",
      paste(nfields, collapse = ", "), collapse = ",")
  }

  cols <- flip(fields)
  if (isTRUE(col_names)) {
    col_names <- str_trim(vpluck(cols, 1))
    cols <- lapply(cols, "[", -1)
    message("Reading column names from file: ",
      paste0(col_names, collapse = ", "))
  } else if (isFALSE(col_names)) {
    col_names <- paste0("X", seq_along(cols))
    message("No column names in file, using X1-X", length(cols))
  } else {
    if (!is.character(col_names))
      stop("col_names must be a character vector", call. = FALSE)
    if (length(col_names) != length(cols))
      stop("col_names must be same length as columns (", length(cols), ")",
        call. = FALSE)
  }
  names(cols) <- col_names

  if (is.null(parsers)) {
    message("Guessing how to parse each column")
    candidates <- lapply(cols, guess_parser, na_strings = na_strings,
      ignore_whitespace = ignore_whitespace)

    pick <- function(var, parsers) {
      selected <- parsers[1]
      others <- if (length(parsers) > 1)
        paste0(" # or ", paste0(parsers[-1], collapse = ", "))

      message(var, " = ", selected, "_parser()", others)
      selected
    }

    names <- Map(pick, names(candidates), candidates)
    parsers <- lapply(names, find_parser)
  }

  column_spec(parsers, col_names, na_strings = na_strings)
}

guess_parser <- function(x, na_strings = "NA", ignore_whitespace = TRUE) {
  if (ignore_whitespace) {
    x <- str_trim(x)
  }
  x <- setdiff(x, c(na_strings, ""))

  coercible <- c(
    skip    = length(x) == 0,
    logical = all(x %in% c("TRUE", "FALSE", "T", "F")),
    integer = is_int(x),
    double  = is_double(x),
    date    = all(grepl("^[0-9]{4}-[0-9]{2}-[0-9]{2}$", x))
  )

  if (!any(coercible)) {
    return("character")
  }

  names(coercible)[coercible]
}

guess_delim <- function(file, n = 30, skip = 0, comment_char = "", quote = "\"",
                        backslash_escape = FALSE,
                        double_escape = FALSE) {

  path <- normalizePath(file)
  x <- count_char_from_file(path, n = n, skip = skip, quote_ = quote,
    comment = comment_char, backslash_escape = backslash_escape,
    double_escape = double_escape)

  names(x) <- rawToChar(as.raw(names(x)), multiple = TRUE)
  counts <- sort(x, decreasing = TRUE)

  lines <- counts[["\n"]]
  candidates <- counts[setdiff(names(counts), "\n")]

  per_line <- candidates / lines
  # Must be at least one delimiter per line
  per_line <- per_line[per_line > 1]
  # Integer number of delimiters per line is best
  is_int <- round(per_line) == per_line
  if (sum(is_int) == 0) {
    stop("Could not guess delimter")
  } else if (sum(is_int) == 1) {
    # Only one delim is used on every line
    delim <- names(per_line)[is_int]
    message("Guessing delimiter is ", delim, " (used ", per_line[is_int],
      " times per line).")
  } else {
    # Use candidate with highest frequency
    ok <- per_line[is_int]
    delim <- names(per_line)[which.max(ok)][1]
    message("Guessing delimiter is ", delim,
      " (", paste0(names(ok), " used ", ok, collapse = ","), ")")
  }

  delim
}

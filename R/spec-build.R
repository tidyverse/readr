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
build_csv_spec <- function(file, parsers = NULL, header = TRUE, quote = '"',
                           na_strings = "NA", n = 0, skip = 0,
                           comment_char = "", double_escape = FALSE,
                           backslash_escape = FALSE) {

  if (is.null(parsers)) {
    path <- normalizePath(file)
    lines <- parse_lines_from_file(path, skip = skip + header, n = 20)
    if (length(lines) == 0) stop("No lines found in ", file, call. = FALSE)
    fields <- lapply(lines, parse_delimited_fields, delim = ",")
    parsers <- guess_parsers(fields)
  }

  delim_spec(
    line_spec(skip = skip, n = n, comment = comment_char),
    field_spec(delim = ",", quote = quote, double_escape = double_escape,
      backslash_escape = backslash_escape),
    column_spec(parsers, header = header, na_strings = na_strings)
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
guess_parsers <- function(fields, na_strings = "NA", ignore_whitespace = TRUE) {
  nfields <- unique(vapply(fields, length, integer(1)))

  if (length(nfields) != 1) {
    stop("Lines do not have the same number of fields: ",
      paste(nfields, collapse = ", "), collapse = ",")
  }

  candidates <- lapply(flip(fields), guess_parser, na_strings = na_strings,
    ignore_whitespace = ignore_whitespace)

  pick <- function(var, parsers) {
    selected <- parsers[1]
    others <- if (length(parsers) > 1)
      paste0(" (also valid: ", paste0(parsers[-1], collapse = ", "), ")")

    message(var, ": ", selected, others)
    selected
  }
  names(candidates) <- paste0("X", seq_along(candidates))

  Map(pick, names(candidates), candidates)
}

guess_parser <- function(x, na_strings = "NA", ignore_whitespace = FALSE) {
  if (ignore_whitespace) {
    x <- gsub("^\\s+|\\s+$", "", x)
  }
  x <- setdiff(x, na_strings)

  coercible <- list(
    logical = function(x) all(x %in% c("TRUE", "FALSE", "T", "F")),
    integer = function(x) all(grepl("^[0-9]+$", x)),
    double  = function(x) is_double(x),
    date    = function(x) all(grepl("^[0-9]{4}-[0-9]{2}-[0-9]{2}$", x))
  )
  ok <- vapply(coercible, function(f) f(x), logical(1))
  if (!any(ok)) {
    return("character")
  }

  names(coercible)[ok]
}


top_delim <- function(file, n = 20, quote = "\"",
                        backslash_escape = FALSE,
                        double_escape = FALSE) {

  x <- count_char_from_file(file, quote = quote,
    backslash_escape = backslash_escape, double_escape = double_escape)

  names(x) <- rawToChar(as.raw(names(x)), multiple = TRUE)
  sort(x, decreasing = TRUE)

  # Look for largest that's multiple of lines
  # Prefer , over . (unless Europe = TRUE?)
}

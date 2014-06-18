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
    lines <- parse_lines(file, skip = skip)
    fields <- lapply(lines, parse_fields, delim = ",", n = 20)
    parsers <- guess_parsers(fields)
  }

  delim_spec(
    line_spec(skip = skip, n = n, comment = comment_char),
    field_spec(delim = ",", quote = quote, double_escape = double_escape,
      backslash_escape = backslash_escape),
    column_spec(parsers, header = header, na_strings = na_strings)
  )
}

#' @param fields List of character vectors as returned by
#'   \code{\link{parse_fields}}
guess_parsers <- function(fields) {
  nfields <- unique(vapply(fields, length, integer(1)))

  if (length(nfields) != 1) {
    stop("Lines do not have the same number of fields: ",
      paste(nfields, collapse = ", "), collapse = ",")
  }

  lapply(flip(fields), guess_parser)
}

guess_parser <- function(x) {
  # Probably needs to be a C++ function:
  # std::string guessParser(CharacterVector x)
  #
  # Fallback approach
  #
  # integer -> double -> character
  # integer -> date time -> date -> character
  #
  # Other approach is to work from most general to most specific

  # [1-9][0-9]+ -> integer
  # [+-]?(?=\d*[.eE])(?=\.?\d)\d*\.?\d*(?:[eE][+-]?\d+)? -> floating point
  # T|F|TRUE|FALSE -> logical
  # [0-9]{4}-[0-9]{2}-[0-9]{2} -> iso8601 date
  # [0-9]{4}-[0-9]{2}-[0-9]{2}T... -> iso8601 date time
  # -> character
  "character"
}

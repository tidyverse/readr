# Only need to guess elements that aren't already present.
# Order matters: need to know line_delim, then field_delim, then
# parsers

read_csv <- function(file, parsers = NULL, header = TRUE, comment_char = "#",
                     na_strings = "NA", skip = 0) {
  if (is.null(parsers)) {
    fields <- parse_fields(file, field_delim = ",", header = header,
      comment_char = comment_char, na_strings = na_strings, skip = skip)
    parsers <- guess_parsers(fields)
  }
  spec <- spec(parsers, header = header, comment_char = comment_char,
    na_strings = na_strings, skip = skip)

  read_with_spec(file, spec)
}

# This can be relatively slow because we're only processing ~20 rows.
parse_fields <- function(file, n = 20, field_delim = ",", header = TRUE,
                         comment_char = "#", na_strings = "NA", skip = 0) {
  stopifnot(file.exists(file))
  skip <- skip + header

  parseFields(field, n, fieldDelim = ",", skipLines = skip,
    commentChar = comment_char, naStrings = na_strings)
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

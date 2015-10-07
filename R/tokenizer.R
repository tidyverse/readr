#' Tokenize a file/string.
#'
#' Turns input into a character vector. Usually the tokenization is done purely
#' in C++, and never exposed to R (because that requires a copy). This function
#' is useful for testing, or when a file doesn't parse correctly and you want
#' to see the underlying tokens.
#'
#' @inheritParams datasource
#' @param tokenizer A tokenizer specification.
#' @param skip Number of lines to skip before reading data.
#' @param n_max Optionally, maximum number of rows to tokenize.
#' @keywords internal
#' @export
#' @examples
#' tokenize("1,2\n3,4,5\n\n6")
#'
#' # Only tokenize first two lines
#' tokenize("1,2\n3,4,5\n\n6", n = 2)
tokenize <- function(file, tokenizer = tokenizer_csv(), skip = 0, n_max = -1L) {
  ds <- datasource(file, skip = skip)
  tokenize_(ds, tokenizer, n_max)
}

#' Tokenizers.
#'
#' Explicitly create tokenizer objects. Usually you will not call these
#' function, but will instead use one of the use friendly wrappers like
#' \code{read_csv}.
#'
#' @keywords internal
#' @name Tokenizers
#' @examples
#' tokenizer_csv()
NULL

#' @export
#' @rdname Tokenizers
#' @param comment A string used to identify comments. Any text after the
#'   comment characters will be silently ignored.
#' @param na Character vector of strings to use for missing values. Set this
#'   option to \code{character()} to indicate no missing values.
#' @param delim Single character used to separate fields within a record.
#' @param quote Single character used to quote strings.
#' @param trim_ws Should leading and trailing whitespace be trimmed from
#'   each field before parsing it?
#' @param escape_double Does the file escape quotes by doubling them?
#'   i.e. If this option is \code{TRUE}, the value \code{""""} represents
#'   a single quote, \code{\"}.
#' @param escape_backslash Does the file use backslashes to escape special
#'   characters? This is more general than \code{escape_double} as backslashes
#'   can be used to escape the delimeter character, the quote characer, or
#'   to add special characters like \code{\\n}.
tokenizer_delim <- function(delim, quote = '"', na = "NA", comment = "",
                            trim_ws = TRUE,
                            escape_double = TRUE,
                            escape_backslash = FALSE) {
  structure(
    list(
      delim = delim,
      quote = quote,
      na = na,
      comment = comment,
      trim_ws = trim_ws,
      escape_double = escape_double,
      escape_backslash = escape_backslash
    ),
    class = "tokenizer_delim"
  )
}

#' @export
#' @rdname Tokenizers
tokenizer_csv <- function(na = "NA", comment = "", trim_ws = TRUE) {
  tokenizer_delim(
    delim = ",",
    quote = '"',
    na = na,
    comment = comment,
    trim_ws = trim_ws,
    escape_double = TRUE,
    escape_backslash = FALSE
  )
}

#' @export
#' @rdname Tokenizers
tokenizer_tsv <- function(na = "NA", comment = "", trim_ws = TRUE) {
  tokenizer_delim(
    delim = "\t",
    quote = '"',
    na = na,
    comment = comment,
    trim_ws = trim_ws,
    escape_double = TRUE,
    escape_backslash = FALSE
  )
}

#' @export
#' @rdname Tokenizers
tokenizer_line <- function() {
  structure(list(), class = "tokenizer_line")
}

#' @export
#' @rdname Tokenizers
tokenizer_log <- function() {
  structure(list(), class = "tokenizer_log")
}


#' @export
#' @rdname Tokenizers
#' @param begin,end Begin and end offsets for each file. These are C++
#'   offsets so the first column is column zero, and the ranges are
#'   [begin, end) (i.e inclusive-exclusive).
tokenizer_fwf <- function(begin, end, na = "NA") {
  structure(list(begin = begin, end = end, na = na), class = "tokenizer_fwf")
}

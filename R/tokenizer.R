#' Tokenize a file/string.
#'
#' This turns a file into a list of tokens: each element of the list represents
#' one line. There are two special tokens: "[MISSING]" and "[EMPTY]".
#'
#' Usually the tokenization is done purely in C++, and never exposed to R
#' (because that requires a copy). This function is useful for testing, or
#' when a file doesn't parse correctly and you want to see the underlying
#' tokens.
#'
#' @inheritParams datasource
#' @param tokenizer A tokenizer specification.
#' @param n Optionally, maximum number of rows to tokenize.
#' @keywords internal
#' @export
#' @examples
#' tokenize("1,2\n3,4,5\n\n6")
#'
#' # Only tokenize first two lines
#' tokenize("1,2\n3,4,5\n\n6", n = 2)
tokenize <- function(file, tokenizer = tokenizer_csv(), n = NA_integer_) {
  ds <- datasource(file)
  tokenize_(ds, tokenizer, if (missing(n)) -1L else n)
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
#' @param na String to use for missing values.
#' @param delim Single character used to separate fields within a record.
#' @param quote Single character used to quote strings.
#' @param escape_double Does the file escape quotes by doubling them?
#'   i.e. If this option is \code{TRUE}, the value \code{""""} represents
#'   a single quote, \code{\"}.
#' @param escape_backslash Does the file use backslashes to escape special
#'   characters? This is more general than \code{escape_double} as backslashes
#'   can be used to escape the delimeter character, the quote characer, or
#'   to add special characters like \code{\\n}.
tokenizer_delim <- function(delim, quote = '"', na = "NA",
                            escape_double = TRUE, escape_backslash = FALSE) {
  structure(
    list(
      delim = delim,
      quote = quote,
      na = na,
      escape_double = escape_double,
      escape_backslash = escape_backslash
    ),
    class = "tokenizer_delim"
  )
}

#' @export
#' @rdname Tokenizers
tokenizer_csv <- function(na = "NA") {
  tokenizer_delim(
    delim = ",",
    quote = '"',
    na = na,
    escape_double = TRUE,
    escape_backslash = FALSE
  )
}

#' @export
#' @rdname Tokenizers
tokenizer_tsv <- function(na = "NA") {
  tokenizer_delim(
    delim = "\t",
    quote = '"',
    na = na,
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
#' @param begin,end Begin and end offsets for each file. These are C++
#'   offsets so the first column is column zero, and the ranges are
#'   [begin, end) (i.e inclusive-exclusive).
tokenizer_fwf <- function(begin, end, na = "NA") {
  structure(list(begin = begin, end = end, na = na), class = "tokenizer_fwf")
}

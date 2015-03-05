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
#' @inheritParams new_source
#' @param tokenizer A tokenizer specification.
#' @param n Optionally, maximum number of rows to tokenize.
#' @keywords internal
#' @export
#' @examples
#' tokenize(text = "1,2\n3,4,5\n\n6")
#'
#' # Only tokenize first two lines
#' tokenize(text = "1,2\n3,4,5\n\n6", n = 2)
tokenize <- function(path, text, tokenizer = csv_tokenizer(), n = NA_integer_) {
  tokenize_(new_source(path, text), tokenizer, if (missing(n)) -1L else n)
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
#' csv_tokenizer()
NULL

#' @export
#' @rdname Tokenizers
#' @param na String to use for missing values.
csv_tokenizer <- function(na = "NA") {
  structure(list(delim = ",", na = na), class = "tokenizer_delimited")
}

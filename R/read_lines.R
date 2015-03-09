#' Read lines from a file or string.
#'
#' @inheritParams new_source
#' @param n_max Number of lines to read. If \code{n} is -1, all lines in
#'   file will be read. For large files, this may
#' @return A character vector with one element for each line.
#' @export
#' @examples
#' read_lines(text = "1\n\n2")
#' tokenize(text = "1\n\n2", tokenizer = line_tokenizer())
read_lines <- function(path, text, n_max = -1L) {
  source <- new_source(path, text)
  read_lines_(source, n_max = n_max)
}

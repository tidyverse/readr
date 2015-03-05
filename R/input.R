#' Read a file into a string.
#'
#' @inheritParams new_source
#' @export
#' @examples
#' read_file(file.path(R.home(), "COPYING"))
#' read_file(text = "abc")
#' read_file(text = charToRaw("abc"))
read_file <- function(path, text) {
  read_file_(new_source(path, text))
}

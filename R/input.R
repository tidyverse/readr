#' Input directly into a string.
#'
#' @inheritParams new_source
#' @export
#' @examples
#' input(file.path(R.home(), "COPYING"))
#' input(text = "abc")
#' input(text = charToRaw("abc"))
input <- function(file, text) {
  input_source(new_source(file, text))
}

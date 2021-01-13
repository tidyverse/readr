#' @export
edition_set <- function(edition) {
  edition <- as.integer(edition)
  stopifnot(edition %in% c(1L, 2L))

  options("readr.edition" = edition)
}

edition_get <- function() {
  getOption("readr.edition", 2L)
}

edition_first <- function() {
  edition_get() == 1L
}

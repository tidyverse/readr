#' @export
edition_set <- function(edition) {
  stopifnot(edition %in% c(1, 2))

  Sys.setenv("readr.edition" = edition)
}

edition_get <- function() {
  Sys.getenv("readr.edition", 2)
}

edition_first <- function() {
  edition_get() == 1
}

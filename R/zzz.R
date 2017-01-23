.onLoad <- function(libname, pkgname) {
  op <- options()
  op.readr <- list(
    readr.show_progress = TRUE
  )
  toset <- !(names(op.readr) %in% names(op))
  if(any(toset)) options(op.readr[toset])
  invisible()
}

release_questions <- function() {
  c(
    "Have checked with the IDE team?"
  )
}

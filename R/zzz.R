.onLoad <- function(libname, pkgname) {
  opt <- options()
  opt_readr <- list(
    readr.show_progress = TRUE
  )
  to_set <- !(names(opt_readr) %in% names(opt))
  if(any(to_set)) options(opt_readr[to_set])
  invisible()
}

release_questions <- function() {
  c(
    "Have checked with the IDE team?"
  )
}

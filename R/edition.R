edition_set <- function(edition) {
  edition <- as.integer(edition)
  stopifnot(edition %in% c(1L, 2L))

  old <- edition_get()

  options("readr.edition" = edition)

  invisible(old)
}

#' @rdname with_edition
#' @export
edition_get <- function() {
  getOption("readr.edition", 2L)
}

#' Temporarily change the active readr edition
#'
#' `with_edition()` allows you to change the active edition of readr for a given block of code.
#' `local_edition()` allows you to change the active edition of readr until the end of the current function or file.
#' `edition_get()` allows you to retrieve the currently active edition.
#'
#' @export
#' @param edition Should be a single integer.
#' @param env Environment that controls scope of changes. For expert use only.
#' @param code Code to run with the changed edition.
with_edition <- function(edition, code) {
  local_edition(edition)
  code
}

#' @rdname with_edition
#' @export
local_edition <- function(edition, env = parent.frame()) {
  rlang::check_installed("withr")
  old <- edition_set(edition)
  withr::defer(edition_set(old), envir = env)
}

edition_first <- function() {
  edition_get() == 1L
}

edition_set <- function(edition) {
  edition <- as.integer(edition)
  stopifnot(edition %in% c(1L, 2L))

  old <- edition_get()

  options("readr.edition" = edition)

  invisible(old)
}

#' Retrieve the currently active edition
#'
#' @returns An integer corresponding to the currently active edition.
#' @export
#' @examples
#' edition_get()
edition_get <- function() {
  getOption("readr.edition", 2L)
}

#' Temporarily change the active readr edition
#'
#' `with_edition()` allows you to change the active edition of readr for a given
#' block of code. `local_edition()` allows you to change the active edition of
#' readr until the end of the current function or file.
#'
#' @export
#' @param edition Should be a single integer, such as `1` or `2`.
#' @param env Environment that controls scope of changes. For expert use only.
#' @param code Code to run with the changed edition.
#'
#' @examples
#' with_edition(1, edition_get())
#' with_edition(2, edition_get())
#'
#' # readr 1e and 2e behave differently when input rows have different number
#' # number of fields
#' with_edition(1, read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z")))
#' with_edition(2, read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z")))
#'
#' # local_edition() applies in a specific scope, for example, inside a function
#' read_csv_1e <- function(...) {
#'   local_edition(1)
#'   read_csv(...)
#' }
#' read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z"))      # 2e behaviour
#' read_csv_1e("1,2\n3,4,5", col_names = c("X", "Y", "Z"))   # 1e behaviour
#' read_csv("1,2\n3,4,5", col_names = c("X", "Y", "Z"))      # 2e behaviour
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

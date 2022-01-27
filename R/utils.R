# Silence R CMD check note
#' @importFrom tibble tibble
NULL

isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

`%||%` <- function(a, b) if (is.null(a)) b else a

is_syntactic <- function(x) make.names(x) == x

#' Determine whether progress bars should be shown
#'
#' By default, readr shows progress bars. However, progress reporting is
#' suppressed if any of the following conditions hold:
#' - The bar is explicitly disabled by setting
#'   `options(readr.show_progress = FALSE)`.
#' - The code is run in a non-interactive session, as determined by
#'   [rlang::is_interactive()].
#' - The code is run in an RStudio notebook chunk, as determined by
#'   `getOption("rstudio.notebook.executing")`.
#' @export
show_progress <- function() {
  isTRUE(getOption("readr.show_progress")) &&
    rlang::is_interactive() &&
    # some analysis re: rstudio.notebook.executing can be found in:
    # https://github.com/r-lib/rlang/issues/1031
    # TL;DR it's not consulted by is_interactive(), but probably should be
    # consulted for progress reporting specifically
    !isTRUE(getOption("rstudio.notebook.executing"))
}

#' Determine whether column types should be shown
#'
#' Wrapper around `getOption("readr.show_col_types")` that implements some fall
#' back logic if the option is unset. This returns:
#' * `TRUE` if the option is set to `TRUE`
#' * `FALSE` if the option is set to `FALSE`
#' * `FALSE` if the option is unset and we appear to be running tests
#' * `NULL` otherwise, in which case the caller determines whether to show
#'   column types based on context, e.g. whether `show_col_types` or actual
#'   `col_types` were explicitly specified
#' @export
should_show_types <- function() {
  opt <- getOption("readr.show_col_types", NA)
  if (isTRUE(opt)) {
    TRUE
  } else if (identical(opt, FALSE)) {
    FALSE
  } else if (is.na(opt) && is_testing()) {
    FALSE
  } else {
    NULL
  }
}

#' Determine whether reading should be done lazily
#'
#' Reading in readr is done lazily unless
#' - `options(readr.read_lazy = FALSE)`
#' @export
should_read_lazy <- function() {
  identical(getOption("readr.read_lazy", FALSE), TRUE)
}

deparse2 <- function(expr, ..., sep = "\n") {
  paste(deparse(expr, ...), collapse = sep)
}

is_integerish <- function(x) {
  floor(x) == x
}

#' Determine how many threads readr should use when processing
#'
#' The number of threads returned can be set by
#' - The global option `readr.num_threads`
#' - The environment variable `VROOM_THREADS`
#' - The value of [parallel::detectCores()]
#' @export
readr_threads <- function() {
  res <- getOption("readr.num_threads")

  if (is.null(res)) {
    res <- as.integer(Sys.getenv("VROOM_THREADS", parallel::detectCores()))
    options("readr.num_threads" = res)
  }

  if (is.na(res) || res <= 0) {
    res <- 1
  }

  res
}

#' @importFrom tibble as_tibble
#' @export
as_tibble.spec_tbl_df <- function(x, ...) {
  attr(x, "spec") <- NULL
  attr(x, "problems") <- NULL
  class(x) <- setdiff(class(x), "spec_tbl_df")
  NextMethod("as_tibble")
}

#' @export
as.data.frame.spec_tbl_df <- function(x, ...) {
  attr(x, "spec") <- NULL
  attr(x, "problems") <- NULL
  class(x) <- setdiff(class(x), "spec_tbl_df")
  NextMethod("as.data.frame")
}

#' @export
`[.spec_tbl_df` <- function(x, ...) {
  attr(x, "spec") <- NULL
  attr(x, "problems") <- NULL
  class(x) <- setdiff(class(x), "spec_tbl_df")
  NextMethod(`[`)
}

#' @importFrom methods setOldClass
setOldClass(c("spec_tbl_df", "tbl_df", "tbl", "data.frame"))

# @export
compare.tbl_df <- function(x, y, ...) {
  attr(x, "spec") <- NULL
  attr(x, "problems") <- NULL

  attr(y, "spec") <- NULL
  attr(y, "problems") <- NULL

  NextMethod("compare")
}

# @export
compare.col_spec <- function(x, y, ...) {
  x[["skip"]] <- NULL
  y[["skip"]] <- NULL

  NextMethod("compare")
}

# @export
compare_proxy.spec_tbl_df <- function(x, path) {
  attr(x, "spec") <- NULL
  attr(x, "problems") <- NULL
  class(x) <- setdiff(class(x), "spec_tbl_df")
  x

  if ("path" %in% names(formals(waldo::compare_proxy))) {
    list(object = x, path = path)
  } else {
    x
  }
}

is_named <- function(x) {
  nms <- names(x)

  if (is.null(nms)) {
    return(FALSE)
  }

  all(nms != "" & !is.na(nms))
}

utctime <- function(year, month, day, hour, min, sec, psec) {
  utctime_(
    as.integer(year), as.integer(month), as.integer(day),
    as.integer(hour), as.integer(min), as.integer(sec), as.numeric(psec)
  )
}

cli_block <- function(expr, class = NULL, type = rlang::inform) {
  msg <- ""
  withCallingHandlers(
    expr,
    message = function(x) {
      msg <<- paste0(msg, x$message)
      invokeRestart("muffleMessage")
    }
  )
  type(msg, class = class)
}

readr_enquo <- function(x) {
  if (rlang::quo_is_call(x, "c") || rlang::quo_is_call(x, "list")) {
    return(rlang::as_quosures(rlang::get_expr(x)[-1], rlang::get_env(x)))
  }
  x
}

check_string <- function(x, nm = deparse(substitute(x)), optional = FALSE) {
  if (rlang::is_string(x)) {
    return()
  }
  if (optional && is.null(x)) {
    return()
  }
  cli::cli_abort("{.code {nm}} must be a string.")
}

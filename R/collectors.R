collector <- function(type, ...) {
  structure(list(...), class = c(paste0("collector_", type), "collector"))
}

#' @export
print.collector <- function(x, ...) {
  cat("<", class(x)[1], ">\n", sep = "")
}

collector_find <- function(name) {
  get(paste0("col_", name), envir = asNamespace("readr"))()
}

#' Column parsing specifications.
#'
#' @name collector
NULL

#' @rdname collector
#' @export
col_character <- function() {
  collector("character")
}

#' @rdname collector
#' @export
col_integer <- function() {
  collector("integer")
}

#' @rdname collector
#' @export
col_double <- function() {
  collector("double")
}

#' @rdname collector
#' @export
col_euro_double <- function() {
  collector("euro_double")
}

#' @rdname collector
#' @export
col_numeric <- function() {
  collector("numeric")
}

#' @rdname collector
#' @export
col_logical <- function() {
  collector("logical")
}

#' @param format Format string passed on to the \code{\link{parse_date}}.
#' @param tz Default time zone to use for input and output (format).
#' @rdname collector
#' @export
col_datetime <- function(format = "", tz = "UTC") {
  collector("datetime", format = format, tz = tz)
}

#' @param levels Character vector providing set of allowed levels.
#' @param ordered Is it an ordered factor?
#' @rdname collector
#' @export
col_factor <- function(levels, ordered = FALSE) {
  collector("factor", levels = levels, ordered = ordered)
}


#' @rdname collector
#' @export
col_skip <- function() {
  collector("skip")
}

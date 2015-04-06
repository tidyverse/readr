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

#' Parse character vectors into typed columns.
#'
#' Use \code{parse_} if you have a character vector you want to parse. Use
#' \code{col_} in conjunction with a \code{read_} function to parse the
#' values as they're read in.
#'
#' @name collector
#' @param x Character vector of values to parse.
#' @seealso \code{\link{parse_datetime}}, \code{\link{type_convert}} to
#'   automatically re-parse all character columns in a data frame.
#' @examples
#' parse_integer(c("1", "2", "3"))
#' parse_double(c("1", "2", "3.123"))
#' parse_euro_double(c("1", "2", "3,123"))
#' parse_factor(c("a", "b"), letters)
#' parse_numeric("$1,123,456.000")
NULL

#' @rdname collector
#' @export
col_character <- function() {
  collector("character")
}

#' @rdname collector
#' @export
parse_character <- function(x) {
  parse_vector(x, col_character())
}

#' @rdname collector
#' @export
col_integer <- function() {
  collector("integer")
}

#' @rdname collector
#' @export
parse_integer <- function(x) {
  parse_vector(x, col_integer())
}

#' @rdname collector
#' @export
col_double <- function() {
  collector("double")
}

#' @rdname collector
#' @export
parse_double <- function(x) {
  parse_vector(x, col_double())
}

#' @rdname collector
#' @export
col_euro_double <- function() {
  collector("euro_double")
}

#' @rdname collector
#' @export
parse_euro_double <- function(x) {
  parse_vector(x, col_euro_double())
}


#' @rdname collector
#' @export
col_numeric <- function() {
  collector("numeric")
}

#' @rdname collector
#' @export
parse_numeric <- function(x) {
  parse_vector(x, col_numeric())
}

#' @rdname collector
#' @export
col_logical <- function() {
  collector("logical")
}

#' @rdname collector
#' @export
parse_logical <- function(x) {
  parse_vector(x, col_logical())
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
parse_factor <- function(x, levels, ordered = FALSE) {
  parse_vector(x, col_factor(levels, ordered))
}

#' @rdname collector
#' @export
col_skip <- function() {
  collector("skip")
}

# More complex ------------------------------------------------------------

#' @rdname parse_datetime
#' @export
col_datetime <- function(format = "", tz = "UTC") {
  collector("datetime", format = format, tz = tz)
}


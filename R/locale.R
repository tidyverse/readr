#' Create locales
#'
#' A locale object tries to capture all the defaults that can vary between
#' countries. You set the locale in once, and the details are automatically
#' passed on down to the columns parsers. The defaults have been chosen to
#' match R (i.e. US English) as closely as possible.
#'
#' @param date_names Character representations of day and month names. Either
#'   a string, which is passed on to \code{\link{date_names_locale}}, or
#'   an object created by \code{\link{date_names}}.
#' @param date_format,time_format Default date and time formats.
#' @param decimal_mark,grouping_mark Symbols used to indicate the decimal
#'   place, and to chunk larger numbers.
#' @param tz Default time zone.
#' @param encoding Default encoding
#' @export
#' @examples
#' locale()
#' locale("fr")
#'
#' # South American locale
#' locale("es_MX", decimal_mark = ",", grouping_mark = ".")
locale <- function(date_names = "en",
                   date_format = "%Y-%m-%d", time_format = "%H:%M",
                   decimal_mark = ".", grouping_mark = ",",
                   tz = "UTC", encoding = "UTF-8") {
  if (is.character(date_names)) {
    date_names <- date_names_locale(date_names)
  }
  stopifnot(is.date_names(date_names))
  stopifnot(is.character(decimal_mark), length(decimal_mark) == 1)
  stopifnot(is.character(grouping_mark), length(grouping_mark) == 1)
  check_tz(tz)
  check_encoding(encoding)

  structure(
    list(
      date_names = date_names,
      date_format = date_format,
      time_format = time_format,
      decimal_mark = decimal_mark,
      grouping_mark = grouping_mark,
      tz = tz,
      encoding = encoding
    ),
    class = "locale"
  )
}

check_tz <- function(x) {
  stopifnot(is.character(x), length(x) == 1)

  if (x %in% OlsonNames())
    return(TRUE)

  stop("Unknown TZ ", x, call. = FALSE)
}
check_encoding <- function(x) {
  stopifnot(is.character(x), length(x) == 1)

  if (x %in% iconvlist())
    return(TRUE)

  stop("Unknown encoding ", x, call. = FALSE)
}

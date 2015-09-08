#' Create or retrieve date names
#'
#' When parsing dates, you often need to know how weekdays of the week and
#' months are represented as text. This pair of functions allows you to either
#' create your own, or retrieve from a standard list. The standard list is
#' derived from ICU (\url{http://site.icu-project.org}) via the stringi package.
#'
#' @param mon,mon_ab Full and abbreviated month names. Starts with Sunday.
#' @param day,day_ab Full and abbreviated week day names
#' @param am_pm Names used for AM and PM.
#' @export
#' @examples
#' date_names_locale("en")
#' date_names_locale("ko")
#'
#' date_names_locale("fr")
#' if (require("stringi")) {
#'   date_names_locale("fr", as_ascii = TRUE)
#' }
date_names <- function(mon, mon_ab = mon, day, day_ab = day,
                       am_pm = c("AM", "PM")) {
  stopifnot(is.character(mon), length(mon) == 12)
  stopifnot(is.character(mon_ab), length(mon_ab) == 12)
  stopifnot(is.character(day), length(day) == 7)
  stopifnot(is.character(day_ab), length(day_ab) == 7)

  structure(
    list(mon = mon, mon_ab = mon_ab, day = day, day_ab = day_ab, am_pm = am_pm),
    class = "date_names"
  )
}

#' @export
#' @rdname date_names
#' @param locale A BCP 47 locale, made up of a languge and a region,
#'   e.g. \code{en_US} for American English. See \code{date_names_locales()}
#'   for a complete list of available locales.
#' @param as_ascii Should accents be stripped and the names converted to ASCII?
#'   This is useful if you're dealing with ASCII data where the correct
#'   spellings have been lost. Requires the \pkg{stringi} package.
date_names_locale <- function(locale, as_ascii = FALSE) {
  stopifnot(is.character(locale), length(locale) == 1)

  symbols <- date_symbols[[locale]]
  if (is.null(symbols)) {
    # See if we have a set for the base language
    base <- strsplit(locale, "_", fixed = TRUE)[[1]][1]
    symbols <- date_symbols[[base]]
  }

  if (is.null(symbols)) {
    stop("Unknown locale '", locale, "'", call. = FALSE)
  }

  if (as_ascii) {
    symbols[] <- lapply(symbols, stringi::stri_trans_general, id = "latin-ascii")
  }

  symbols
}

#' @export
#' @rdname date_names
date_names_locales <- function() {
  names(date_symbols)
}

#' @export
print.date_names <- function(x, ...) {
  cat("<date_names>\n")

  if (identical(x$day, x$day_ab)) {
    day <- paste0(x$day, collapse = ", ")
  } else {
    day <- paste0(x$day, " (", x$day_ab, ")", collapse = ", ")
  }

  if (identical(x$mon, x$mon_ab)) {
    mon <- paste0(x$mon, collapse = ", ")
  } else {
    mon <- paste0(x$mon, " (", x$mon_ab, ")", collapse = ", ")
  }
  am_pm <- paste0(x$am_pm, collapse = "/")

  cat_wrap("Days:   ", day)
  cat_wrap("Months: ",  mon)
  cat_wrap("AM/PM:  ", am_pm)
}

is.date_names <- function(x) inherits(x, "date_names")

cat_wrap <- function(header, body) {
  body <- strwrap(body, exdent = nchar(header))
  cat(header, paste(body, collapse = "\n"), "\n", sep = "")
}

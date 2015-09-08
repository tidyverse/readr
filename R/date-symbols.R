date_names <- function(locale) {
  stopifnot(is.character(locale), length(locale) == 1)

  locale <- tolower(locale)
  symbols <- date_symbols[[locale]]
  if (!is.null(symbols)) {
    return(symbols)
  }

  # See if we have a set for the base language
  base <- strsplit(locale, "_", fixed = TRUE)[[1]][1]
  symbols <- date_symbols[[base]]
  if (!is.null(symbols)) {
    return(symbols)
  }

  stop("Unknown locale '", locale, "'", call. = FALSE)
}

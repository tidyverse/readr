#' Return melted data for each token
#'
#' For certain non-rectangular data format, it can be useful to parse the data
#' into a melted format where each row is a single token.
#' @inheritParams read_delim
#' @export
melt_delim <- function(file, delim, quote = '"',
                       escape_backslash = FALSE, escape_double = TRUE,
                       locale = default_locale(),
                       na = c("", "NA"), quoted_na = TRUE,
                       comment = "", trim_ws = FALSE,
                       skip = 0, n_max = Inf) {
  tokenizer <- tokenizer_delim(delim, quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na, quoted_na = quoted_na, comment = comment, trim_ws = trim_ws)

  file <- standardise_path(file)
  ds <- datasource(file, skip = skip, comment = comment)
  melt_tokens(ds, tokenizer, locale, n_max)
}

melt_tokens <- function(data, tokenizer, locale, n_max) {
  if (n_max == Inf) {
    n_max <- -1
  }
  melt_tokens_(data, tokenizer, locale, n_max)
}

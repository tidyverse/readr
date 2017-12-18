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
  if (!nzchar(delim)) {
    stop("`delim` must be at least one character, ",
      "use `melt_table()` for whitespace delimited input.", call. = FALSE)
  }
  tokenizer <- tokenizer_delim(delim, quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na, quoted_na = quoted_na, comment = comment, trim_ws = trim_ws)
  file <- standardise_path(file)
  ds <- datasource(file, skip = skip, comment = comment)
  melt_delimited(ds, tokenizer, locale, n_max)
}

melt_tokens <- function(data, tokenizer, locale_, n_max) {
  if (n_max == Inf) {
    n_max <- -1
  }
  melt_tokens_(data, tokenizer, locale_, n_max)
}

melt_delimited <- function(file, tokenizer, locale = default_locale(), skip = 0,
                           comment = "", n_max = Inf,
                           guess_max = min(1000, n_max)) {
  name <- source_name(file)
  # If connection needed, read once.
  file <- standardise_path(file)
  if (is.connection(file)) {
    data <- read_connection(file)
  } else {
    if (empty_file(file)) {
       return(tibble::data_frame())
    }
    if (is.character(file) && identical(locale$encoding, "UTF-8")) {
      # When locale is not set, file is probablly marked as its correct encoding.
      # As default_locale() assumes file is UTF-8, file should be encoded as UTF-8 for non-UTF-8 MBCS locales.
      data <- enc2utf8(file)
    } else {
      data <- file
    }
  }

  ds <- datasource(data, comment = comment)

  melt_tokens(ds, tokenizer, locale_ = locale, n_max = n_max)
}

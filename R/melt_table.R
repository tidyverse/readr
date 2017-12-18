#' Return melted data for each token in a whitespace-separated file
#'
#' @inheritParams read_table
#' @export
melt_table <- function(file, locale = default_locale(), na = "NA", skip = 0,
                       n_max = Inf, guess_max = min(n_max, 1000),
                       comment = "") {
  ds <- datasource(file, skip = skip)
  columns <- fwf_empty(ds, skip = skip, n = guess_max, comment = comment)
  skip <- skip + columns$skip

  tokenizer <- tokenizer_fwf(columns$begin, columns$end, na = na, comment = comment)

  ds <- datasource(file = ds, skip = skip)

  melt_tokens(ds, tokenizer, locale_ = locale, n_max = n_max)
}

#' @rdname melt_table
#' @export
melt_table2 <- function(file, locale = default_locale(), na = "NA", skip = 0,
                       n_max = Inf, comment = "") {
  tokenizer <- tokenizer_ws(na = na, comment = comment)
  melt_delimited(file, tokenizer, locale = locale, skip = skip,
                 comment = comment, n_max = n_max,)
}


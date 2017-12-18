#' Return melted data for each token in a fixed width file
#'
#' For certain non-rectangular data format, it can be useful to parse the data
#' into a melted format where each row is a single token.
#' @inheritParams melt_fwf
#' @export
melt_fwf <- function(file, col_positions,
                     locale = default_locale(), na = c("", "NA"),
                     comment = "", trim_ws = TRUE, skip = 0, n_max = Inf) {
  ds <- datasource(file, skip = skip)
  if (inherits(ds, "source_file") && empty_file(file)) {
    return(tibble::tibble())
  }

  tokenizer <- tokenizer_fwf(col_positions$begin, col_positions$end, na = na, comment = comment, trim_ws = trim_ws)

  melt_tokens(ds, tokenizer, locale_ = locale,
              n_max = if (n_max == Inf) -1 else n_max)
}


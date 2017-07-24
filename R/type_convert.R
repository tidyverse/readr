#' Re-convert character columns in existing data frame
#'
#' This is useful if you need to do some manual munging - you can read the
#' columns in as character, clean it up with (e.g.) regular expressions and
#' then let readr take another stab at parsing it. The name is a homage to
#' the base \code{\link[utils]{type.convert}()}.
#'
#' @param df A data frame.
#' @param col_types One of `NULL`, a [cols()] specification, or
#'   a string. See `vignette("readr")` for more details.
#'
#'   If `NULL`, all column types will be imputed from the first 1000 rows
#'   on the input. This is convenient (and fast), but not robust. If the
#'   imputation fails, you'll need to supply the correct types yourself.
#'
#'   If a column specification created by [cols()], it must contain
#'   one column specification for each column. If you only want to read a
#'   subset of the columns, use [cols_only()].
#'
#'   Unlike other functions `type_convert()` does not allow character
#'   specifications of `col_types`.
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @export
#' @examples
#' df <- data.frame(
#'   x = as.character(runif(10)),
#'   y = as.character(sample(10)),
#'   stringsAsFactors = FALSE
#' )
#' str(df)
#' str(type_convert(df))
#'
#' df <- data.frame(x = c("NA", "10"), stringsAsFactors = FALSE)
#' str(type_convert(df))
#'
#' # Type convert can be used to infer types from an entire dataset
#' type_convert(
#'   read_csv(readr_example("mtcars.csv"),
#'            col_types = cols(.default = col_character())))
type_convert <- function(df, col_types = NULL, na = c("", "NA"), trim_ws = TRUE,
                         locale = default_locale()) {
  stopifnot(is.data.frame(df))
  is_character <- vapply(df, is.character, logical(1))

  char_cols <- df[is_character]
  guesses <- lapply(char_cols, function(x) {
    x[x %in% na] <- NA
    guess_parser(x, locale)
  })

  if (is.character(col_types)) {
    stop("`col_types` must be `NULL` or a `cols` specification for `type_convert()`.",
      call. = FALSE)
  }

  specs <- col_spec_standardise(
    col_types = col_spec_limit_names(col_types, names(char_cols)),
    col_names = names(char_cols),
    guessed_types =  guesses
  )

  if (is.null(col_types)) {
    show_cols_spec(specs)
  }

  df[is_character] <- lapply(seq_along(char_cols), function(i) {
    type_convert_col(char_cols[[i]], specs$cols[[i]], which(is_character)[i],
      locale_ = locale, na = na, trim_ws = trim_ws)
  })

  df
}

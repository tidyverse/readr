#' Re-convert character columns in existing data frame.
#'
#' This is useful if you need to do some manual munging - you can read the
#' columns in as character, clean it up with (e.g.) regular expressions and
#' then let readr take another stab at parsing it.
#'
#' @param df A data frame.
#' @inheritParams col_types_standardise
#' @export
#' @examples
#' df <- data.frame(
#'   x = as.character(runif(10)),
#'   y = as.character(sample(10)),
#'   stringsAsFactors = FALSE
#' )
#' str(df)
#' str(type_convert(df))
type_convert <- function(df, col_types = NULL) {
  is_character <- vapply(df, is.character, logical(1))

  guesses <- lapply(df[is_character], collectorGuess)
  col_types <- col_types_standardise(col_types, names(df), guesses)

  df[is_character] <- Map(type_convert_col, df[is_character], col_types, which(is_character))
  df
}

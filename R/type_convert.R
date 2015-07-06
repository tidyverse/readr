#' Re-convert character columns in existing data frame.
#'
#' This is useful if you need to do some manual munging - you can read the
#' columns in as character, clean it up with (e.g.) regular expressions and
#' then let readr take another stab at parsing it.
#'
#' @param df A data frame.
#' @inheritParams col_types_standardise
#' @param guess automatically guess types for character columns
#' @export
#' @examples
#' df <- data.frame(
#'   x = as.character(runif(10)),
#'   y = as.character(sample(10)),
#'   stringsAsFactors = FALSE
#' )
#' str(df)
#' str(type_convert(df))
type_convert <- function(df, col_types = NULL, guess = TRUE) {
  # if guess flag is set, guess character columns
  is_guessed <- if ( guess ) vapply(df, is.character, logical(1)) else rep_len(FALSE, ncol(df))
  # columns to be converted
  is_converted <- if (!is.null(names(col_types))) {
    # column is guessed or listed in col_types
    is_guessed | names(df) %in% col_types
  } else {
    # no names, all columns have to be converted
    rep_len( TRUE, ncol(df) )
  }

  guesses <- lapply(df[is_guessed], collectorGuess)
  names(guesses) <- names(df)[is_guessed]
  col_types <- col_types_standardise(col_types, names(df)[is_converted], guesses)

  df[is_converted] <- Map(type_convert_col, df[is_converted], col_types, which(is_converted))
  df
}

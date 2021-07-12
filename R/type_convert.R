#' Re-convert character columns in existing data frame
#'
#' This is useful if you need to do some manual munging - you can read the
#' columns in as character, clean it up with (e.g.) regular expressions and
#' then let readr take another stab at parsing it. The name is a homage to
#' the base [utils::type.convert()].
#'
#' @param df A data frame.
#' @param col_types One of `NULL`, a [cols()] specification, or
#'   a string. See `vignette("readr")` for more details.
#'
#'   If `NULL`, column types will be imputed using all rows.
#' @inheritParams tokenizer_delim
#' @inheritParams read_delim
#' @note `type_convert()` removes a 'spec' attribute,
#' because it likely modifies the column data types.
#' (see [spec()] for more information about column specifications).
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
#'
#' # first read the data as character
#' data <- read_csv(readr_example("mtcars.csv"),
#'   col_types = list(.default = col_character())
#' )
#' str(data)
#' # Then convert it with type_convert
#' type_convert(data)
type_convert <- function(df, col_types = NULL, na = c("", "NA"), trim_ws = TRUE,
                         locale = default_locale()) {
  stopifnot(is.data.frame(df))
  is_character <- vapply(df, is.character, logical(1))

  if (!any(is_character)) {
    warning("`type_convert()` only converts columns of type 'character'.\n- `df` has no columns of type 'character'", call. = FALSE)
  }

  char_cols <- df[is_character]

  col_types <- keep_character_col_types(df, col_types)

  guesses <- lapply(char_cols, guess_parser, locale = locale, na = na)

  specs <- col_spec_standardise(
    col_types = col_types,
    col_names = names(char_cols),
    guessed_types = guesses
  )

  if (is.null(col_types) && !is_testing()) {
    show_cols_spec(specs)
  }

  df[is_character] <- lapply(seq_along(char_cols), function(i) {
    type_convert_col(char_cols[[i]], specs$cols[[i]], which(is_character)[i],
      locale_ = locale, na = na, trim_ws = trim_ws
    )
  })

  attr(df, "spec") <- NULL

  df
}

keep_character_col_types <- function(df, col_types) {
  if (is.null(col_types)) {
    return(col_types)
  }

  is_character <- vapply(df, is.character, logical(1))
  if (is.character(col_types)) {
    if (length(col_types) != 1) {
      stop("`col_types` must be a single string.", call. = FALSE)
    }
    if (nchar(col_types) != length(df)) {
      stop(
        "`df` and `col_types` must have consistent lengths:\n",
        "  * `df` has length ", length(df), "\n",
        "  * `col_types` has length ", nchar(col_types),
        call. = FALSE
      )
    }

    idx <- which(is_character)
    col_types <- paste(substring(col_types, idx, idx), collapse = "")
    return(col_types)
  }

  char_cols <- names(df)[is_character]
  col_types$cols <- col_types$cols[names(col_types$cols) %in% char_cols]

  col_types
}

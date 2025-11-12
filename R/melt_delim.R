#' Return melted data for each token in a delimited file (including csv & tsv)
#'
#' `r lifecycle::badge("superseded")`
#' This function has been superseded in readr and moved to [the meltr
#' package](https://r-lib.github.io/meltr/).
#'
#' For certain non-rectangular data formats, it can be useful to parse the data
#' into a melted format where each row represents a single token.
#'
#' `melt_csv()` and `melt_tsv()` are special cases of the general
#' `melt_delim()`. They're useful for reading the most common types of
#' flat file data, comma separated values and tab separated values,
#' respectively. `melt_csv2()` uses `;` for the field separator and `,` for the
#' decimal point. This is common in some European countries.
#' @inheritParams read_delim
#' @return A [tibble()] of four columns:
#'   * `row`, the row that the token comes from in the original file
#'   * `col`, the column that the token comes from in the original file
#'   * `data_type`, the data type of the token, e.g. `"integer"`, `"character"`,
#'     `"date"`, guessed in a similar way to the `guess_parser()` function.
#'   * `value`, the token itself as a character string, unchanged from its
#'     representation in the original file.
#'
#'   If there are parsing problems, a warning tells you
#'   how many, and you can retrieve the details with [problems()].
#' @seealso [read_delim()] for the conventional way to read rectangular data
#' from delimited files.
#' @export
#' @examples
#' # Input sources -------------------------------------------------------------
#' # Read from a path
#' melt_csv(readr_example("mtcars.csv"))
#' melt_csv(readr_example("mtcars.csv.zip"))
#' melt_csv(readr_example("mtcars.csv.bz2"))
#' \dontrun{
#' melt_csv("https://github.com/tidyverse/readr/raw/main/inst/extdata/mtcars.csv")
#' }
#'
#' # Or directly from a string (must contain a newline)
#' melt_csv("x,y\n1,2\n3,4")
#'
#' # To import empty cells as 'empty' rather than `NA`
#' melt_csv("x,y\n,NA,\"\",''", na = "NA")
#'
#' # File types ----------------------------------------------------------------
#' melt_csv("a,b\n1.0,2.0")
#' melt_csv2("a;b\n1,0;2,0")
#' melt_tsv("a\tb\n1.0\t2.0")
#' melt_delim("a|b\n1.0|2.0", delim = "|")
#' @export
melt_delim <- function(
  file,
  delim,
  quote = '"',
  escape_backslash = FALSE,
  escape_double = TRUE,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  comment = "",
  trim_ws = FALSE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_delim()",
      details = "Please use `meltr::melt_delim()` instead"
    )
  }

  if (!nzchar(delim)) {
    stop(
      "`delim` must be at least one character, ",
      "use `melt_table()` for whitespace delimited input.",
      call. = FALSE
    )
  }
  tokenizer <- tokenizer_delim(
    delim,
    quote = quote,
    escape_backslash = escape_backslash,
    escape_double = escape_double,
    na = na,
    quoted_na = quoted_na,
    comment = comment,
    trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  melt_delimited(
    file,
    tokenizer,
    locale = locale,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    comment = comment,
    n_max = n_max,
    progress = progress
  )
}

#' @rdname melt_delim
#' @export
melt_csv <- function(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_csv()",
      details = "Please use `meltr::melt_csv()` instead"
    )
  }

  tokenizer <- tokenizer_csv(
    na = na,
    quoted_na = quoted_na,
    quote = quote,
    comment = comment,
    trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  melt_delimited(
    file,
    tokenizer,
    locale = locale,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    comment = comment,
    n_max = n_max,
    progress = progress
  )
}

#' @rdname melt_delim
#' @export
melt_csv2 <- function(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_csv2()",
      details = "Please use `meltr::melt_csv2()` instead"
    )
  }

  if (locale$decimal_mark == ".") {
    cli::cli_alert_info(
      "Using {.val ','} as decimal and {.val '.'} as grouping mark. Use {.fn read_delim} for more control."
    )
    locale$decimal_mark <- ","
    locale$grouping_mark <- "."
  }
  tokenizer <- tokenizer_delim(
    delim = ";",
    na = na,
    quoted_na = quoted_na,
    quote = quote,
    comment = comment,
    trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  melt_delimited(
    file,
    tokenizer,
    locale = locale,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    comment = comment,
    n_max = n_max,
    progress = progress
  )
}


#' @rdname melt_delim
#' @export
melt_tsv <- function(
  file,
  locale = default_locale(),
  na = c("", "NA"),
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_tsv()",
      details = "Please use `meltr::melt_tsv()` instead"
    )
  }

  tokenizer <- tokenizer_tsv(
    na = na,
    quoted_na = quoted_na,
    quote = quote,
    comment = comment,
    trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  melt_delimited(
    file,
    tokenizer,
    locale = locale,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    comment = comment,
    n_max = n_max,
    progress = progress
  )
}

# Helper functions for reading from delimited files ----------------------------
col_spec_melt <-
  structure(
    list(
      row = structure(
        list(),
        class = c(
          "collector_double",
          "collector"
        )
      ),
      col = structure(
        list(),
        class = c(
          "collector_double",
          "collector"
        )
      ),
      data_type = structure(
        list(),
        class = c(
          "collector_character",
          "collector"
        )
      ),
      value = structure(
        list(),
        class = c(
          "collector_character",
          "collector"
        )
      )
    ),
    .Names = c("row", "col", "data_type", "value")
  )

melt_tokens <- function(data, tokenizer, locale_, n_max, progress) {
  if (n_max == Inf) {
    n_max <- -1
  }
  melt_tokens_(data, tokenizer, col_spec_melt, locale_, n_max, progress)
}

melt_delimited <- function(
  file,
  tokenizer,
  locale = default_locale(),
  skip = 0,
  skip_empty_rows = FALSE,
  comment = "",
  n_max = Inf,
  progress = show_progress()
) {
  name <- source_name(file)
  # If connection needed, read once.
  file <- standardise_path(file)
  if (is.connection(file)) {
    data <- datasource_connection(
      file,
      skip,
      skip_empty_rows = skip_empty_rows,
      comment
    )
  } else {
    if (empty_file(file)) {
      return(tibble::tibble(
        row = double(),
        col = double(),
        data_type = character(),
        value = character()
      ))
    }
    if (is.character(file) && identical(locale$encoding, "UTF-8")) {
      # When locale is not set, file is probablly marked as its correct encoding.
      # As default_locale() assumes file is UTF-8, file should be encoded as UTF-8 for non-UTF-8 MBCS locales.
      data <- enc2utf8(file)
    } else {
      data <- file
    }
  }
  ds <- datasource(
    data,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    comment = comment
  )
  out <- melt_tokens(
    ds,
    tokenizer,
    locale_ = locale,
    n_max = n_max,
    progress = progress
  )
  warn_problems(out)
}

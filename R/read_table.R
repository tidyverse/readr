#' Read whitespace-separated columns into a tibble
#'
#' @description
#' `read_table()` is designed to read the type of textual
#' data where each column is separated by one (or more) columns of space.
#'
#' `read_table()` is like [read.table()], it allows any number of whitespace
#' characters between columns, and the lines can be of different lengths.
#'
#' `spec_table()` returns the column specifications rather than a data frame.
#'
#' @seealso [read_fwf()] to read fixed width files where each column
#'   is not separated by whitespace. `read_fwf()` is also useful for reading
#'   tabular data with non-standard formatting.
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams read_delim
#' @export
#' @examples
#' ws <- readr_example("whitespace-sample.txt")
#' writeLines(read_lines(ws))
#' read_table(ws)
#' @rdname read_table
#' @export
read_table <- function(
  file,
  col_names = TRUE,
  col_types = NULL,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  comment = "",
  show_col_types = should_show_types(),
  skip_empty_rows = TRUE
) {
  tokenizer <- tokenizer_ws(
    na = na,
    comment = comment,
    skip_empty_rows = skip_empty_rows
  )
  read_delimited(
    file,
    tokenizer,
    col_names = col_names,
    col_types = col_types,
    locale = locale,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    skip_quote = FALSE,
    comment = comment,
    n_max = n_max,
    guess_max = guess_max,
    progress = progress,
    show_col_types = show_col_types
  )
}

#' @rdname spec_delim
#' @export
spec_table <- generate_spec_fun(read_table)

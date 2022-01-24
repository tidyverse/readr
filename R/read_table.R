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
#' writeLines(read_file(ws))
#' read_table(ws, col_names = FALSE)

#' @rdname read_table
#' @export
read_table <- function(file, col_names = TRUE, col_types = NULL,
                        locale = default_locale(), na = "NA", skip = 0,
                        n_max = Inf, guess_max = min(n_max, 1000),
                        progress = show_progress(), comment = "",
                        show_col_types = should_show_types(),
                        skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_ws(
    na = na, comment = comment,
    skip_empty_rows = skip_empty_rows
  )
  read_delimited(file, tokenizer,
    col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, skip_empty_rows = skip_empty_rows,
    skip_quote = FALSE, comment = comment, n_max = n_max, guess_max = guess_max, progress = progress,
    show_col_types = show_col_types
  )
}

#' Read whitespace-separated columns into a tibble
#'
#' @description
#' `r lifecycle::badge("deprecated")`
#'
#' This function is deprecated because we renamed it to [read_table()] and
#' removed the old `read_table` function, which was too strict for most cases
#' and was analogous to just using `read_fwf()`.
#' @keywords internal
#' @export
read_table2 <- function(file, col_names = TRUE, col_types = NULL,
                        locale = default_locale(), na = "NA", skip = 0,
                        n_max = Inf, guess_max = min(n_max, 1000),
                        progress = show_progress(), comment = "",
                        skip_empty_rows = TRUE) {
  lifecycle::deprecate_soft("2.0.0", "read_table2()", "read_table()")
  read_table(
    file = file,
    col_names = col_names,
    col_types = col_types,
    locale = locale,
    na = na,
    skip = skip,
    n_max = n_max,
    guess_max = guess_max,
    progress = progress,
    comment = comment,
    skip_empty_rows = skip_empty_rows)
}

#' @rdname spec_delim
#' @export
spec_table <- generate_spec_fun(read_table)

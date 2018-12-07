#' Count the number of fields in each line of a file
#'
#' This is useful for diagnosing problems with functions that fail
#' to parse correctly.
#'
#' @inheritParams datasource
#' @param tokenizer A tokenizer that specifies how to break the `file`
#'   up into fields, e.g., [tokenizer_csv()],
#'   [tokenizer_fwf()]
#' @param n_max Optionally, maximum number of rows to count fields for.
#' @export
#' @examples
#' count_fields(readr_example("mtcars.csv"), tokenizer_csv())
count_fields <- function(file, tokenizer, skip = 0, n_max = -1L) {
  ds <- datasource(file, skip = skip, skip_empty_rows = FALSE)
  count_fields_(ds, tokenizer, n_max)
}

#' Read common/combined log file into a tibble
#'
#' This is a fairly standard format for log files - it uses both quotes
#' and square brackets for quoting, and there may be literal quotes embedded
#' in a quoted string. The dash, "-", is used for missing values.
#'
#' @inheritParams read_delim
#' @export
#' @examples
#' read_log(readr_example("example.log"))
read_log <- function(file, col_names = FALSE, col_types = NULL,
                      skip = 0, n_max = -1, progress = NULL) {
  progress <- progress %||% progress_defaults()
  tokenizer <- tokenizer_log()
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, progress = progress)
}

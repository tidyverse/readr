#' Parse
#'
#' This tokenizes then collects the input values into a single vector.
#' It's mostly useful for testing
#'
#' @inheritParams new_source
#' @keywords internal
#' @export
#' @examples
#' parse_vector("1,2,3,NA", csv_tokenizer(), col_integer())
#' parse_vector("1,2,3,NA", csv_tokenizer(), col_double())
#' parse_vector("1,2,3,NA", csv_tokenizer(), col_character())
#' parse_vector("1,2,3,NA", csv_tokenizer(), col_skip())
#'
#' # Invalid values are replaced with missing values with a warning.
#' parse_vector("1,2,-", csv_tokenizer(), col_double())
#' parse_vector("1,2,-", csv_tokenizer(), col_integer())
parse_vector <- function(text, tokenizer, collector) {
  parse_(new_source(text = text), tokenizer, collector)
}

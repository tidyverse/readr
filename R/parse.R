#' Parse
#'
#' This tokenizes then collects the input values into a single vector.
#' It's mostly useful for testing
#'
#' @inheritParams datasource
#' @keywords internal
#' @export
#' @examples
#' parse_vector("1,2,3,NA\n", tokenizer_csv(), col_integer())
#' parse_vector("1,2,3,NA\n", tokenizer_csv(), col_double())
#' parse_vector("1,2,3,NA\n", tokenizer_csv(), col_character())
#' parse_vector("1,2,3,NA\n", tokenizer_csv(), col_skip())
#'
#' # Invalid values are replaced with missing values with a warning.
#' parse_vector("1,2,-\n", tokenizer_csv(), col_double())
#' parse_vector("1,2,-\n", tokenizer_csv(), col_integer())
parse_vector <- function(file, tokenizer, collector) {
  ds <- datasource(file)
  parse_(ds, tokenizer, collector)
}

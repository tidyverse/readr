#' Parse into a vector.
#'
#' This tokenizes then collects the input values into a single vector.
#' It's mostly useful for testing
#'
#' @param text String to parse.
#' @keywords internal
#' @export
#' @examples
#' parse_vector("1,2,3,NA", tokenizer_csv(), col_integer())
#' parse_vector("1,2,3,NA", tokenizer_csv(), col_double())
#' parse_vector("1,2,3,NA", tokenizer_csv(), col_character())
#' parse_vector("1,2,3,NA", tokenizer_csv(), col_skip())
#'
#' parse_vector("1,2,3,.", tokenizer_csv(na = "."), col_double())
#'
#' # Invalid values are replaced with missing values with a warning.
#' parse_vector("1,2,-\n", tokenizer_csv(), col_double())
#' parse_vector("1,2,-\n", tokenizer_csv(), col_integer())
parse_vector <- function(text, tokenizer, collector) {
  ds <- datasource_string(text, 0)
  parse_(ds, tokenizer, collector)
}

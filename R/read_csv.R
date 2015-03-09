#' Read a csv file into a data frame.
#'
#' @inheritParams new_source
#' @inheritParams tokenizer_csv
#' @inheritParams col_names_standardise
#' @inheritParams col_types_standardise
#' @param n_max Maximum number of records to read.
#' @export
#' @examples
#' read_csv(text = "x,y\n1,2\n3,4")
#'
#' # Override default col types
#' read_csv(text = "x,y\n1,2\n3,4", col_types = "dd")
#' @useDynLib readr
#' @importClassesFrom Rcpp "C++Object"
read_csv <- function(path, text, col_names = TRUE, col_types = NULL, na = "NA",
                     skip = 0, n_max = -1) {
  source <- new_source(path, text, skip = skip)
  tokenizer <- tokenizer_csv(na = na)

  if (isTRUE(col_names))
    skip <- skip + 1
  col_names <- col_names_standardise(col_names, header(source, tokenizer))

  source <- new_source(path, text, skip = skip)
  col_types <- col_types_standardise(col_types, col_names, types(source, tokenizer))
  read_tokens(source, tokenizer, col_types, col_names, n_max = n_max)
}

# The header is the first row, parsed into fields
header <- function(source, tokenizer) {
  first <- read_lines_(source, n_max = 1)
  parse_vector(text = first, tokenizer = tokenizer, col_character())
}

types <- function(source, tokenizer) {
  collectorsGuess(source, tokenizer, n = 100)
}

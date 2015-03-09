#' Read a csv file into a data frame.
#'
#' @inheritParams new_source
#' @inheritParams tokenizer_csv
#' @inheritParams col_names_standardise
#' @inheritParams col_types_standardise
#' @export
#' @examples
#' read_csv(text = "1,2\n3,4", col_types = "ii", col_names = c("x", "y"))
read_csv <- function(path, text, col_names = TRUE, col_types = NULL, na = "NA") {
  source <- new_source(path, text)
  tokenizer <- tokenizer_csv(na = na)

  if (isTRUE(col_names))
    skip <- skip + 1
  col_names <- col_names_standardise(col_names, header(source, tokenizer))
  col_types <- col_types_standardise(col_types, col_names, types(source, tokenizer))

  read_tokens(source, tokenizer, col_types, col_names)
}

# The header is the first row, parsed into fields
header <- function(source, tokenizer) {
  first <- read_lines_(source, n_max = 1)
  parse_vector(text = first, tokenizer = tokenizer, col_character())
}

types <- function(source, tokenizer) {
  collectorsGuess(source, tokenizer, n = 100)
}

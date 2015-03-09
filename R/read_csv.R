#' Read a csv file into a data frame.
#'
#' @inheritParams new_source
#' @inheritParams tokenizer_csv
#' @inheritParams columns
#' @export
#' @examples
#' read_csv(text = "1,2\n3,4", col_types = "ii", col_names = c("x", "y"))
read_csv <- function(path, col_types, col_names, na = "NA", text = NULL) {
  source <- new_source(path, text)
  tokenizer <- tokenizer_csv(na = na)
  collectors <- columns(col_types, col_names)

  read_tokens(source, tokenizer, collectors$col_types)
}

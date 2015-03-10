#' Read a csv file into a data frame.
#'
#' @inheritParams datasource
#' @inheritParams tokenizer_csv
#' @inheritParams col_names_standardise
#' @inheritParams col_types_standardise
#' @param n_max Maximum number of records to read.
#' @export
#' @examples
#' read_csv("x,y\n1,2\n3,4")
#'
#' # Override default col types
#' read_csv("x,y\n1,2\n3,4", col_types = "dd")
#' @useDynLib readr
#' @importClassesFrom Rcpp "C++Object"
read_csv <- function(file, col_names = TRUE, col_types = NULL, na = "NA",
                     skip = 0, n_max = -1) {
  ds <- datasource(file, skip = skip)
  tokenizer <- tokenizer_csv(na = na)

  if (isTRUE(col_names))
    skip <- skip + 1
  col_names <- col_names_standardise(col_names, header(ds, tokenizer))

  ds <- datasource(file, skip = skip)
  col_types <- col_types_standardise(col_types, col_names, types(ds, tokenizer))
  read_tokens(ds, tokenizer, col_types, col_names, n_max = n_max)
}

# The header is the first row, parsed into fields
header <- function(datasource, tokenizer) {
  first <- read_lines_(datasource, n_max = 1)
  parse_vector(datasource_string(first, 0), tokenizer = tokenizer, col_character())
}

types <- function(source, tokenizer) {
  collectorsGuess(source, tokenizer, n = 100)
}


#' Save a data frame to a csv file.
#'
#' This is about twice as fast as \code{\link{write.csv}}, and never
#' writes row names.
#'
#' @param x A data frame to write to disk
#' @param path Path to write to.
#' @param append If \code{FALSE}, will create a new file. If \code{TRUE},
#'   will append to an existing file.
#' @param col_names Write columns names at the top of the file?
#' @export
write_csv <- function(x, path, append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))

  path <- normalizePath(path, mustWork = FALSE)
  stream_csv(x, path, col_names = col_names, append = append)
}

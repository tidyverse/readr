#' Read text file where columns are separated by whitespace.
#'
#' This is designed to read the type of textual data where each column is
#' separate by one (or more) columns of space. Each line is the same length,
#' and each field is in the same position in every line. It's similar to
#' \code{\link{read.table}}, but rather parsing like a file delimited by
#' arbitrary amounts of whitespace, it first finds empty columns and then
#' parses like a fixed width file.
#'
#' @seealso \code{\link{read_fwf}} to read fixed width files where each column
#'   is not separated by whitespace. \code{read_fwf} is also useful for reading
#'   tabular data with non-standard formatting.
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams col_names_standardise
#' @inheritParams col_types_standardise
#' @inheritParams read_delim
#' @export
#' @examples
#' # One corner from http://www.masseyratings.com/cf/compare.htm
#' massey <- system.file("extdata/massey-rating.txt", package = "readr")
#' cat(read_file(massey))
#' read_table(massey)
#'
#' # Sample of 1978 fuel economy data from
#' # http://www.fueleconomy.gov/feg/epadata/78data.zip
#' epa <- system.file("extdata/epa78.txt", package = "readr")
#' cat(read_file(epa))
#' read_table(epa, col_names = FALSE)
read_table <- function(file, col_names = TRUE, col_types = NULL,
                       locale = default_locale(), na = "NA",
                       skip = 0, n_max = -1) {
  columns <- fwf_empty(file, skip = skip)

  ds <- datasource(file, skip = skip)
  tokenizer <- tokenizer_fwf(columns$begin, columns$end, na = na)

  if (isTRUE(col_names))
    skip <- skip + 1
  col_names <- col_names_standardise(col_names, read_header(ds, tokenizer, locale))

  ds <- datasource(file, skip = skip)
  col_types <- col_types_standardise(col_types, col_names,
    types(ds, tokenizer, locale))
  read_tokens(ds, tokenizer, col_types, col_names, locale_ = locale,
    n_max = n_max)
}

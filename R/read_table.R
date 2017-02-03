#' Read whitespace-separated columns into a tibble
#'
#' This is designed to read the type of textual data where each column is
#' separate by one (or more) columns of space. Each line is the same length,
#' and each field is in the same position in every line. It's similar to
#' [read.table()], but rather parsing like a file delimited by
#' arbitrary amounts of whitespace, it first finds empty columns and then
#' parses like a fixed width file. `spec_table()` returns the column
#' specification rather than a data frame.
#'
#' @seealso [read_fwf()] to read fixed width files where each column
#'   is not separated by whitespace. `read_fwf()` is also useful for reading
#'   tabular data with non-standard formatting.
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams read_delim
#' @export
#' @examples
#' # One corner from http://www.masseyratings.com/cf/compare.htm
#' massey <- readr_example("massey-rating.txt")
#' cat(read_file(massey))
#' read_table(massey)
#'
#' # Sample of 1978 fuel economy data from
#' # http://www.fueleconomy.gov/feg/epadata/78data.zip
#' epa <- readr_example("epa78.txt")
#' cat(read_file(epa))
#' read_table(epa, col_names = FALSE)
read_table <- function(file, col_names = TRUE, col_types = NULL,
                       locale = default_locale(), na = "NA", skip = 0,
                       n_max = Inf, guess_max = min(n_max, 1000),
                       progress = show_progress(), comment = "") {
  columns <- fwf_empty(file, skip = skip, n = guess_max, comment = comment)
  skip <- skip + columns$skip

  tokenizer <- tokenizer_fwf(columns$begin, columns$end, na = na, comment = comment)

  spec <- col_spec_standardise(
    file = file, skip = skip, n = guess_max,
    col_names = col_names, col_types = col_types,
    locale = locale, tokenizer = tokenizer
  )

  if (progress) {
     print(spec, n = getOption("readr.num_columns", 20))
  }

  ds <- datasource(file, skip = skip + isTRUE(col_names))
  res <- read_tokens(ds, tokenizer, spec$cols, names(spec$cols), locale_ = locale,
    n_max = n_max, progress = progress)
  attr(res, "spec") <- spec

  res
}

#' @rdname spec_delim
#' @export
spec_table <- generate_spec_fun(read_table)

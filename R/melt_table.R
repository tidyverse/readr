#' Return melted data for each token in a whitespace-separated file
#'
#' @description
#'
#' For certain non-rectangular data formats, it can be useful to parse the data
#' into a melted format where each row represents a single token.
#'
#' `melt_table()` and `melt_table2()` are designed to read the type of textual
#' data where each column is separated by one (or more) columns of space.
#'
#' `melt_table2()` allows any number of whitespace characters between columns,
#' and the lines can be of different lengths.
#'
#' `melt_table()` is more strict, each line must be the same length,
#' and each field is in the same position in every line. It first finds empty
#' columns and then parses like a fixed width file.
#'
#' @seealso [melt_fwf()] to melt fixed width files where each column
#'   is not separated by whitespace. `melt_fwf()` is also useful for reading
#'   tabular data with non-standard formatting.  [read_table()] is the
#'   conventional way to read tabular data from whitespace-separated files.
#' @inheritParams read_table
#' @export
#' @examples
#' # One corner from http://www.masseyratings.com/cf/compare.htm
#' massey <- readr_example("massey-rating.txt")
#' cat(read_file(massey))
#' melt_table(massey)
#'
#' # Sample of 1978 fuel economy data from
#' # http://www.fueleconomy.gov/feg/epadata/78data.zip
#' epa <- readr_example("epa78.txt")
#' cat(read_file(epa))
#' melt_table(epa)
melt_table <- function(file, locale = default_locale(), na = "NA", skip = 0,
                       n_max = Inf, guess_max = min(n_max, 1000),
                       progress = show_progress(), comment = "",
                       skip_empty_rows = FALSE) {
  ds <- datasource(file, skip = skip)
  if (inherits(ds, "source_file") && empty_file(file)) {
       return(tibble::data_frame(row = double(), col = double(),
                                 data_type = character(), value = character()))
  }

  columns <- fwf_empty(ds, skip = skip, n = guess_max, comment = comment)
  tokenizer <- tokenizer_fwf(columns$begin, columns$end, na = na,
                             comment = comment,
                             skip_empty_rows = skip_empty_rows)

  ds <- datasource(file = ds, skip = skip)
  out <- melt_tokens(ds, tokenizer, locale_ = locale, n_max = n_max,
                     progress = progress)
  warn_problems(out)
}

#' @rdname melt_table
#' @export
melt_table2 <- function(file, locale = default_locale(), na = "NA", skip = 0,
                       n_max = Inf, progress = show_progress(), comment = "",
                       skip_empty_rows = FALSE) {
  ds <- datasource(file, skip = skip)
  if (inherits(ds, "source_file") && empty_file(file)) {
       return(tibble::data_frame(row = double(), col = double(),
                                 data_type = character(), value = character()))
  }
  tokenizer <- tokenizer_ws(na = na, comment = comment,
                            skip_empty_rows = skip_empty_rows)

  ds <- datasource(file = ds, skip = skip)
  melt_delimited(ds, tokenizer, locale = locale, skip = skip,
                 comment = comment, n_max = n_max, progress = progress)
}

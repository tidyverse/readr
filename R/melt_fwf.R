

#' Return melted data for each token in a fixed width file
#'
#' For certain non-rectangular data formats, it can be useful to parse the data
#' into a melted format where each row represents a single token.
#'
#' `melt_fwf()` parses each token of a fixed width file into a single row, but
#' it still requires that each field is in the same in every row of the
#' source file.
#'
#' @seealso [melt_table()] to melt fixed width files where each
#'   column is separated by whitespace, and [read_fwf()] for the conventional
#'   way to read rectangular data from fixed width files.
#' @inheritParams read_fwf
#' @param col_positions Column positions, as created by [fwf_empty()],
#'   [fwf_widths()] or [fwf_positions()]. To read in only selected fields,
#'   use [fwf_positions()]. If the width of the last column is variable (a
#'   ragged fwf file), supply the last end position as NA.
#' @export
#' @examples
#' fwf_sample <- readr_example("fwf-sample.txt")
#' cat(read_lines(fwf_sample))
#'
#' # You can specify column positions in several ways:
#' # 1. Guess based on position of empty columns
#' melt_fwf(fwf_sample, fwf_empty(fwf_sample, col_names = c("first", "last", "state", "ssn")))
#' # 2. A vector of field widths
#' melt_fwf(fwf_sample, fwf_widths(c(20, 10, 12), c("name", "state", "ssn")))
#' # 3. Paired vectors of start and end positions
#' melt_fwf(fwf_sample, fwf_positions(c(1, 30), c(10, 42), c("name", "ssn")))
#' # 4. Named arguments with start and end positions
#' melt_fwf(fwf_sample, fwf_cols(name = c(1, 10), ssn = c(30, 42)))
#' # 5. Named arguments with column widths
#' melt_fwf(fwf_sample, fwf_cols(name = 20, state = 10, ssn = 12))
melt_fwf <- function(file, col_positions,
                     locale = default_locale(), na = c("", "NA"),
                     comment = "", trim_ws = TRUE, skip = 0, n_max = Inf,
                     progress = show_progress(),
                     skip_empty_rows = FALSE) {
  ds <- datasource(file, skip = skip)
  if (inherits(ds, "source_file") && empty_file(file)) {
       return(tibble::data_frame(row = double(), col = double(),
                                 data_type = character(), value = character()))
  }
  tokenizer <- tokenizer_fwf(col_positions$begin, col_positions$end, na = na,
                             comment = comment, trim_ws = trim_ws,
                             skip_empty_rows = skip_empty_rows)
  out <- melt_tokens(ds, tokenizer, locale_ = locale,
                     n_max = if (n_max == Inf) -1 else n_max, progress = progress)
  warn_problems(out)
}

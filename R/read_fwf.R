#' Read a fixed width file.
#'
#' A fixed width file can be a very compact representation of numeric data.
#' It's also very fast to parse, because every field is in the same place in
#' every line. Unfortunately, it's painful to parse because you need to
#' describe the length of every field. Readr aims to make it as easy as possible
#' by providing a number of different ways to describe the field structure.
#'
#' @seealso \code{\link{read_table}} to read fixed width files where each
#'   column is separated by whitespace.
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams read_delim
#' @param col_positions Column positions, as created by \code{fwf_empty},
#'   \code{fwf_widths} or \code{fwf_positions}. To read in only selected fields,
#'   use \code{fwf_positions}. The width of the last column will be silently
#'   extended to the next line break.
#' @export
#' @examples
#' fwf_sample <- system.file("extdata/fwf-sample.txt", package = "readr")
#' cat(read_lines(fwf_sample))
#'
#' # You can specify column positions in three ways:
#' # 1. Guess based on position of empty columns
#' read_fwf(fwf_sample, fwf_empty(fwf_sample))
#' # 2. A vector of field widths
#' read_fwf(fwf_sample, fwf_widths(c(2, 5, 3)))
#' # 3. Paired vectors of start and end positions
#' read_fwf(fwf_sample, fwf_positions(c(1, 4), c(2, 10)))
read_fwf <- function(file, col_positions, col_types = NULL,
                     locale = default_locale(), na = c("", "NA"),
                     skip = 0, n_max = -1, progress = interactive()) {
  ds <- datasource(file, skip = skip)
  tokenizer <- tokenizer_fwf(col_positions$begin, col_positions$end, na = na)

  col_types <- col_spec_standardise(
    file, skip = skip, n_max = n_max,
    tokenizer = tokenizer, locale = locale,
    col_names = col_positions$col_names, col_types = col_types
  )

  out <- read_tokens(ds, tokenizer, col_types, names(col_types),
    locale_ = locale, n_max = n_max, progress = progress)

  out <- name_problems(out)
  warn_problems(out, source_name(file))
}

#' @rdname read_fwf
#' @export
fwf_empty <- function(file, skip = 0, col_names = NULL) {
  ds <- datasource(file, skip = skip)

  out <- whitespaceColumns(ds)

  if (is.null(col_names)) {
    col_names <- paste0("X", seq_along(out$begin))
  } else {
    stopifnot(length(out$begin) == length(col_names))
  }
  out$col_names <- col_names

  out
}

#' @rdname read_fwf
#' @export
#' @param widths Width of each field.
#' @param col_names Either NULL, or a character vector column names.
fwf_widths <- function(widths, col_names = NULL) {
  pos <- cumsum(c(1, widths))

  fwf_positions(pos[-length(pos)], pos[-1] - 1, col_names)
}

#' @rdname read_fwf
#' @export
#' @param start,end Starting and ending (inclusive) positions of each field.
fwf_positions <- function(start, end, col_names = NULL) {
  stopifnot(length(start) == length(end))

  if (is.null(col_names)) {
    col_names <- paste0("X", seq_along(start))
  } else {
    stopifnot(length(start) == length(col_names))
  }

  list(
    begin = start - 1,
    end = end, # -1 to change to 0 offset, +1 to be exclusive,
    col_names = col_names
  )
}


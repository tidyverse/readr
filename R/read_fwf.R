#' Read a fixed width file into a tibble
#'
#' A fixed width file can be a very compact representation of numeric data.
#' It's also very fast to parse, because every field is in the same place in
#' every line. Unfortunately, it's painful to parse because you need to
#' describe the length of every field. Readr aims to make it as easy as possible
#' by providing a number of different ways to describe the field structure.
#'
#' @seealso [read_table()] to read fixed width files where each
#'   column is separated by whitespace.
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams read_delim
#' @param col_positions Column positions, as created by [fwf_empty()],
#'   [fwf_widths()] or [fwf_positions()]. To read in only selected fields,
#'   use [fwf_positions()]. If the width of the last column is variable (a
#'   ragged fwf file), supply the last end position as NA.
#' @export
#' @examples
#' fwf_sample <- readr_example("fwf-sample.txt")
#' cat(read_lines(fwf_sample))
#'
#' # You can specify column positions in three ways:
#' # 1. Guess based on position of empty columns
#' read_fwf(fwf_sample, fwf_empty(fwf_sample, col_names = c("first", "last", "state", "ssn")))
#' # 2. A vector of field widths
#' read_fwf(fwf_sample, fwf_widths(c(20, 10, 12), c("name", "state", "ssn")))
#' # 3. Paired vectors of start and end positions
#' read_fwf(fwf_sample, fwf_positions(c(1, 30), c(10, 42), c("name", "ssn")))
read_fwf <- function(file, col_positions, col_types = NULL,
                     locale = default_locale(), na = c("", "NA"),
                     comment = "", skip = 0, n_max = Inf,
                     guess_max = min(n_max, 1000), progress = interactive()) {
  ds <- datasource(file, skip = skip)

  if (inherits(ds, "source_file") && empty_file(file)) {
    return(tibble::data_frame())
  }

  tokenizer <- tokenizer_fwf(col_positions$begin, col_positions$end, na = na, comment = comment)

  spec <- col_spec_standardise(
    file,
    skip = skip,
    n = guess_max,
    tokenizer = tokenizer,
    locale = locale,
    col_names = col_positions$col_names,
    col_types = col_types,
    drop_skipped_names = TRUE
  )

  if (is.null(col_types) && !inherits(ds, "source_string")) {
    show_cols_spec(spec)
  }

  out <- read_tokens(ds, tokenizer, spec$cols, names(spec$cols),
    locale_ = locale, n_max = if (n_max == Inf) -1 else n_max, progress = progress)

  out <- name_problems(out)
  attr(out, "spec") <- spec
  warn_problems(out, source_name(file))
}

#' @rdname read_fwf
#' @export
#' @param n Number of lines the tokenizer will read to determine file structure. By default
#'      it is set to 100.
fwf_empty <- function(file, skip = 0, col_names = NULL, comment = "", n = 100L) {
  ds <- datasource(file, skip = skip)

  out <- whitespaceColumns(ds, comment = comment, n = n)
  out$end[length(out$end)] <- NA

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
#' @param widths Width of each field. Use NA as width of last field when
#'    reading a ragged fwf file.
#' @param col_names Either NULL, or a character vector column names.
fwf_widths <- function(widths, col_names = NULL) {
  pos <- cumsum(c(1, abs(widths)))

  fwf_positions(pos[-length(pos)], pos[-1] - 1, col_names)
}

#' @rdname read_fwf
#' @export
#' @param start,end Starting and ending (inclusive) positions of each field.
#'    Use NA as last end field when reading a ragged fwf file.
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

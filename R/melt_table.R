#' Return melted data for each token in a whitespace-separated file
#'
#' @description
#' `r lifecycle::badge("superseded")`
#' This function has been superseded in readr and moved to [the meltr
#' package](https://r-lib.github.io/meltr/).
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
#' fwf <- readr_example("fwf-sample.txt")
#' writeLines(read_lines(fwf))
#' melt_table(fwf)
#'
#' ws <- readr_example("whitespace-sample.txt")
#' writeLines(read_lines(ws))
#' melt_table2(ws)
melt_table <- function(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  comment = "",
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_table()",
      details = "Please use `meltr::melt_table()` instead"
    )
  }
  ds <- datasource(file, skip = skip, skip_empty_rows = skip_empty_rows)
  if (inherits(ds, "source_file") && empty_file(file)) {
    return(tibble::tibble(
      row = double(),
      col = double(),
      data_type = character(),
      value = character()
    ))
  }

  local_edition(1)
  columns <- fwf_empty(
    ds,
    skip = skip,
    skip_empty_rows = skip_empty_rows,
    n = guess_max,
    comment = comment
  )
  tokenizer <- tokenizer_fwf(
    columns$begin,
    columns$end,
    na = na,
    comment = comment,
    skip_empty_rows = skip_empty_rows
  )

  ds <- datasource(file = ds, skip = skip, skip_empty_rows = skip_empty_rows)
  out <- melt_tokens(
    ds,
    tokenizer,
    locale_ = locale,
    n_max = n_max,
    progress = progress
  )
  warn_problems(out)
}

#' @rdname melt_table
#' @export
melt_table2 <- function(
  file,
  locale = default_locale(),
  na = "NA",
  skip = 0,
  n_max = Inf,
  progress = show_progress(),
  comment = "",
  skip_empty_rows = FALSE
) {
  if (!edition_first()) {
    lifecycle::deprecate_soft(
      "2.0.0",
      what = "melt_table2()",
      details = "Please use `meltr::melt_table2()` instead"
    )
  }

  ds <- datasource(file, skip = skip, skip_empty_rows = skip_empty_rows)
  if (inherits(ds, "source_file") && empty_file(file)) {
    return(tibble::tibble(
      row = double(),
      col = double(),
      data_type = character(),
      value = character()
    ))
  }
  tokenizer <- tokenizer_ws(
    na = na,
    comment = comment,
    skip_empty_rows = skip_empty_rows
  )

  ds <- datasource(file = ds, skip = skip, skip_empty_rows = skip_empty_rows)
  melt_delimited(
    ds,
    tokenizer,
    locale = locale,
    skip = skip,
    comment = comment,
    n_max = n_max,
    progress = progress
  )
}

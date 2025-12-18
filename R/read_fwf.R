#' Read a fixed-width file into a tibble
#'
#' @description
#' Fixed-width files store tabular data with each field occupying a specific
#' range of character positions in every line. Once the fields are identified,
#' converting them to the appropriate R types works just like for delimited
#' files. The unique challenge with fixed-width files is describing where each
#' field begins and ends. \pkg{readr} tries to ease this pain by offering a
#' few different ways to specify the field structure:
#' - `fwf_empty()` - Guesses based on the positions of empty columns. This is
#'   the default. (Note that `fwf_empty()` returns 0-based positions, for
#'   internal use.)
#' - `fwf_widths()` - Supply the widths of the columns.
#' - `fwf_positions()` - Supply paired vectors of start and end positions. These
#'   are interpreted as 1-based positions, so are off-by-one compared to the
#'   output of `fwf_empty()`.
#' - `fwf_cols()` - Supply named arguments of paired start and end positions or
#'    column widths.
#'
#' Note: `fwf_empty()` cannot work with a connection or with any of the input
#' types that involve a connection internally, which includes remote and
#' compressed files. The reason is that this would necessitate reading from the
#' connection twice. In these cases, you'll have to either provide the field
#' structure explicitly with another `fwf_*()` function or download (and
#' decompress, if relevant) the file first.
#'
#' @details
#' Here's a enhanced example using the contents of the file accessed via
#' `readr_example("fwf-sample.txt")`.
#'
#' ```
#'          1         2         3         4
#' 123456789012345678901234567890123456789012
#' [     name 20      ][state 10][  ssn 12  ]
#' John Smith          WA        418-Y11-4111
#' Mary Hartford       CA        319-Z19-4341
#' Evan Nolan          IL        219-532-c301
#' ```
#'
#' Here are some valid field specifications for the above (they aren't all
#' equivalent! but they are all valid):
#'
#' ```
#' fwf_widths(c(20, 10, 12), c("name", "state", "ssn"))
#' fwf_positions(c(1, 30), c(20, 42), c("name", "ssn"))
#' fwf_cols(state = c(21, 30), last = c(6, 20), first = c(1, 4), ssn = c(31, 42))
#' fwf_cols(name = c(1, 20), ssn = c(30, 42))
#' fwf_cols(name = 20, state = 10, ssn = 12)
#' ```
#'
#' @seealso [read_table()] to read fixed width files where each
#'   column is separated by whitespace.
#'
#' @section Second edition changes:
#' Comments are now only ignored if they appear at the start of a line.
#' Comments elsewhere in a line are no longer treated specially.
#'
#' @inheritParams datasource
#' @inheritParams tokenizer_fwf
#' @inheritParams read_delim
#' @param col_positions Column positions, as created by [fwf_empty()],
#'   `fwf_widths()`, `fwf_positions()`, or `fwf_cols()`. To read in only
#'   selected fields, use `fwf_positions()`. If the width of the last column
#'   is variable (a ragged fwf file), supply the last end position as `NA`.
#' @export
#' @examples
#' fwf_sample <- readr_example("fwf-sample.txt")
#' writeLines(read_lines(fwf_sample))
#'
#' # You can specify column positions in several ways:
#' # 1. Guess based on position of empty columns
#' read_fwf(fwf_sample, fwf_empty(fwf_sample, col_names = c("first", "last", "state", "ssn")))
#' # 2. A vector of field widths
#' read_fwf(fwf_sample, fwf_widths(c(20, 10, 12), c("name", "state", "ssn")))
#' # 3. Paired vectors of start and end positions
#' read_fwf(fwf_sample, fwf_positions(c(1, 30), c(20, 42), c("name", "ssn")))
#' # 4. Named arguments with start and end positions
#' read_fwf(fwf_sample, fwf_cols(name = c(1, 20), ssn = c(30, 42)))
#' # 5. Named arguments with column widths
#' read_fwf(fwf_sample, fwf_cols(name = 20, state = 10, ssn = 12))
read_fwf <- function(
  file,
  col_positions = fwf_empty(file, skip, n = guess_max),
  col_types = NULL,
  col_select = NULL,
  id = NULL,
  locale = default_locale(),
  na = c("", "NA"),
  comment = "",
  trim_ws = TRUE,
  skip = 0,
  n_max = Inf,
  guess_max = min(n_max, 1000),
  progress = show_progress(),
  name_repair = "unique",
  num_threads = readr_threads(),
  show_col_types = should_show_types(),
  lazy = should_read_lazy(),
  skip_empty_rows = TRUE
) {
  if (edition_first()) {
    ds <- datasource(file, skip = skip, skip_empty_rows = skip_empty_rows)
    if (inherits(ds, "source_file") && empty_file(file)) {
      return(tibble::tibble())
    }

    tokenizer <- tokenizer_fwf(
      col_positions$begin,
      col_positions$end,
      na = na,
      comment = comment,
      trim_ws = trim_ws,
      skip_empty_rows = skip_empty_rows
    )

    spec <- col_spec_standardise(
      file,
      skip = skip,
      guess_max = guess_max,
      tokenizer = tokenizer,
      locale = locale,
      col_names = col_positions$col_names,
      col_types = col_types,
      drop_skipped_names = TRUE
    )

    if (is.null(col_types) && !inherits(ds, "source_string") && !is_testing()) {
      show_cols_spec(spec)
    }

    out <- read_tokens(
      datasource(file, skip = spec$skip, skip_empty_rows = skip_empty_rows),
      tokenizer,
      spec$cols,
      names(spec$cols),
      locale_ = locale,
      n_max = if (n_max == Inf) -1 else n_max,
      progress = progress
    )

    out <- name_problems(out, names(spec$cols), source_name(file))
    attr(out, "spec") <- spec
    return(warn_problems(out))
  }

  vroom::vroom_fwf(
    file,
    col_positions = col_positions,
    col_types = col_types,
    col_select = {{ col_select }},
    id = id,
    .name_repair = name_repair,
    locale = locale,
    na = na,
    comment = comment,
    skip_empty_rows = skip_empty_rows,
    trim_ws = trim_ws,
    skip = skip,
    n_max = n_max,
    guess_max = guess_max,
    show_col_types = show_col_types,
    progress = progress,
    altrep = lazy,
    num_threads = num_threads
  )
}

#' @rdname read_fwf
#' @export
#' @param n Number of lines the tokenizer will read to determine file structure. By default
#'      it is set to 100.
fwf_empty <- function(
  file,
  skip = 0,
  skip_empty_rows = deprecated(),
  col_names = NULL,
  comment = "",
  n = 100L
) {
  if (edition_first()) {
    skip_empty_rows <- if (is_present(skip_empty_rows)) {
      skip_empty_rows
    } else {
      FALSE
    }
    ds <- datasource(
      file,
      skip = skip,
      skip_empty_rows = skip_empty_rows
    )

    out <- whitespaceColumns(ds, comment = comment, n = n)
    out$end[length(out$end)] <- NA

    col_names <- fwf_col_names(col_names, length(out$begin))
    out$col_names <- col_names
    return(out)
  }

  if (!missing(skip_empty_rows)) {
    lifecycle::deprecate_stop(
      when = "2.0.0",
      what = "readr::fwf_empty(skip_empty_rows = )",
      details = c(
        "i" = "This argument is not supported in readr edition 2.",
        "i" = "Use `with_edition(1, ...)` or `local_edition(1)` to use the legacy edition 1."
      )
    )
  }

  vroom::fwf_empty(
    file = file,
    skip = skip,
    col_names = col_names,
    comment = comment,
    n = n
  )
}

#' @rdname read_fwf
#' @export
#' @param widths Width of each field. Use `NA` as the width of the last field
#'   when reading a ragged fixed-width file.
#' @param col_names Either NULL, or a character vector column names.
fwf_widths <- function(widths, col_names = NULL) {
  if (edition_first()) {
    pos <- cumsum(c(1L, abs(widths)))
    return(fwf_positions(pos[-length(pos)], pos[-1] - 1L, col_names))
  }
  vroom::fwf_widths(widths = widths, col_names = col_names)
}

#' @rdname read_fwf
#' @export
#' @param start,end Starting and ending (inclusive) positions of each field.
#'    **Positions are 1-based**: the first character in a line is at position 1.
#'    Use `NA` as the last value of `end` when reading a ragged fixed-width
#'    file.
fwf_positions <- function(start, end = NULL, col_names = NULL) {
  if (edition_first()) {
    stopifnot(length(start) == length(end))
    col_names <- fwf_col_names(col_names, length(start))

    return(tibble(
      begin = start - 1L,
      end = end, # -1 to change to 0 offset, +1 to be exclusive,
      col_names = as.character(col_names)
    ))
  }
  vroom::fwf_positions(start = start, end = end, col_names = col_names)
}


#' @rdname read_fwf
#' @export
#' @param ... If the first element is a data frame,
#'   then it must have all numeric columns and either one or two rows.
#'   The column names are the variable names. The column values are the
#'   variable widths if a length one vector, and if length two, variable start and end
#'   positions. The elements of `...` are used to construct a data frame
#'   with or or two rows as above.
fwf_cols <- function(...) {
  if (edition_first()) {
    x <- lapply(list(...), as.integer)
    names(x) <- fwf_col_names(names(x), length(x))
    x <- tibble::as_tibble(x)
    if (nrow(x) == 2) {
      res <- fwf_positions(as.integer(x[1, ]), as.integer(x[2, ]), names(x))
    } else if (nrow(x) == 1) {
      res <- fwf_widths(as.integer(x[1, ]), names(x))
    } else {
      stop(
        "All variables must have either one (width) two (start, end) values.",
        call. = FALSE
      )
    }
    return(res)
  }
  vroom::fwf_cols(...)
}

fwf_col_names <- function(nm, n) {
  nm <- nm %||% rep("", n)
  nm_empty <- (nm == "")
  nm[nm_empty] <- paste0("X", seq_len(n))[nm_empty]
  nm
}

#' @useDynLib readr, .registration = TRUE
NULL

#' Read a delimited file (including csv & tsv) into a tibble
#'
#' `read_csv()` and `read_tsv()` are special cases of the general
#' `read_delim()`. They're useful for reading the most common types of
#' flat file data, comma separated values and tab separated values,
#' respectively. `read_csv2()` uses `;` for the field separator and `,` for the
#' decimal point. This is common in some European countries.
#' @inheritParams datasource
#' @inheritParams tokenizer_delim
#' @param col_names Either `TRUE`, `FALSE` or a character vector
#'   of column names.
#'
#'   If `TRUE`, the first row of the input will be used as the column
#'   names, and will not be included in the data frame. If `FALSE`, column
#'   names will be generated automatically: X1, X2, X3 etc.
#'
#'   If `col_names` is a character vector, the values will be used as the
#'   names of the columns, and the first row of the input will be read into
#'   the first row of the output data frame.
#'
#'   Missing (`NA`) column names will generate a warning, and be filled
#'   in with dummy names `X1`, `X2` etc. Duplicate column names
#'   will generate a warning and be made unique with a numeric suffix.
#' @param col_types One of `NULL`, a [cols()] specification, or
#'   a string. See `vignette("readr")` for more details.
#'
#'   If `NULL`, all column types will be imputed from the first 1000 rows
#'   on the input. This is convenient (and fast), but not robust. If the
#'   imputation fails, you'll need to supply the correct types yourself.
#'
#'   If a column specification created by [cols()], it must contain
#'   one column specification for each column. If you only want to read a
#'   subset of the columns, use [cols_only()].
#'
#'   Alternatively, you can use a compact string representation where each
#'   character represents one column:
#' - c = character
#' - i = integer
#' - n = number
#' - d = double
#' - l = logical
#' - f = factor
#' - D = date
#' - T = date time
#' - t = time
#' - ? = guess
#' - _ or - = skip
#'
#'    By default, reading a file without a column specification will print a
#'    message showing what `readr` guessed they were. To remove this message,
#'    use `col_types = cols()`.
#' @param locale The locale controls defaults that vary from place to place.
#'   The default locale is US-centric (like R), but you can use
#'   [locale()] to create your own locale that controls things like
#'   the default time zone, encoding, decimal mark, big mark, and day/month
#'   names.
#' @param n_max Maximum number of records to read.
#' @param guess_max Maximum number of records to use for guessing column types.
#' @param progress Display a progress bar? By default it will only display
#'   in an interactive session and not while knitting a document. The display
#'   is updated every 50,000 values and will only display if estimated reading
#'   time is 5 seconds or more. The automatic progress bar can be disabled by
#'   setting option `readr.show_progress` to `FALSE`.
#' @return A [tibble()]. If there are parsing problems, a warning tells you
#'   how many, and you can retrieve the details with [problems()].
#' @export
#' @examples
#' # Input sources -------------------------------------------------------------
#' # Read from a path
#' read_csv(readr_example("mtcars.csv"))
#' read_csv(readr_example("mtcars.csv.zip"))
#' read_csv(readr_example("mtcars.csv.bz2"))
#'
#' \dontrun{
#' # Including remote paths
#' read_csv("https://github.com/tidyverse/readr/raw/master/inst/extdata/mtcars.csv")
#' }
#'
#' # Or directly from a string (must contain a newline)
#' read_csv("x,y\n1,2\n3,4")
#'
#' # Column types --------------------------------------------------------------
#' # By default, readr guesses the columns types, looking at the first 1000 rows.
#' # You can override with a compact specification:
#' read_csv("x,y\n1,2\n3,4", col_types = "dc")
#'
#' # Or with a list of column types:
#' read_csv("x,y\n1,2\n3,4", col_types = list(col_double(), col_character()))
#'
#' # If there are parsing problems, you get a warning, and can extract
#' # more details with problems()
#' y <- read_csv("x\n1\n2\nb", col_types = list(col_double()))
#' y
#' problems(y)
#'
#' # File types ----------------------------------------------------------------
#' read_csv("a,b\n1.0,2.0")
#' read_csv2("a;b\n1,0;2,0")
#' read_tsv("a\tb\n1.0\t2.0")
#' read_delim("a|b\n1.0|2.0", delim = "|")
read_delim <- function(file, delim, quote = '"',
                       escape_backslash = FALSE, escape_double = TRUE,
                       col_names = TRUE, col_types = NULL,
                       locale = default_locale(),
                       na = c("", "NA"), quoted_na = TRUE,
                       comment = "", trim_ws = FALSE,
                       skip = 0, n_max = Inf, guess_max = min(1000, n_max),
                       progress = show_progress(),
                       skip_empty_rows = TRUE) {

  if (!nzchar(delim)) {
    stop("`delim` must be at least one character, ",
      "use `read_table()` for whitespace delimited input.", call. = FALSE)
  }
  tokenizer <- tokenizer_delim(delim, quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na, quoted_na = quoted_na, comment = comment, trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, skip_empty_rows = skip_empty_rows,
    comment = comment, n_max = n_max, guess_max = guess_max, progress = progress)
}

#' @rdname read_delim
#' @export
read_csv <- function(file, col_names = TRUE, col_types = NULL,
                     locale = default_locale(), na = c("", "NA"),
                     quoted_na = TRUE, quote = "\"", comment = "", trim_ws = TRUE,
                     skip = 0, n_max = Inf, guess_max = min(1000, n_max),
                     progress = show_progress(), skip_empty_rows = TRUE) {
  if (edition_first()) {
  tokenizer <- tokenizer_csv(na = na, quoted_na = quoted_na, quote = quote,
    comment = comment, trim_ws = trim_ws, skip_empty_rows = skip_empty_rows)
  return(
    read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
      locale = locale, skip = skip, skip_empty_rows = skip_empty_rows,
      comment = comment, n_max = n_max, guess_max = guess_max, progress = progress
    )
  )
  }

  if (!missing(quoted_na)) {
    lifecycle::deprecate_soft("2.0.0", "read_csv(quoted_na = )")
  }
  vroom::vroom(file, delim = ",", col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, na = na, quote = quote, comment = comment, trim_ws = trim_ws,
    escape_double = TRUE, escape_backslash = FALSE, locale = locale, guess_max = guess_max,
    progress = progress)
}

#' @rdname read_delim
#' @export
read_csv2 <- function(file, col_names = TRUE, col_types = NULL,
                      locale = default_locale(),
                      na = c("", "NA"), quoted_na = TRUE, quote = "\"",
                      comment = "", trim_ws = TRUE, skip = 0, n_max = Inf,
                      guess_max = min(1000, n_max), progress = show_progress(),
                      skip_empty_rows = TRUE) {

  if (locale$decimal_mark == ".") {
    cli::cli_alert_info("Using {.val ','} as decimal and {.val '.'} as grouping mark. Use {.fn read_delim} for more control.")
    locale$decimal_mark <- ","
    locale$grouping_mark <- "."
  }
  tokenizer <- tokenizer_delim(delim = ";", na = na, quoted_na = quoted_na,
    quote = quote, comment = comment, trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, skip_empty_rows = skip_empty_rows,
    comment = comment, n_max = n_max, guess_max = guess_max, progress = progress)
}


#' @rdname read_delim
#' @export
read_tsv <- function(file, col_names = TRUE, col_types = NULL,
                     locale = default_locale(),
                     na = c("", "NA"), quoted_na = TRUE, quote = "\"",
                     comment = "", trim_ws = TRUE, skip = 0, n_max = Inf,
                     guess_max = min(1000, n_max), progress = show_progress(),
                     skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_tsv(na = na, quoted_na = quoted_na, quote = quote,
    comment = comment, trim_ws = trim_ws, skip_empty_rows = skip_empty_rows)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, skip_empty_rows = skip_empty_rows,
    comment = comment, n_max = n_max, guess_max = guess_max, progress = progress)
}

# Helper functions for reading from delimited files ----------------------------
read_tokens <- function(data, tokenizer, col_specs, col_names, locale_, n_max, progress) {
  if (n_max == Inf) {
    n_max <- -1
  }
  read_tokens_(data, tokenizer, col_specs, col_names, locale_, n_max, progress)
}

read_delimited <- function(file, tokenizer, col_names = TRUE, col_types = NULL,
                           locale = default_locale(), skip = 0, skip_empty_rows = TRUE, comment = "",
                           n_max = Inf, guess_max = min(1000, n_max), progress = show_progress()) {
  name <- source_name(file)
  # If connection needed, read once.
  file <- standardise_path(file)
  if (is.connection(file)) {
    data <- datasource_connection(file, skip, skip_empty_rows, comment)
    if (empty_file(data[[1]])) {
       return(tibble::tibble())
    }
  } else {
    if (!isTRUE(grepl("\n", file)[[1]]) && empty_file(file)) {
       return(tibble::tibble())
    }
    if (is.character(file) && identical(locale$encoding, "UTF-8")) {
      # When locale is not set, file is probably marked as its correct encoding.
      # As default_locale() assumes file is UTF-8, file should be encoded as UTF-8 for non-UTF-8 MBCS locales.
      data <- enc2utf8(file)
    } else {
      data <- file
    }
  }

  spec <- col_spec_standardise(
    data, skip = skip, skip_empty_rows = skip_empty_rows,
    comment = comment, guess_max = guess_max, col_names = col_names,
    col_types = col_types, tokenizer = tokenizer, locale = locale)

  ds <- datasource(data, skip = spec$skip, skip_empty_rows = skip_empty_rows, comment = comment)

  if (is.null(col_types) && !inherits(ds, "source_string") && !is_testing()) {
    show_cols_spec(spec)
  }

  out <- read_tokens(ds, tokenizer, spec$cols, names(spec$cols), locale_ = locale,
    n_max = n_max, progress = progress)

  out <- name_problems(out, names(spec$cols), name)
  attr(out, "spec") <- spec
  warn_problems(out)
}

generate_spec_fun <- function(x) {
  formals(x)$n_max <- 0
  formals(x)$guess_max <- 1000

  args <- formals(x)

  body(x) <-
    call("attr",
      as.call(c(substitute(x), stats::setNames(lapply(names(args), as.symbol), names(args)))),
      "spec")

  formals(x) <- args

  x
}

#' Generate a column specification
#'
#' When printed, only the first 20 columns are printed by default. To override,
#' set `options(readr.num_columns)` can be used to modify this (a value of 0
#' turns off printing).
#'
#' @return The `col_spec` generated for the file.
#' @inheritParams read_delim
#' @export
#' @examples
#' # Input sources -------------------------------------------------------------
#' # Retrieve specs from a path
#' spec_csv(system.file("extdata/mtcars.csv", package = "readr"))
#' spec_csv(system.file("extdata/mtcars.csv.zip", package = "readr"))
#'
#' # Or directly from a string (must contain a newline)
#' spec_csv("x,y\n1,2\n3,4")
#'
#' # Column types --------------------------------------------------------------
#' # By default, readr guesses the columns types, looking at the first 1000 rows.
#' # You can specify the number of rows used with guess_max.
#' spec_csv(system.file("extdata/mtcars.csv", package = "readr"), guess_max = 20)
spec_delim <- generate_spec_fun(read_delim)

#' @rdname spec_delim
#' @export
spec_csv <- generate_spec_fun(read_csv)

#' @rdname spec_delim
#' @export
spec_csv2 <- generate_spec_fun(read_csv2)

#' @rdname spec_delim
#' @export
spec_tsv <- generate_spec_fun(read_tsv)

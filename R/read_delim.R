#' @useDynLib readr
#' @importClassesFrom Rcpp "C++Object"
NULL

#' Read a delimited file into a data frame.
#'
#' \code{read_csv} and \code{read_tsv} are special cases of the general
#' \code{read_delim}. They're useful for reading the most common types of
#' flat file data, comma separated values and tab separated values,
#' respectively. \code{read_csv2} uses \code{;} for separators, instead of
#' \code{,}. This is common in European countries which use \code{,} as the
#' decimal separator.
#'
#' @inheritParams datasource
#' @inheritParams tokenizer_delim
#' @param col_names Either \code{TRUE}, \code{FALSE} or a character vector
#'   of column names.
#'
#'   If \code{TRUE}, the first row of the input will be used as the column
#'   names, and will not be included in the data frame. If \code{FALSE}, column
#'   names will be generated automatically: X1, X2, X3 etc.
#'
#'   If \code{col_names} is a character vector, the values will be used as the
#'   names of the columns, and the first row of the input will be read into
#'   the first row of the output data frame.
#' @param col_types One of \code{NULL}, a \code{\link{cols}}, specification of
#'   a string. See \code{vignette("column-types")} for more details.
#'
#'   If \code{NULL}, all column types will be imputed from the first 1000 rows
#'   on the input. This is convenient (and fast), but not robust. If the
#'   imputation fails, you'll need to supply the correct types yourself.
#'
#'   If a column specification created by \code{\link{cols}}, it must contain
#'   one "\code{\link{collector}}" for each column. If you only want to read a
#'   subset of the columns, use \code{\link{cols_only}}.
#'
#'   Alternatively, you can use a compact string representation where each
#'   character represents one column:
#'   c = character, i = integer, n = number, d = double,
#'   l = logical, D = date, T = date time, t = time, ? = guess, or
#'   \code{_}/\code{-} to skip the column.
#' @param locale The locale controls defaults that vary from place to place.
#'   The default locale is US-centric (like R), but you can use
#'   \code{\link{locale}} to create your own locale that controls things like
#'   the default time zone, encoding, decimal mark, big mark, and day/month
#'   names.
#' @param n_max Maximum number of records to read.
#' @param progress Display a progress bar? By default it will only display
#'   in an interactive session. The display is updated every 50,000 values
#'   and will only display if estimated reading time is 5 seconds or more.
#' @return A data frame. If there are parsing problems, a warning tells you
#'   how many, and you can retrieve the details with \code{\link{problems}()}.
#' @export
#' @examples
#' # Input sources -------------------------------------------------------------
#' # Read from a path
#' read_csv(system.file("extdata/mtcars.csv", package = "readr"))
#' read_csv(system.file("extdata/mtcars.csv.zip", package = "readr"))
#' read_csv(system.file("extdata/mtcars.csv.bz2", package = "readr"))
#' read_csv("https://github.com/hadley/readr/raw/master/inst/extdata/mtcars.csv")
#'
#' # Or directly from a string (must contain a newline)
#' read_csv("x,y\n1,2\n3,4")
#'
#' # Column types --------------------------------------------------------------
#' # By default, readr guess the columns types, looking at the first 100 rows.
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
                       na = c("", "NA"), comment = "",
                       skip = 0, n_max = -1, progress = interactive()) {
  tokenizer <- tokenizer_delim(delim, quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na, comment = comment)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, comment = comment, n_max = n_max,
    progress = progress)
}

#' @rdname read_delim
#' @export
read_csv <- function(file, col_names = TRUE, col_types = NULL,
                     locale = default_locale(), na = c("", "NA"), comment = "",
                     trim_ws = TRUE, skip = 0, n_max = -1,
                     progress = interactive()) {

  tokenizer <- tokenizer_csv(na = na, comment = comment, trim_ws = trim_ws)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, comment = comment, n_max = n_max,
    progress = progress)
}

#' @rdname read_delim
#' @export
read_csv2 <- function(file, col_names = TRUE, col_types = NULL,
                      locale = default_locale(),
                      na = c("", "NA"), comment = "",
                      trim_ws = TRUE, skip = 0, n_max = -1,
                      progress = interactive()) {

  if (locale$decimal_mark == ".") {
    locale$decimal_mark <- ","
    locale$grouping_mark <- "."
  }

  tokenizer <- tokenizer_delim(delim = ";", na = na, comment = comment,
    trim_ws = trim_ws)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, comment = comment, n_max = n_max,
    progress = progress)
}


#' @rdname read_delim
#' @export
read_tsv <- function(file, col_names = TRUE, col_types = NULL,
                     locale = default_locale(),
                     na = c("", "NA"), comment = "",
                     trim_ws = TRUE, skip = 0, n_max = -1,
                     progress = interactive()) {

  tokenizer <- tokenizer_tsv(na = na, comment = comment, trim_ws = trim_ws)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    locale = locale, skip = skip, comment = comment, n_max = n_max,
    progress = progress)
}

# Helper functions for reading from delimited files ----------------------------
read_delimited <- function(file, tokenizer, col_names = TRUE, col_types = NULL,
                           locale = default_locale(), skip = 0, comment = "",
                           n_max = -1, progress = interactive()) {
  name <- source_name(file)
  # If connection needed, read once.
  file <- standardise_path(file)
  if (is.connection(file)) {
    data <- read_connection(file)
  } else {
    data <- file
  }

  col_types <- col_spec_standardise(
    data, skip = skip, comment = comment, n_max = n_max,
    col_names = col_names, col_types = col_types,
    tokenizer = tokenizer, locale = locale)

  ds <- datasource(data, skip = skip + isTRUE(col_names), comment = comment)

  out <- read_tokens(ds, tokenizer, col_types, names(col_types), locale_ = locale,
    n_max = n_max, progress = progress)

  out <- name_problems(out)
  warn_problems(out, name)
}

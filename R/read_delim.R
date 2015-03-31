#' @useDynLib readr
#' @importClassesFrom Rcpp "C++Object"
NULL

#' Read a delimited file into a data frame.
#'
#' \code{read_csv} and \code{read_tsv} are special cases of the general
#' \code{read_delim}. They're useful for reading the most common types of
#' flat file data. \code{read_csv2} uses \code{;} for separators, instead of
#' \code{,}. This is common in European countries which use \code{,} as the
#' decimal separator.
#'
#' @inheritParams datasource
#' @inheritParams tokenizer_delim
#' @inheritParams col_names_standardise
#' @inheritParams col_types_standardise
#' @param n_max Maximum number of records to read.
#' @param progress Display a progress bar? By default it will only display
#'   in an interactive session. The display is updated every 50,000 values
#'   and will on display if estimated reading time is 5 seconds or more.
#' @usage read_delim(file, delim, quote = '\"', escape_backslash = TRUE,
#'   escape_double = TRUE, na = "NA", col_names = TRUE, col_types = NULL,
#'   skip = 0, n_max = -1, progress = interactive())
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
#' # File types ----------------------------------------------------------------
#' read_csv("a,b\n1.0,2.0")
#' read_csv2("a;b\n1,0;2,0")
#' read_tsv("a\tb\n1.0\t2.0")
#' read_delim("a|b\n1.0|2.0", delim = "|")
read_delim <- function(file, delim, quote = '"', escape_backslash = TRUE,
                       escape_double = TRUE, na = "NA", col_names = TRUE,
                       col_types = NULL, skip = 0, n_max = -1,
                       progress = interactive()) {
  tokenizer <- tokenizer_delim(delim, quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, progress = progress)
}

#' @rdname read_delim
#' @export
read_csv <- function(file, col_names = TRUE, col_types = NULL, na = "NA",
                     skip = 0, n_max = -1, progress = interactive()) {

  tokenizer <- tokenizer_csv(na = na)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, progress = progress)
}

#' @rdname read_delim
#' @export
read_csv2 <- function(file, col_names = TRUE, col_types = NULL, na = "NA",
                      skip = 0, n_max = -1, progress = interactive()) {

  tokenizer <- tokenizer_delim(delim = ";", na = na)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, progress = progress)
}


#' @rdname read_delim
#' @export
read_tsv <- function(file, col_names = TRUE, col_types = NULL, na = "NA",
                     skip = 0, n_max = -1, progress = interactive()) {

  tokenizer <- tokenizer_tsv(na = na)
  read_delimited(file, tokenizer, col_names = col_names, col_types = col_types,
    skip = skip, n_max = n_max, progress = progress)
}

# Helper functions for reading from delimited files ----------------------------
read_delimited <- function(file, tokenizer, col_names = TRUE, col_types = NULL,
                           skip = 0, n_max = -1, progress = interactive()) {
  # If connection needed, read once.
  file <- standardise_path(file)
  if (is.connection(file)) {
    file <- read_connection(file)
  }

  ds <- datasource(file, skip = skip)

  if (isTRUE(col_names))
    skip <- skip + 1
  col_names <- col_names_standardise(col_names, header(ds, tokenizer))

  ds <- datasource(file, skip = skip)
  col_types <- col_types_standardise(col_types, col_names, types(ds, tokenizer))
  read_tokens(ds, tokenizer, col_types, col_names, n_max = n_max,
    progress = progress)

}

# The header is the first row, parsed into fields
header <- function(datasource, tokenizer) {
  first <- read_lines_(datasource, n_max = 1)
  parse_vector(first, tokenizer = tokenizer, col_character())
}

types <- function(source, tokenizer) {
  collectorsGuess(source, tokenizer, n = 100)
}

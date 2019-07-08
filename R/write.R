#' Write a data frame to a delimited file
#'
#' This is about twice as fast as [write.csv()], and never
#' writes row names. `output_column()` is a generic method used to coerce
#' columns to suitable output.
#'
#' @section Output:
#' Factors are coerced to character. Doubles are formatted using the grisu3
#' algorithm. POSIXct's are formatted as ISO8601 with a UTC timezone *Note:
#' `POSIXct` objects in local or non-UTC timezones will be converted to UTC time
#' before writing.*
#'
#' All columns are encoded as UTF-8. `write_excel_csv()` and `write_excel_csv2()` also include a
#' \href{https://en.wikipedia.org/wiki/Byte_order_mark}{UTF-8 Byte order mark}
#' which indicates to Excel the csv is UTF-8 encoded.
#'
#' `write_excel_csv2()` and `write_csv2` were created to allow users with
#' different locale settings save csv files with their default settings `;` as
#' column separator and `,` as decimal separator. This is common in some European countries.
#'
#' Values are only quoted if needed: if they contain a comma, quote or newline.
#'
#' The `write_*()` functions will automatically compress outputs if an appropriate extension is given. At present, three
#' extensions are supported, `.gz` for gzip compression, `.bz2` for bzip2 compression and `.xz` for lzma compression.  See
#' the examples for more information.
#'
#' @param x A data frame to write to disk
#' @param path Path or connection to write to.
#' @param append If `FALSE`, will overwrite existing file. If `TRUE`,
#'   will append to existing file. In both cases, if file does not exist a new
#'   file is created.
#' @param col_names Write columns names at the top of the file? Must be either
#'   `TRUE` or `FALSE`.
#' @param delim Delimiter used to separate values. Defaults to `" "` for `write_delim()`, `","` for `write_excel_csv()` and
#' `";"` for `write_excel_csv2()`. Must be a single character.
#' @param na String used for missing values. Defaults to NA. Missing values
#'   will never be quoted; strings with the same value as `na` will
#'   always be quoted.
#' @param quote_escape The type of escaping to use for quoted values, one of
#'   "double", "backslash" or "none". You can also use `FALSE`, which is
#'   equivalent to "none". The default is to double the quotes, which is the
#'   format excel expects.
#' @return `write_*()` returns the input `x` invisibly.
#' @references Florian Loitsch, Printing Floating-Point Numbers Quickly and
#' Accurately with Integers, PLDI '10,
#' <http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf>
#' @export
#' @examples
#' \dontshow{.old_wd <- setwd(tempdir())}
#' # If you only specify a file name, write_()* will write
#' # the file to your current working directory.
#' write_csv(mtcars, "mtcars.csv")
#' write_tsv(mtcars, "mtcars.tsv")
#'
#' # If you add an extension to the file name, write_()* will
#' # automatically compress the output.
#' write_tsv(mtcars, "mtcars.tsv.gz")
#' write_tsv(mtcars, "mtcars.tsv.bz2")
#' write_tsv(mtcars, "mtcars.tsv.xz")
#'
#' \dontshow{setwd(.old_wd)}
write_delim <- function(x, path, delim = " ", na = "NA", append = FALSE,
                        col_names = !append, quote_escape = "double") {
  stopifnot(is.data.frame(x))

  x[] <- lapply(names(x), function(i) output_column(x[[i]], i))
  stream_delim(x, path, delim = delim, col_names = col_names, append = append,
    na = na, quote_escape = quote_escape)

  invisible(x)
}

#' @rdname write_delim
#' @export
write_csv <- function(x, path, na = "NA", append = FALSE, col_names = !append,
                      quote_escape = "double") {
  write_delim(x, path, delim = ",", na = na, append = append,
    col_names = col_names, quote_escape = quote_escape)
}

#' @rdname write_delim
#' @export
write_csv2 <- function(x, path, na = "NA", append = FALSE, col_names = !append,
                       quote_escape = "double") {
  x <- change_decimal_separator(x, decimal_mark = ",")
  write_delim(x, path, delim = ";", na = na, append = append,
    col_names = col_names, quote_escape = quote_escape)
}

#' @rdname write_delim
#' @export
write_excel_csv <- function(x, path, na = "NA", append = FALSE,
                            col_names = !append, delim = ",", quote_escape = "double") {

  stopifnot(is.data.frame(x))

  datetime_cols <- vapply(x, inherits, logical(1), "POSIXt")
  x[datetime_cols] <- lapply(x[datetime_cols], format, "%Y/%m/%d %H:%M:%S")

  x[] <- lapply(x, output_column)
  stream_delim(x, path, delim, col_names = col_names, append = append,
    na = na, bom = TRUE, quote_escape = quote_escape)

  invisible(x)
}

#' @rdname write_delim
#' @export
write_excel_csv2 <- function(x, path, na = "NA", append = FALSE,
                             col_names = !append, delim = ";", quote_escape = "double") {
  x <- change_decimal_separator(x, decimal_mark = ",")

  datetime_cols <- vapply(x, inherits, logical(1), "POSIXt")
  x[datetime_cols] <- lapply(x[datetime_cols], format, "%Y/%m/%d %H:%M:%S")

  x[] <- lapply(x, output_column)
  write_excel_csv(x, path, na, append, col_names, delim, quote_escape = quote_escape)
}

#' @rdname write_delim
#' @export
write_tsv <- function(x, path, na = "NA", append = FALSE, col_names = !append, quote_escape = "double") {
  write_delim(x, path, delim = '\t', na = na, append = append, col_names = col_names, quote_escape = quote_escape)
}

#' Convert a data frame to a delimited string
#'
#' These functions are equivalent to [write_csv()] etc., but instead
#' of writing to disk, they return a string.
#'
#' @return A string.
#' @inheritSection write_delim Output
#' @inheritParams write_delim
#' @inherit write_delim references
#' @examples
#' # format_()* functions are useful for testing and reprexes
#' cat(format_csv(head(mtcars)))
#' cat(format_tsv(head(mtcars)))
#' cat(format_delim(head(mtcars), ";"))
#'
#' df <- data.frame(x = c(1, 2, NA))
#' format_csv(df, na = ".")
#'
#' # Quotes are automatically added as needed
#' df <- data.frame(x = c("a ", '"', ",", "\n"))
#' cat(format_csv(df))
#' @export
format_delim <- function(x, delim, na = "NA", append = FALSE,
                         col_names = !append, quote_escape = "double") {
  stopifnot(is.data.frame(x))

  x[] <- lapply(x, output_column)
  res <- stream_delim(df = x, path = NULL, delim = delim, col_names = col_names, append = append, na = na, quote_escape = quote_escape)
  Encoding(res) <- "UTF-8"
  res
}

#' @export
#' @rdname format_delim
format_csv <- function(x, na = "NA", append = FALSE, col_names = !append, quote_escape = "double") {
  format_delim(x, delim = ",", na = na, append = append, col_names = col_names, quote_escape = quote_escape)
}

#' @export
#' @rdname format_delim
format_csv2 <- function(x, na = "NA", append = FALSE, col_names = !append, quote_escape = "double") {
  x <- change_decimal_separator(x, decimal_mark = ",")
  format_delim(x, delim = ";", na = na, append = append, col_names = col_names, quote_escape = quote_escape)
}

#' @export
#' @rdname format_delim
format_tsv <- function(x, na = "NA", append = FALSE, col_names = !append, quote_escape = "double") {
  format_delim(x, delim = "\t", na = na, append = append, col_names = col_names, quote_escape = quote_escape)
}

#' Preprocess column for output
#'
#' This is a generic function that applied to each column before it is saved
#' to disk. It provides a hook for S3 classes that need special handling.
#'
#' @keywords internal
#' @param x A vector
#' @export
#' @examples
#' # Most columns are left as is, but POSIXct are
#' # converted to ISO8601.
#' x <- parse_datetime("2016-01-01")
#' str(output_column(x))
output_column <- function(x, name) {
  UseMethod("output_column")
}

#' @export
output_column.default <- function(x, name) {
  if (!is.object(x)) return(x)
  as.character(x)
}

#' @export
output_column.double <- function(x, name) {
  x
}

#' @export
output_column.POSIXt <- function(x, name) {
  format(x, "%Y-%m-%dT%H:%M:%OSZ", tz = "UTC", justify = "none")
}

#' @export
output_column.list <- function(x, name) {
  stop("Flat files can't store the list column `", name, "`", call. = FALSE)
}

stream_delim <- function(df, path, append = FALSE, bom = FALSE, ..., quote_escape) {
  quote_escape <- standardise_escape(quote_escape)

  path <- standardise_path(path, input = FALSE)

  if (inherits(path, "connection") && !isOpen(path)) {
    on.exit(close(path), add = TRUE)
    if (isTRUE(append)) {
      open(path, "ab")
    } else {
      open(path, "wb")
    }
  }
  stream_delim_(df, path, ..., bom = bom, quote_escape = quote_escape)
}

change_decimal_separator <- function(x, decimal_mark = ",") {
  stopifnot(is.data.frame(x))
  numeric_cols <- vapply(x, is.numeric, logical(1))

  format_seps <- function(x, decimal_mark) {
    nas <- is.na(x)
    x <- format(x, decimal.mark = decimal_mark)
    x[nas] <- NA_character_
    x
  }

  x[numeric_cols] <- lapply(x[numeric_cols], format_seps, decimal_mark)

  x
}

standardise_escape <- function(x) {
  if (identical(x, FALSE)) {
    x <- "none"
  }

  escape_types <- c("double" = 1L, "backslash" = 2L, "none" = 3L)
  escape <- match.arg(tolower(x), names(escape_types))

  escape_types[escape]
}

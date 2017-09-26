#' Write a data frame to a delimited file
#'
#' This is about twice as fast as [write.csv()], and never
#' writes row names. `output_column()` is a generic method used to coerce
#' columns to suitable output.
#'
#' @section Output:
#' Factors are coerced to character. Doubles are formatted using the grisu3
#' algorithm. POSIXct's are formatted as ISO8601.
#'
#' All columns are encoded as UTF-8. `write_excel_csv()` and `write_excel_csv2()` also include a
#' \href{https://en.wikipedia.org/wiki/Byte_order_mark}{UTF-8 Byte order mark}
#' which indicates to Excel the csv is UTF-8 encoded.
#'
#' Values are only quoted if needed: if they contain a comma, quote or newline.
#'
#' @param x A data frame to write to disk
#' @param path Path or connection to write to.
#' @param append If `FALSE`, will overwrite existing file. If `TRUE`,
#'   will append to existing file. In both cases, if file does not exist a new
#'   file is created.
#' @param col_names Write columns names at the top of the file?
#' @param delim Delimiter used to separate values. Defaults to `" "`. `write_excel_csv()` has `","` as default and
#' `write_excel_csv2` has `";"` as default. Must be a single character.
#' @param na String used for missing values. Defaults to NA. Missing values
#'   will never be quoted; strings with the same value as `na` will
#'   always be quoted.
#' @return `write_*()` returns the input `x` invisibly.
#' @references Florian Loitsch, Printing Floating-Point Numbers Quickly and
#' Accurately with Integers, PLDI '10,
#' \url{http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf}
#' @export
#' @examples
#' tmp <- tempfile()
#' write_csv(mtcars, tmp)
#' head(read_csv(tmp))
#'
#' # format_* is useful for testing and reprexes
#' cat(format_csv(head(mtcars)))
#' cat(format_tsv(head(mtcars)))
#' cat(format_delim(head(mtcars), ";"))
#'
#' df <- data.frame(x = c(1, 2, NA))
#' format_csv(df, na = ".")
#'
#' # Quotes are automatically as needed
#' df <- data.frame(x = c("a", '"', ",", "\n"))
#' cat(format_csv(df))
#'
#' # A output connection will be automatically created for output filenames
#' # with appropriate extensions.
#' dir <- tempdir()
#' write_tsv(mtcars, file.path(dir, "mtcars.tsv.gz"))
#' write_tsv(mtcars, file.path(dir, "mtcars.tsv.bz2"))
#' write_tsv(mtcars, file.path(dir, "mtcars.tsv.xz"))
write_delim <- function(x, path, delim = " ", na = "NA", append = FALSE,
                        col_names = !append) {
  stopifnot(is.data.frame(x))

  x_out <- lapply(x, output_column)
  stream_delim(x_out, path, delim, col_names = col_names, append = append,
    na = na)

  invisible(x)
}

#' @rdname write_delim
#' @export
write_csv <- function(x, path, na = "NA", append = FALSE, col_names = !append) {
  write_delim(x, path, delim = ",", na = na,append = append, col_names = col_names)
}

#' @rdname write_delim
#' @export
write_excel_csv <- function(x, path, delim = ",", na = "NA", append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))

  x_formated <- if(delim == ";") {
    dplyr::mutate_if(x, is.numeric, dplyr::funs(format(., decimal.mark = ",")))
  } else {
    x
  }
  x_out <- lapply(x_formated, output_column)
  stream_delim(x_out, path, delim, col_names = col_names, append = append,
    na = na, bom = TRUE)

  invisible(x)
}

#' @rdname write_delim
#' @export
write_excel_csv2 <- function(x, path,  delim = ";", na = "NA", append = FALSE, col_names = !append) {
  write_excel_csv(x, path, delim, na, append, col_names)
}

#' @rdname write_delim
#' @export
write_tsv <- function(x, path, na = "NA", append = FALSE, col_names = !append) {
  write_delim(x, path, delim = '\t', na = na, append = append, col_names = col_names)
}

#' Convert a data frame to a delimited string
#'
#' These functions are equivalent to [write_csv()] etc., but instead
#' of writing to disk, they return a string.
#'
#' @return A string.
#' @inherit write_delim
#' @export
format_delim <- function(x, delim, na = "NA", append = FALSE, col_names = !append) {
  stopifnot(is.data.frame(x))

  x <- lapply(x, output_column)
  stream_delim(x, NULL, delim, col_names = col_names, append = append, na = na)
}

#' @export
#' @rdname format_delim
format_csv <- function(x, na = "NA", append = FALSE, col_names = !append) {
  format_delim(x, delim = ",", na = na, append = append, col_names = col_names)
}

#' @export
#' @rdname format_delim
format_tsv <- function(x, na = "NA", append = FALSE, col_names = !append) {
  format_delim(x, delim = "\t", na = na, append = append, col_names = col_names)
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
output_column <- function(x) {
  UseMethod("output_column")
}

#' @export
output_column.default <- function(x) {
  if (!is.object(x)) return(x)
  as.character(x)
}

#' @export
output_column.double <- function(x) {
  x
}

#' @export
output_column.POSIXt <- function(x) {
  format(x, "%Y-%m-%dT%H:%M:%OSZ", tz = "UTC")
}

stream_delim <- function(df, path, append = FALSE, ...) {
  path <- standardise_path(path, input = FALSE)

  if (inherits(path, "connection") && !isOpen(path)) {
    on.exit(close(path), add = TRUE)
    if (isTRUE(append)) {
      open(path, "ab")
    } else {
      open(path, "wb")
    }
  }
  stream_delim_(df, path, ...)
}

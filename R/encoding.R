#' Guess encoding of file.
#'
#' Uses \code{\link[stringi]{stri_enc_detect}}: see the documentation there
#' for caveats.
#'
#' @rdname encoding
#' @param file A character string specifying an input as specified in
#'   \code{\link{datasource}}, a raw vector, or a list of raw vectors.
#' @inheritParams datasource
#' @inheritParams read_lines
#' @param threshold Only report guesses above this threshold of certainty.
#' @return A tibble
#' @export
#' @examples
#' guess_encoding(readr_example("mtcars.csv"))
#' guess_encoding(read_lines_raw(readr_example("mtcars.csv")))
#' guess_encoding(read_file_raw(readr_example("mtcars.csv")))
#'
#' guess_encoding("a\n\u00b5\u00b5")
guess_encoding <- function(file, n_max = 1e4, threshold = 0.20) {
  if (!requireNamespace("stringi", quietly = TRUE)) {
    stop("stringi package required for encoding operations", call. = FALSE)
  }

  if (is.character(file)) {
    lines <- unlist(read_lines_raw(file, n_max = n_max))
  } else if (is.raw(file)) {
    lines <- file
  } else if (is.list(file)) {
    lines <- unlist(file)
  } else {
    stop("Unknown input to `file`", call. = FALSE)
  }

  if (stringi::stri_enc_isascii(lines)) {
    return(data.frame(encoding = "ASCII", confidence = 1))
  }

  guess <- stringi::stri_enc_detect(lines)

  df <- tibble::as_tibble(guess[[1]])
  names(df) <- tolower(names(df))
  df[df$confidence > threshold, c("encoding", "confidence")]
}

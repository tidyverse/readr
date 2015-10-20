#' Guess encoding of file.
#'
#' Uses \code{\link[stringi]{stri_enc_detect}}: see the documentation there
#' for caveats.
#'
#' @rdname encoding
#' @inheritParams datasource
#' @inheritParams read_lines
#' @param threshold Only report guesses above this threshold of certainty.
#' @export
#' @examples
#' guess_encoding(system.file("extdata/mtcars.csv", package = "readr"))
#' guess_encoding("a\n\u00b5\u00b5")
guess_encoding <- function(file, n_max = 1e4, threshold = 0.20) {
  if (!requireNamespace("stringi", quietly = TRUE)) {
    stop("stringi package required for encoding operations", call. = FALSE)
  }

  lines <- read_lines_raw(file, n_max = n_max)
  all <- unlist(lines)

  if (stringi::stri_enc_isascii(all)) {
    return(data.frame(encoding = "ASCII", confidence = 1))
  }

  guess <- stringi::stri_enc_detect(all)

  df <- as.data.frame(guess[[1]], stringsAsFactors = FALSE)
  names(df) <- tolower(names(df))
  df[df$confidence > threshold, c("encoding", "confidence"), drop = FALSE]
}

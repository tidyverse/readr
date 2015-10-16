#' Retrieve parsing problems.
#'
#' Readr functions will only throw an error if parsing fails in an unrecoverable
#' way. However, there are lots of potential problems that you might want to
#' know about - these are stored in the \code{problems} attribute of the
#' output, which you can easily access with this function.
#'
#' @param x An data frame (from \code{read_*}) or a vector
#'   (from \code{parse_*}).
#' @return A data frame with one row for each problem and four columns:
#'   \item{row,col}{Row and column of problem}
#'   \item{expected}{What readr expected to find}
#'   \item{actual}{What it actually got}
#' @export
#' @examples
#' x <- parse_integer(c("1X", "blah", "3"))
#' problems(x)
#'
#' y <- parse_integer(c("1", "2", "3"))
#' problems(y)
problems <- function(x) {
  probs <- probs(x)
  if (is.null(probs)) {
    structure(
      data.frame(
        row = integer(),
        col = integer(),
        expected = character(),
        actual = character(),
        stringsAsFactors = FALSE
      ),
      class = c("tbl_df", "data.frame")
    )
  } else {
    probs
  }
}

probs <- function(x) {
  attr(suppressWarnings(x), "problems")
}

n_problems <- function(x) {
  probs <- probs(x)
  if (is.null(probs)) 0 else nrow(probs)
}

problem_rows <- function(x) {
  if (n_problems(x) == 0)
    return(x[0, , drop = FALSE])

  probs <- problems(x)
  x[unique(probs$row), , drop = FALSE]
}

warn_problems <- function(x, name = "input") {
  n <- n_problems(x)
  if (n == 0)
    return(x)

  probs <- attr(x, "problems")
  many_problems <- nrow(probs) > 5

  probs_f <- format(utils::head(probs, 5), justify = "left")
  probs_f[probs_f == "NA"] <- "--"
  probs_f <- rbind(names(probs), probs_f)
  probs_f <- lapply(probs_f, format, justify = "right")

  if (many_problems) {
    width <- vapply(probs_f, function(x) max(nchar(x)), integer(1))
    dots <- vapply(width, function(i) paste(rep(".", i), collapse = ""),
      FUN.VALUE = character(1))

    probs_f <- Map(c, probs_f, dots)
  }

  probs_f <- do.call(paste, c(probs_f, list(sep = " ", collapse = "\n")))
  warning(n, " parsing failure", if (n > 1) "s", ".\n", probs_f,
    if (many_problems) "\n.See problems(...) for more details.",
    call. = FALSE, immediate. = TRUE, noBreaks. = TRUE)

  x
}

name_problems <- function(x) {
  if (n_problems(x) == 0)
    return(x)

  problems <- problems(x)
  problems$col <- names(x)[problems$col]
  attr(x, "problems") <- problems

  x
}

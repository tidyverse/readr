#' Retrieve parsing problems
#'
#' Readr functions will only throw an error if parsing fails in an unrecoverable
#' way. However, there are lots of potential problems that you might want to
#' know about - these are stored in the `problems` attribute of the
#' output, which you can easily access with this function.
#' `stop_for_problems()` will throw an error if there are any parsing
#' problems: this is useful for automated scripts where you want to throw
#' an error as soon as you encounter a problem.
#'
#' @param x An data frame (from `read_*()`) or a vector
#'   (from `parse_*()`).
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
problems <- local({
  no_problems <- tibble::tibble(
    row = integer(),
    col = integer(),
    expected = character(),
    actual = character()
  )

  function(x = .Last.value) {
    problems <- probs(x)

    if (is.null(problems)) {
      return(invisible(no_problems))
    }

    if (inherits(problems, "tbl_df")) {
      return(problems)
    }

    vroom::problems(x)
  }
})

#' @export
#' @rdname problems
stop_for_problems <- function(x) {
  n <- n_problems(x)
  if (n == 0) {
    return(invisible(x))
  }

  stop(n, " parsing failure", if (n > 1) "s", call. = FALSE)
}

probs <- function(x) {
  attr(suppressWarnings(x), "problems")
}

n_problems <- function(x) {
  probs <- problems(x)
  if (is.null(probs)) 0 else nrow(probs)
}

problem_rows <- function(x) {
  if (n_problems(x) == 0) {
    return(x[0, , drop = FALSE])
  }

  probs <- problems(x)
  x[unique(probs$row), , drop = FALSE]
}

warn_problems <- function(x) {
  n <- n_problems(x)
  if (n == 0) {
    return(x)
  }

  probs <- as.data.frame(attr(x, "problems"))
  many_problems <- nrow(probs) > 5

  probs_f <- format(utils::head(probs, 5), justify = "left")
  probs_f[probs_f == "NA"] <- "--"
  probs_f <- rbind(names(probs), probs_f)
  probs_f <- lapply(probs_f, format, justify = "right")

  if (many_problems) {
    # nchar fails with non-ascii characters, so encode characters beforehand.
    width <- vapply(probs_f, function(x) max(nchar(encodeString(x))), integer(1))
    dots <- vapply(width, function(i) paste(rep(".", i), collapse = ""),
      FUN.VALUE = character(1)
    )

    probs_f <- Map(c, probs_f, dots)
  }

  probs_f <- do.call(paste, c(probs_f, list(sep = " ", collapse = "\n")))
  warning(n, " parsing failure", if (n > 1) "s", ".\n",
    probs_f, "\n",
    if (many_problems) "See problems(...) for more details.\n",
    call. = FALSE, immediate. = TRUE, noBreaks. = TRUE
  )

  x
}

name_problems <- function(x, all_colnames, name = "input") {
  if (n_problems(x) == 0) {
    return(x)
  }

  problems <- problems(x)
  problems$file <- name
  problems$col <- all_colnames[problems$col]
  attr(x, "problems") <- problems

  x
}

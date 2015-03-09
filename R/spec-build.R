guess_delim <- function(file, n = 30, skip = 0, comment_char = "", quote = "\"",
                        backslash_escape = FALSE,
                        double_escape = FALSE) {

  # file <- check_file(file)
#   x <- count_char_from_file(file, n = n, skip = skip, quote_ = quote,
#     comment_ = comment_char, backslash_escape = backslash_escape,
#     double_escape = double_escape)

  names(x) <- rawToChar(as.raw(names(x)), multiple = TRUE)
  counts <- sort(x, decreasing = TRUE)

  lines <- counts[["\n"]]
  candidates <- counts[setdiff(names(counts), "\n")]

  per_line <- candidates / lines
  # Must be at least one delimiter per line
  per_line <- per_line[per_line > 1]
  # Integer number of delimiters per line is best
  is_int <- round(per_line) == per_line
  if (sum(is_int) == 0) {
    stop("Could not guess delimter")
  } else if (sum(is_int) == 1) {
    # Only one delim is used on every line
    delim <- names(per_line)[is_int]
    message("Guessing delimiter is ", delim, " (used ", per_line[is_int],
      " times per line).")
  } else {
    # Use candidate with highest frequency
    ok <- per_line[is_int]
    delim <- names(per_line)[which.max(ok)][1]
    message("Guessing delimiter is ", delim,
      " (", paste0(names(ok), " used ", ok, collapse = ","), ")")
  }

  delim
}

#' @export
format.time <- function(x, ...) {
  x <- as.integer(x)
  h <- x %/% 3600L
  m <- (x - h * 3600L) %/% 60L
  s <- x %% 60L

  hms <- paste0(
    format(h, align = "right"), ":",
    sprintf("%02d", m), ":",
    sprintf("%02d", s)
  )

  ifelse(is.na(x), "NA", hms)
}

#' @export
print.time <- function(x, ...) {
  print(format(x), quote = FALSE)
}

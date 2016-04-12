#' @export
format.time <- function(x, ...) {
  x_nosign <- as.integer(abs(x))
  h <- x_nosign %/% 3600L
  m <- (x_nosign - h * 3600L) %/% 60L
  s <- x_nosign %% 60L

  hms <- paste0(
    ifelse(sign(x) == -1, "-", ""),
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

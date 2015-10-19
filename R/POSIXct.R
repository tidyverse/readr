POSIXct <- function(x, tz = "UTC") {
  structure(x, class = c("POSIXct", "POSIXt"), tzone = tz)
}

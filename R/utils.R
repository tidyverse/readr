isFALSE <- function(x) identical(x, FALSE)

is.connection <- function(x) inherits(x, "connection")

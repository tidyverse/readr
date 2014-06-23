isFALSE <- function(x) identical(x, FALSE)

str_trim <- function(x) gsub("^\\s+|\\s+$", "", x)

pluck <- function(x, i) lapply(x, "[[", i)
vpluck <- function(x, i) vapply(x, "[[", i, FUN.VALUE = x[[1]][[i]])


check_file <- function(file) {
  if (inherits(file, "connection")) return(file)
  if (!is.character(file) || length(file) != 1) {
    stop("file must be a string.", call. = FALSE)
  }

  if (!file.exists(file)) {
    stop("'", file, "' does not exist", call. = FALSE)
  }

  normalizePath(file, "/")
}

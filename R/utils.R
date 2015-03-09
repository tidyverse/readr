isFALSE <- function(x) identical(x, FALSE)

str_trim <- function(x) gsub("^\\s+|\\s+$", "", x)

pluck <- function(x, i) lapply(x, "[[", i)
vpluck <- function(x, i) vapply(x, "[[", i, FUN.VALUE = x[[1]][[i]])


is_absolute_path <- function(path) {
  grepl("^(/|[A-Za-z]:|\\\\|~)", path)
}

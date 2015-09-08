#' Read multiple files from a file catalog
#'
#' A file catalog is a \code{data.frame} object (df) where each observation is a
#' specification of how to read in a particular file. The minimum variables are
#' \code{file}, \code{read_fun} and \code{dots}.
#'
#' @param catalog df. A file catalog.
#' @param bind boolean. Should \code{dplyr::bind_rows()} be called on output.
#'  Defaults to FALSE.
#' @examples
#'  # first we make a catalog
#'  files <- c(system.file("extdata/mtcars.csv", package = "readr"),
#'            system.file("extdata/mtcars.csv.zip", package = "readr"),
#'            system.file("extdata/mtcars.csv.bz2", package = "readr"))
#'  catalog <- dplyr::data_frame(file = files,
#'                              read_fun = "read_csv",
#'                              dots = list(list(skip = 1),
#'                                          list(n_max = 1),
#'                                         list(col_names = FALSE)))
#'  read_catalog(catalog)
#'  read_catalog(catalog, bind = TRUE)
#' @export
read_catalog <- function(catalog, bind = FALSE) {
  df <- catalog
  calls <- purrr::map3(df$file, df$read_fun, df$dots, compose_call)
  l <- purrr::map(calls, eval)
  if (bind) l <- dplyr::bind_rows(l)
  l
}

compose_call <- function(file, fun, dots) {
  dots <- c(list(file = file), dots)
  pryr::make_call(fun, .args = dots)
}

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
#'  \dontrun{
#'  # first we make a catalog
#'  files <- c(system.file("extdata/mtcars.csv", package = "readr"),
#'  system.file("extdata/mtcars.csv.zip", package = "readr"),
#'  system.file("extdata/mtcars.csv.bz2", package = "readr"))
#'  catalog <- dplyr::data_frame(file = files,
#'                               read_fun = readr::read_csv,
#'                               dots = c(list(skip = 1), list(n_max = 2), list()))
#'  read_catalog(catalog)
#'  }
#' @export
read_catalog <- function(catalog, bind = FALSE) {
  # fill in specified params for each fun and return the partialled fun
  funs <- purrr::map2(catalog$read_fun, catalog$dots, compose_function)
  # read each file in catalog with its speficied fun
  l <- purrr::map2(catalog$file, funs)
  # bind the output ?
  if (bind)
    l <- dplyr::bind_rows(l)
  l
}

compose_function <- function(fun, dots) {
  f <- match.fun(fun)
  purrr::partial(f, dots)
}

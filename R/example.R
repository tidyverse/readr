#' Get path to readr example
#'
#' readr comes bundled with a number of sample files in its `inst/extdata`
#' directory. This function make them easy to access
#'
#' @param path Name of file. If `NULL`, the example files will be listed.
#' @export
#' @examples
#' readr_example()
#' readr_example("challenge.csv")
readr_example <- function(path = NULL) {
  if (is.null(path)) {
    dir(system.file("extdata", package = "readr"))
  } else {
    system.file("extdata", path, package = "readr", mustWork = TRUE)
  }
}

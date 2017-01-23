#' Get path to readr example
#'
#' readr comes bundled with a number of sample files in its `inst/extdata`
#' directory. This function make them easy to access
#'
#' @param path Name of file
#' @export
#' @keywords internal
#' @examples
#' readr_example("challenge.csv")
readr_example <- function(path) {
  system.file("extdata", path, package = "readr", mustWork = TRUE)
}

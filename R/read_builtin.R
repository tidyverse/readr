#' Read built-in object from package
#'
#' Consistent wrapper around [data()] that forces the promise. This is also a
#' stronger parallel to loading data from a file.
#'
#' @param x Name (character string) of data set to read.
#' @param package Name of package from which to find data set. By default, all
#' attached packages are searched and then the 'data' subdirectory (if present)
#' of the current working directory.
#'
#' @return An object of the built-in class of `x`.
#' @export
#' @examples
#' if (requireNamespace("dplyr")) {
#'   read_builtin("starwars", "dplyr")
#'
#'   read_builtin("storms", "dplyr")
#'}
read_builtin <- function(x, package = NULL) {
  warn_to_error <- function(e) {
    stop(conditionMessage(e), call. = FALSE)
  }
  tryCatch(
    warning = function(e) warn_to_error(e),
    expr = {
      res <- data(list = list(x), package = package, envir = environment(), verbose = FALSE)
      get(res[[1]], envir = environment())
    }
  )
}

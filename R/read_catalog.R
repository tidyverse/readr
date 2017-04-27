#' Read multiple files from an input catalog
#'
#' An input catalog (inca for short?) is a table that catalogs the inputs of a
#' project. It is a `data.frame` object where each observation/record/row
#' represents an input: something to be inputed into R relevant to your project.
#'
#' Defining variables are: \code{in_name} a character string of the human-friendly
#' name of the input, \code{in_fun} a character string of the name of the
#' function to use to read the input, and \code{in_args} a named list of the
#' arguments to be used when reading the input.
#'
#' @param inca (df). A input catalog (inca).
#' @param bind (lgl). Should \code{dplyr::bind_rows()} be called on output?
#' @param .id (chr). Name of the id column to use if bind is set to TRUE.
#'  Defaults to FALSE.
#' @examples
#'  # see the vignette.
#' @export
read_catalog <- function(inca, bind = FALSE, .id = "id") {
  calls <- compose_calls(inca$in_name, inca$in_fun, inca$in_args)
  l <- purrr::map(calls, eval)
  if (bind) l <- dplyr::bind_rows(l, .id = .id)
  l
}

compose_calls <- function(name, f, args) {
  l <- purrr::map2(f, args, pryr::make_call)
  setNames(l, name)
}

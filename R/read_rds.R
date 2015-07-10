#' Read object from RDS file.
#'
#' This is a minimal wrapper around \code{\link{readRDS}} that uses the
#' same naming scheme as all other functions in \pkg{readR}.
#'
#' @param path Path of file
#' @export
#' @examples
#' temp <- tempfile()
#' write_rds(mtcars, temp)
#' read_rds(temp)
read_rds <- function(path) {
  readRDS(path)
}

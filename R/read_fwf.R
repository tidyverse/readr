
fwf_spec <- function(widths = NULL, start = NULL, end = NULL, column = NULL) {
  ok <- !is.null(widths) && is.null(start) && is.null(end) ||
    is.null(widths) && !is.null(start) && !is.null(end)
  if (!ok) {
    stop("Must supply either widths or both start and end", call. = FALSE)
  }
  if (is.null(start)) {
    pos <- cumsum(c(0, widths))
    start <- pos[1]
    end <- pos[-length(pos)] - 1
  }

  structure(
    list(
      start = start,
      end = end,
      column = column
    ),
    class = c("fwf_spec", "file_spec", "spec")
  )
}


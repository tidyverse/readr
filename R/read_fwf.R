read_fwf <- function(file, fields, col_types = NULL, na = "NA", skip = 0,
                     n_max = -1) {
  ds <- datasource(file, skip = skip)
  tokenizer <- tokenizer_fwf(fields$begin, fields$end, na = na)

  col_types <- col_types_standardise(col_types, col_names, types(ds, tokenizer))
  col_names <- paste0("X", seq_along(col_types))
  read_tokens(ds, tokenizer, col_types, col_names, n_max = n_max)
}

fwf_empty <- function(file) {
  ds <- datasource(file)
  whitespaceColumns(ds)
}

fwf_col <- function(widths = NULL, start = NULL, end = NULL) {
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

  list(
    begin = start - 1,
    end = end # -1 to change to 0 offset, +1 to be exclusive
  )
}


# Generates the chunked definition from the melt_* definition
generate_melt_chunked_fun <- function(x) { # nocov start
  args <- formals(x)

  # Remove n_max argument
  args <- args[names(args) != "n_max"]

  args <- append(args, alist(callback = , chunk_size = 10000), 1)

  b <- as.list(body(x))

  # Change melt_delimited to melt_delimited_chunked
  b[[length(b)]][[1]] <- quote(melt_delimited_chunked)

  call_args <- as.list(b[[length(b)]])

  # Remove the n_max argument
  call_args <- call_args[!names(call_args) == "n_max"]

  # add the callback and chunk_size arguments
  b[[length(b)]] <- as.call(append(call_args, alist(callback = callback, chunk_size = chunk_size), 2))

  body(x) <- as.call(b)

  formals(x) <- args

  x
} # nocov end

# Generates the modified melt_delimited function
generate_melt_delimited_chunked <- function(x) { # nocov start
  args <- formals(x)
  args <- args[names(args) != "n_max"]
  args <- append(args, alist(callback = , chunk_size = 10000), 1)

  b <- as.list(body(x))

  for (i in seq_along(b)) {
    if (is.call(b[[i]]) && identical(b[[i]][[1]], as.symbol("<-")) &&
      is.call(b[[i]][[3]]) && identical(b[[i]][[3]][[1]], quote(melt_tokens))) {

      # Change melt_tokens() to melt_tokens_chunked
      b[[i]][[3]][[1]] <- quote(melt_tokens_chunked)
      chunked_call <- as.list(b[[i]][[3]])

      # Remove the n_max argument
      chunked_call <- chunked_call[!names(chunked_call) == "n_max"]

      # Add the callback and chunk_size arguments
      b[[i]] <- as.call(append(chunked_call, alist(callback = callback, chunk_size = chunk_size), 2))

      # Remove additional calls
      b <- b[-seq(i + 1, length(b))]
      body(x) <- as.call(b)
      formals(x) <- args
      return(x)
    }
  }

  x
} # nocov end

melt_tokens_chunked <- function(data, callback, chunk_size, tokenizer, locale_, progress) {
  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  melt_tokens_chunked_(
    data, callback, chunk_size, tokenizer, col_spec_melt,
    locale_, progress
  )

  return(callback$result())
}

melt_delimited_chunked <- generate_melt_delimited_chunked(melt_delimited)

#' Melt a delimited file by chunks
#'
#' For certain non-rectangular data formats, it can be useful to parse the data
#' into a melted format where each row represents a single token.
#'
#' `melt_delim_chunked()` and the specialisations `melt_csv_chunked()`,
#' `melt_csv2_chunked()` and `melt_tsv_chunked()` read files by a chunk of rows
#' at a time, executing a given function on one chunk before reading the next.
#'
#' @inheritParams read_delim_chunked
#' @param callback A callback function to call on each chunk
#' @param chunk_size The number of rows to include in each chunk
#' @keywords internal
#' @family chunked
#' @export
#' @examples
#' # Cars with 3 gears
#' f <- function(x, pos) subset(x, data_type == "integer")
#' melt_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
melt_delim_chunked <- generate_melt_chunked_fun(melt_delim)

#' @rdname melt_delim_chunked
#' @export
melt_csv_chunked <- generate_melt_chunked_fun(melt_csv)

#' @rdname melt_delim_chunked
#' @export
melt_csv2_chunked <- generate_melt_chunked_fun(melt_csv2)

#' @rdname melt_delim_chunked
#' @export
melt_tsv_chunked <- generate_melt_chunked_fun(melt_tsv)

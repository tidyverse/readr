read_lines_chunked <- function(file, callback, chunk_size = 10000, skip = 0,
  locale = default_locale(), na = character(), progress = interactive()) {
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)

  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  read_lines_chunked_(ds, locale, na, chunk_size, callback, progress)

  return(callback$result())
}

# Generates the chunked definition from the read_* definition
generate_chunked_fun <- function(x) {
  args <- formals(x)

  # Remove n_max argument
  args <- args[names(args) != "n_max"]

  # Change guess_max default to use chunk_size
  args$guess_max[[3]] <- quote(chunk_size)

  args <- append(args, alist(callback =, chunk_size = 10000), 1)

  b <- as.list(body(x))

  # Change read_delimited to read_delimited_chunked
  b[[3]][[1]] <- quote(read_delimited_chunked)

  call_args <- as.list(b[[3]])

  # Remove the n_max argument
  call_args <- call_args[!names(call_args) == "n_max"]

  # add the callback and chunk_size arguments
  b[[3]] <- as.call(append(call_args, alist(callback = callback, chunk_size = chunk_size), 2))

  body(x) <- as.call(b)

  formals(x) <- args

  x
}

# Generates the modified read_delimited function
generate_read_delimited_chunked <- function(x) {
  args <- formals(x)
  args <- args[names(args) != "n_max"]
  args <- append(args, alist(callback =, chunk_size = 10000), 1)

  b <- as.list(body(x))

  for (i in seq_along(b)) {
    if (is.call(b[[i]]) && identical(b[[i]][[1]], as.symbol("<-")) &&
        is.call(b[[i]][[3]]) && identical(b[[i]][[3]][[1]], quote(read_tokens))) {

      # Change read_tokens() to read_tokens_chunked
      b[[i]][[3]][[1]] <- quote(read_tokens_chunked)
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
}

read_tokens_chunked <- function(data, callback, chunk_size, tokenizer, col_specs, col_names, locale_, progress) {
  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  read_tokens_chunked_(data, callback, chunk_size, tokenizer, col_specs, col_names, locale_, progress)

  return(callback$result())
}

read_delimited_chunked <- generate_read_delimited_chunked(read_delimited)

#' Read a delimited file by chunks
#'
#' @inheritParams read_delim
#' @param callback A callback function to call on each chunk
#' @param chunk_size The number of rows to include in each chunk
#' @include read_delim.R
#' @export
read_delim_chunked <- generate_chunked_fun(read_delim)

#' @rdname read_delim_chunked
#' @export
read_csv_chunked <- generate_chunked_fun(read_csv)

#' @rdname read_delim_chunked
#' @export
read_csv2_chunked <- generate_chunked_fun(read_csv2)

#' @rdname read_delim_chunked
#' @export
read_tsv_chunked <- generate_chunked_fun(read_tsv)

as_chunk_callback <- function(x) UseMethod("as_chunk_callback")
as_chunk_callback.function <- function(x) {
  SideEffectChunkCallback$new(x)
}
as_chunk_callback.R6ClassGenerator <- function(x) {
  as_chunk_callback(x$new())
}
as_chunk_callback.ChunkCallback <- function(x) {
  x
}

ChunkCallback <- R6::R6Class("ChunkCallback",
  private = list(
    callback = NULL
  ),
  public = list(
    initialize = function(callback) NULL,
    receive = function(data, index) NULL,
    continue = function() TRUE,
    result = function() NULL,
    finally = function() NULL
  )
)

# This would be used if the result should be thrown away
SideEffectChunkCallback <- R6::R6Class("SideEffectChunkCallback", inherit = ChunkCallback,
  private = list(
     cancel = FALSE
    ),
  public = list(
    initialize = function(callback) {
      check_callback_fun(callback)
      private$callback <- callback
    },
    receive = function(data, index) {
      result <- private$callback(data, index)
      private$cancel <- identical(result, FALSE)
    },
    continue = function() {
      !private$cancel
    }
  )
)

# Used if the result of each chunk should be combined
# at the end
DataFrameCallback <- R6::R6Class("DataFrameCallback", inherit = ChunkCallback,
  public = list(
    initialize = function(callback) {
      private$callback <- callback
    },
    receive = function(data, index) {
      result <- private$callback(data, index)
      private$results <- c(private$results, list(result))
    },
    result = function() {
      dplyr::bind_rows(private$results)
    }
  )
)

check_callback_fun <- function(callback) {
  n_args <- length(formals(callback))
  if (n_args < 2) {
    stop("`callback` must have two or more arguments", call. = FALSE)
  }
}

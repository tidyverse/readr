read_lines_chunked <- function(file, callback, skip = 0, n_max = -1L, chunk_size = 10000,
                       locale = default_locale(), na = character(), progress = interactive()) {
  if (empty_file(file)) {
    return(character())
  }
  ds <- datasource(file, skip = skip)

  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  read_lines_(ds, locale, na, callback, chunk_size, n_max, progress)

  return(callback$result())
}

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

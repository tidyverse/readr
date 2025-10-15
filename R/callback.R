as_chunk_callback <- function(x) UseMethod("as_chunk_callback")

#' @exportS3Method as_chunk_callback 'function'
as_chunk_callback.function <- function(x) {
  SideEffectChunkCallback$new(x)
}

#' @exportS3Method
as_chunk_callback.R6ClassGenerator <- function(x) {
  as_chunk_callback(x$new())
}

#' @exportS3Method
as_chunk_callback.ChunkCallback <- function(x) {
  x
}

#' Callback classes
#'
#' These classes are used to define callback behaviors.
#'
#' \describe{
#'  \item{ChunkCallback}{Callback interface definition, all callback functions should inherit from this class.}
#'  \item{SideEffectChunkCallback}{Callback function that is used only for side effects, no results are returned.}
#'  \item{DataFrameCallback}{Callback function that combines each result together at the end.}
#'  \item{AccumulateCallBack}{
#'    Callback function that accumulates a single result. Requires the parameter `acc` to specify
#'    the initial value of the accumulator.  The parameter `acc` is `NULL` by default.
#'  }
#' }
#' @usage NULL
#' @format NULL
#' @name callback
#' @keywords internal
#' @family chunked
#' @examples
#' ## If given a regular function it is converted to a SideEffectChunkCallback
#'
#' # view structure of each chunk
#' read_lines_chunked(readr_example("mtcars.csv"), str, chunk_size = 5)
#'
#' # Print starting line of each chunk
#' f <- function(x, pos) print(pos)
#' read_lines_chunked(readr_example("mtcars.csv"), SideEffectChunkCallback$new(f), chunk_size = 5)
#'
#' # If combined results are desired you can use the DataFrameCallback
#'
#' # Cars with 3 gears
#' f <- function(x, pos) subset(x, gear == 3)
#' read_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
#'
#' # The ListCallback can be used for more flexible output
#' f <- function(x, pos) x$mpg[x$hp > 100]
#' read_csv_chunked(readr_example("mtcars.csv"), ListCallback$new(f), chunk_size = 5)
#'
#' # The AccumulateCallback accumulates results from each chunk
#' f <- function(x, pos, acc) sum(x$mpg) + acc
#' read_csv_chunked(readr_example("mtcars.csv"), AccumulateCallback$new(f, acc = 0), chunk_size = 5)
#' @export
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

#' @usage NULL
#' @format NULL
#' @rdname callback
#' @export
SideEffectChunkCallback <- R6::R6Class("SideEffectChunkCallback",
  inherit = ChunkCallback,
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

#' @usage NULL
#' @format NULL
#' @rdname callback
#' @export
DataFrameCallback <- R6::R6Class("DataFrameCallback",
  inherit = ChunkCallback,
  private = list(
    results = list()
  ),
  public = list(
    initialize = function(callback) {
      private$callback <- callback
    },
    receive = function(data, index) {
      result <- private$callback(data, index)
      private$results <- c(private$results, list(result))
    },
    result = function() {
      do.call(`rbind`, private$results)
    },
    finally = function() {
      private$results <- list()
    }
  )
)

#' @usage NULL
#' @format NULL
#' @rdname callback
#' @export
ListCallback <- R6::R6Class("ListCallback",
  inherit = ChunkCallback,
  private = list(
    results = list()
  ),
  public = list(
    initialize = function(callback) {
      private$callback <- callback
    },
    receive = function(data, index) {
      result <- private$callback(data, index)
      private$results <- c(private$results, list(result))
    },
    result = function() {
      private$results
    },
    finally = function() {
      private$results <- list()
    }
  )
)

#' @usage NULL
#' @format NULL
#' @rdname callback
#' @export
AccumulateCallback <- R6::R6Class("AccumulateCallback",
  inherit = ChunkCallback,
  private = list(
    acc = NULL
  ),
  public = list(
    initialize = function(callback, acc = NULL) {
      check_callback_fun(callback,
        req_args = 3,
        message = "`callback` must have three or more arguments"
      )
      private$acc <- acc
      private$callback <- callback
    },
    receive = function(data, index) {
      private$acc <- private$callback(data, index, private$acc)
    },
    result = function() {
      private$acc
    }
  )
)

check_callback_fun <- function(callback, req_args = 2, message = NULL) {
  if (is.null(message)) {
    message <- "`callback` must have two or more arguments"
  }
  n_args <- length(formals(callback))
  if (n_args < req_args) {
    stop(message, call. = FALSE)
  }
}

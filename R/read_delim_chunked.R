# Generates the modified read_delimited function
generate_read_delimited_chunked <- function(x) {
  args <- formals(x)
  args <- args[names(args) != "n_max"]
  args <- append(args, alist(callback = , chunk_size =), 1)

  # Change guess_max default to use chunk_size
  args$guess_max[[3]] <- quote(chunk_size)

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
      b[[i]] <- as.call(append(chunked_call, alist(callback = callback, chunk_size = chunk_size, spec = spec), 2))

      # Remove additional calls
      b <- b[-seq(i + 1, length(b))]
      body(x) <- as.call(b)
      formals(x) <- args
      return(x)
    }
  }

  x
}

read_tokens_chunked <- function(data, callback, chunk_size, tokenizer, col_specs, col_names, locale_, spec, progress) {
  callback <- as_chunk_callback(callback)
  on.exit(callback$finally(), add = TRUE)

  read_tokens_chunked_(data, callback, chunk_size, tokenizer, col_specs, col_names, locale_, spec, progress)

  return(callback$result())
}

utils::globalVariables(c("callback", "chunk_size"))

read_delimited_chunked <- generate_read_delimited_chunked(read_delimited)

#' Read a delimited file by chunks
#'
#' @inheritParams read_delim
#' @param callback A callback function to call on each chunk
#' @param chunk_size The number of rows to include in each chunk
#' @keywords internal
#' @family chunked
#' @export
#' @details The number of lines in `file` can exceed the maximum integer value in R (~2 billion).
#' @examples
#' # Cars with 3 gears
#' f <- function(x, pos) subset(x, gear == 3)
#' read_csv_chunked(readr_example("mtcars.csv"), DataFrameCallback$new(f), chunk_size = 5)
read_delim_chunked <- function(file, callback, delim = NULL, chunk_size = 10000, quote = '"',
                               escape_backslash = FALSE, escape_double = TRUE,
                               col_names = TRUE, col_types = NULL,
                               locale = default_locale(),
                               na = c("", "NA"), quoted_na = TRUE,
                               comment = "", trim_ws = FALSE,
                               skip = 0, guess_max = chunk_size,
                               progress = show_progress(),
                               skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_delim(delim,
    quote = quote,
    escape_backslash = escape_backslash, escape_double = escape_double,
    na = na, quoted_na = quoted_na, comment = comment, trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  read_delimited_chunked(file,
    callback = callback, chunk_size = chunk_size, tokenizer = tokenizer,
    col_names = col_names, col_types = col_types, locale = locale, skip = skip,
    skip_empty_rows = skip_empty_rows, comment = comment, guess_max = guess_max,
    progress = progress
  )
}

#' @rdname read_delim_chunked
#' @export
read_csv_chunked <- function(file, callback, chunk_size = 10000, col_names = TRUE, col_types = NULL,
                             locale = default_locale(), na = c("", "NA"),
                             quoted_na = TRUE, quote = "\"", comment = "", trim_ws = TRUE,
                             skip = 0, guess_max = chunk_size,
                             progress = show_progress(), skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_csv(
    na = na, quoted_na = quoted_na, quote = quote,
    comment = comment, trim_ws = trim_ws, skip_empty_rows = skip_empty_rows
  )
  read_delimited_chunked(file,
    callback = callback, chunk_size = chunk_size,
    tokenizer = tokenizer, col_names = col_names, col_types = col_types, locale = locale,
    skip = skip, skip_empty_rows = skip_empty_rows, comment = comment,
    guess_max = guess_max, progress = progress
  )
}

#' @rdname read_delim_chunked
#' @export
read_csv2_chunked <- function(file, callback, chunk_size = 10000, col_names = TRUE, col_types = NULL,
                              locale = default_locale(), na = c("", "NA"),
                              quoted_na = TRUE, quote = "\"", comment = "", trim_ws = TRUE,
                              skip = 0, guess_max = chunk_size,
                              progress = show_progress(), skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_delim(
    delim = ";", na = na, quoted_na = quoted_na,
    quote = quote, comment = comment, trim_ws = trim_ws,
    skip_empty_rows = skip_empty_rows
  )
  read_delimited_chunked(file,
    callback = callback, chunk_size = chunk_size,
    tokenizer = tokenizer, col_names = col_names, col_types = col_types, locale = locale,
    skip = skip, skip_empty_rows = skip_empty_rows, comment = comment,
    guess_max = guess_max, progress = progress
  )
}

#' @rdname read_delim_chunked
#' @export
read_tsv_chunked <- function(file, callback, chunk_size = 10000, col_names = TRUE, col_types = NULL,
                             locale = default_locale(), na = c("", "NA"),
                             quoted_na = TRUE, quote = "\"", comment = "", trim_ws = TRUE,
                             skip = 0, guess_max = chunk_size,
                             progress = show_progress(), skip_empty_rows = TRUE) {
  tokenizer <- tokenizer_tsv(
    na = na, quoted_na = quoted_na, quote = quote,
    comment = comment, trim_ws = trim_ws, skip_empty_rows = skip_empty_rows
  )
  read_delimited_chunked(file,
    callback = callback, chunk_size = chunk_size,
    tokenizer = tokenizer, col_names = col_names, col_types = col_types, locale = locale,
    skip = skip, skip_empty_rows = skip_empty_rows, comment = comment,
    guess_max = guess_max, progress = progress
  )
}

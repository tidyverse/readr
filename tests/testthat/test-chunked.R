context("chunked")

test_that("read_lines_chunked", {
  file <- readr_example("mtcars.csv")
  num_rows <- length(readLines(file))

  get_sizes <- function(data, pos) sizes[[length(sizes) + 1]] <<- length(data)

  # Full file in one chunk
  sizes <- list()
  read_lines_chunked(file, get_sizes)
  expect_equal(num_rows, sizes[[1]])

  # Each line separately
  sizes <- list()
  read_lines_chunked(file, get_sizes, chunk_size = 1)
  expect_true(all(sizes == 1))
  expect_equal(num_rows, length(sizes))

  # In chunks of 5
  sizes <- list()
  read_lines_chunked(file, get_sizes, chunk_size = 5)
  expect_true(all(sizes[1:6] == 5))
  expect_true(all(sizes[[7]] == 3))
})

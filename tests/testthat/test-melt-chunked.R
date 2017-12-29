context("melt-chunked")

test_that("melt_delim_chunked", {
  file <- readr_example("mtcars.csv")
  unchunked <- melt_csv(file)

  get_dims <- function(data, pos) dims[[length(dims) + 1]] <<- dim(data)

  # Full file in one chunk
  dims <- list()
  melt_csv_chunked(file, get_dims)
  expect_equal(dim(unchunked), dims[[1]])

  # Each line separately
  dims <- list()
  melt_csv_chunked(file, get_dims, chunk_size = 1)
  expect_true(all(vapply(dims[1:6], identical, logical(1), c(11L, 4L))))
  expect_equal(nrow(unchunked) / 11L, length(dims))

  # In chunks of 5
  dims <- list()
  melt_csv_chunked(file, get_dims, chunk_size = 5)
  expect_true(all(vapply(dims[1:6], identical, logical(1), c(55L, 4L))))
  expect_true(identical(dims[[7]], c(33L, 4L)))

  # Halting early
  get_dims_stop <- function(data, pos) {
    dims[[length(dims) + 1]] <<- dim(data)
    if (pos >= 5) {
      return(FALSE)
    }
  }
  dims <- list()
  melt_csv_chunked(file, get_dims_stop, chunk_size = 5)
  expect_true(length(dims) == 2)
  expect_true(all(vapply(dims[1:2], identical, logical(1), c(55L, 4L))))
})

test_that("DataFrameCallback works as intended", {
  f <- readr_example("mtcars.csv")
  out0 <- subset(melt_csv(f), data_type == "integer")
  fun3 <- DataFrameCallback$new(function(x, pos)
                                subset(x, data_type == "integer"))

  out1 <- melt_csv_chunked(f, fun3)
  out2 <- melt_csv_chunked(f, fun3, chunk_size = 1)
  out3 <- melt_csv_chunked(f, fun3, chunk_size = 10)

  expect_true(all.equal(out0, out1))
  expect_true(all.equal(out0, out2))
  expect_true(all.equal(out0, out3))


  # No matching rows
  out0 <- subset(melt_csv(f), data_type == "integer")

  fun5 <- DataFrameCallback$new(function(x, pos) subset(x, data_type == "integer"))

  out1 <- melt_csv_chunked(f, fun5)

  # Need to set guess_max higher than 1 to guess correct column types
  out2 <- melt_csv_chunked(f, fun5, chunk_size = 1)

  out3 <- melt_csv_chunked(f, fun5, chunk_size = 10)

  expect_true(all.equal(out0, out1))
  expect_true(all.equal(out0, out2))
  expect_true(all.equal(out0, out3))
})

test_that("ListCallback works as intended", {
  f <- readr_example("mtcars.csv")
  out0 <- melt_csv(f)

  fun <- ListCallback$new(function(x, pos) x[["value"]])
  out1 <- melt_csv_chunked(f, fun, chunk_size = 10)

  expect_equal(out0[["value"]], unlist(out1))
})

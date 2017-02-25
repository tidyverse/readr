context("write_lines")
test_that("write_lines uses UTF-8 encoding", {
  tmp <- tempfile()
  on.exit(unlink(tmp))
  write_lines(c("fran\u00e7ais", "\u00e9l\u00e8ve"), tmp)
  x <- read_lines(tmp, locale = locale(encoding = "UTF-8"), progress = FALSE)
  expect_equal(x, c("fran\u00e7ais", "\u00e9l\u00e8ve"))
})

test_that("write_lines writes an empty file if given a empty character vector", {
  tmp <- tempfile()
  on.exit(unlink(tmp))
  write_lines(character(), tmp)
  expect_true(empty_file(tmp))
})

test_that("write_lines respects the NA argument", {
  tmp <- tempfile()
  tmp2 <- tempfile()
  on.exit(unlink(c(tmp, tmp2)))

  write_lines(c("first", NA_character_, "last"), tmp)
  expect_equal(read_lines(tmp), c("first", "NA", "last"))

  write_lines(c("first", NA_character_, "last"), tmp2, na = "test")
  expect_equal(read_lines(tmp2), c("first", "test", "last"))
})

test_that("write_lines can append to a file", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  write_lines(c("first", "last"), tmp)
  write_lines(c("first", "last"), tmp, append = TRUE)

  expect_equal(read_lines(tmp), c("first", "last", "first", "last"))
})

test_that("write_lines accepts a list of raws", {
  x <- lapply(seq_along(1:10), function(x) charToRaw(paste0(collapse = "", sample(letters, size = sample(0:22, 1)))))
  tmp <- tempfile()
  on.exit(unlink(tmp))

  write_lines(x, tmp)

  expect_equal(read_lines(tmp), vapply(x, rawToChar, character(1)))
})

# write_file ------------------------------------------------------------------
test_that("write_file round trips", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  x <- "foo\nbar"
  write_file(x, tmp)

  expect_equal(read_file(tmp), x)
})

test_that("write_file round trips with an empty vector", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  x <- ""
  write_file(x, tmp)

  expect_equal(read_file(tmp), x)
})

test_that("write_file errors if given a character vector of length != 1", {
  tmp <- tempfile()

  expect_error(write_file(character(), tmp))
  expect_error(write_file(c("foo", "bar"), tmp))
})

test_that("write_file with raw round trips", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  x <- charToRaw("foo\nbar")
  write_file(x, tmp)

  expect_equal(read_file_raw(tmp), x)
})

test_that("write_file with raw round trips with an empty vector", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  x <- raw()
  write_file(x, tmp)

  expect_equal(read_file_raw(tmp), x)
})

test_that("write_lines can write to compressed files", {

  mt <- read_lines(readr_example("mtcars.csv.bz2"))

  filename <- file.path(tempdir(), "mtcars.csv.bz2")
  on.exit(unlink(filename))
  write_lines(mt, filename)

  expect_true(is_bz2_file(filename))
  expect_equal(mt, read_lines(filename))
})

test_that("write_file can write to compressed files", {

  mt <- read_file(readr_example("mtcars.csv.bz2"))

  filename <- file.path(tempdir(), "mtcars.csv.bz2")
  on.exit(unlink(filename))
  write_file(mt, filename)

  expect_true(is_bz2_file(filename))
  expect_equal(mt, read_file(filename))
})

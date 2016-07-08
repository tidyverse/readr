context("write_lines")
test_that("write_lines uses UTF-8 encoding", {
  tmp <- tempfile()
  on.exit(unlink(tmp))
  write_lines(c("fran\u00e7ais", "\u00e9l\u00e8ve"), tmp)
  x <- read_lines(tmp, locale = locale(encoding = "UTF-8"), progress = FALSE)
  expect_equal(x, c("fran\u00e7ais", "\u00e9l\u00e8ve"))
})

test_that("write_lines writes and empty file if given a empty character vector", {
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

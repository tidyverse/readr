context("read_lines")

test_that("read_lines respects encoding", {
  x <- read_lines("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"), progress = FALSE)
  expect_equal(x, c("fran\u00e7ais", "\u00e9l\u00e8ve"))
})

test_that("read_lines returns an empty character vector on an empty file", {
  expect_equal(read_lines("empty-file", progress = FALSE), character())
})

test_that("read_lines handles embedded nuls", {
  expect_equal(read_lines("null-file", progress = FALSE), c("a,b,c", "1,2,", "3,4,5"))
})

test_that("read_lines uses na argument", {
  expect_equal(read_lines("sample_text.txt", na = "abc", progress = FALSE), c(NA_character_, "123"))
  expect_equal(read_lines("sample_text.txt", na = "123", progress = FALSE), c("abc", NA_character_))
  expect_equal(read_lines("sample_text.txt", na = c("abc", "123"), progress = FALSE), c(NA_character_, NA_character_))
})

test_that("blank lines are passed unchanged", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  x <- c("abc", "", "123")
  write_lines(path = tmp, x)
  expect_equal(read_lines(tmp), x)
  expect_equal(read_lines(tmp, na = ""), c("abc", NA_character_, "123"))
})

test_that("allocation works as expected", {
  tmp <- tempfile(fileext = ".gz")
  on.exit(unlink(tmp))

  x <- rep(paste(rep("a", 2 ^ 10), collapse = ''), 2 ^ 11)
  writeLines(x, tmp)
  expect_equal(length(read_lines(tmp)), 2^11)
})

# These tests are slow so are commented out
#test_that("long vectors are supported", {
  #tmp <- tempfile(fileext = ".gz")
  #on.exit(unlink(tmp))

  #x <- rep(paste(rep("a", 2 ^ 16), collapse = ''), 2 ^ 15)
  #con <- gzfile(tmp, open = "w", compression = 0)
  #writeLines(x, con)
  #close(con)

  #expect_equal(length(read_lines(tmp)), 2^15)

  #expect_equal(length(read_lines_raw(tmp)), 2^15)
#})

context("read_table")

# read_table -------------------------------------------------------------------

test_that("read_table silently reads ragged last column", {
  x <- read_table("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)
  expect_equal(x$foo, c(1, 3, 5))
})

test_that("read_table skips all comment lines", {
  x <- read_table("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)

  y <- read_table("#comment1\n#comment2\nfoo bar\n1   2\n3   4\n5   6\n", progress = FALSE, comment = "#")

  expect_equal(x, y)
})

test_that("read_table can read from a pipe (552)", {
  x <- read_table(pipe("echo a b c && echo 1 2 3 && echo 4 5 6"), progress = FALSE)
  expect_equal(x$a, c(1, 4))
})

# read_table2 -------------------------------------------------------------------

test_that("read_table2 silently reads ragged columns", {
  x <- read_table2("foo bar\n1 2\n3   4\n5     6\n", progress = FALSE)
  expect_equal(x$foo, c(1, 3, 5))
})

test_that("read_table2 skips all comment lines", {
  x <- read_table2("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)

  y <- read_table2("#comment1\n#comment2\nfoo bar\n1   2\n3   4\n5   6\n", progress = FALSE, comment = "#")

  expect_equal(x, y)
})

test_that("read_table2 can read from a pipe (552)", {
  x <- read_table2(pipe("echo a b c && echo 1 2 3 && echo 4 5 6"))
  expect_equal(x$a, c(1, 4))
})


test_that("Source skips comments in header", {
  x <- "SKIP\nCOMMENT\nSKIP\na b\n1 2"
  expected_result <- read_table("a b\n1 2", col_names = TRUE)
  result1 <- read_table(x, skip = 2, comment = "COMMENT", col_names = TRUE)
  expect_equal(expected_result, result1)
})

test_that("Source skips comments in header even if comment has a different encoding", {
  x <- "SKIP\nC\u00d6MMENT\nSKIP\na b\n1 2"
  Encoding(x) <- "UTF-8"
  comment <- "C\u00d6MMENT"
  Encoding(comment) <- "UTF-8"
  comment_latin1 <- iconv("C\u00d6MMENT", "UTF-8", "latin1")
  expected_result <- read_table("a b\n1 2", col_names = TRUE)
  result1 <- read_table(x, comment = comment, col_names = TRUE, skip = 2)
  result2 <- read_table(x, comment = comment_latin1, col_names = TRUE, skip = 2)
  expect_equal(expected_result, result1)
  expect_equal(result1, result2)
})

test_that("Source skips multiple comments in header", {
  x <- "KOMMENT\nCOMMENT\nSKIP\na b\n1 2"
  comment <- c("KOMMENT", "COMMENT")
  expected_result <- read_table("a b\n1 2", col_names = TRUE)
  result1 <- read_table(x, comment = comment, col_names = TRUE, skip = 1)
  expect_equal(result1, expected_result)
})

test_that("Encoding conversion for comments in header works", {
  x <- "C\u00d6MMENT\nK\u00d6MMENT\nSKIP\na b\n1 2"
  comment <- c(iconv("K\u00d6MMENT", "UTF-8", "latin1"), "C\u00d6MMENT")
  expected_result <- read_table("a b\n1 2", col_names = TRUE)
  result1 <- read_table(x, comment = comment, col_names = TRUE, skip = 1)
  expect_equal(result1, expected_result)
})



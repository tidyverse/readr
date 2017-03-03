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

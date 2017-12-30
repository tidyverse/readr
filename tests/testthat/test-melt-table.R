context("melt_table")

# melt_table -------------------------------------------------------------------

test_that("melt_table silently reads ragged last column", {
  x <- melt_table("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)
  expect_equal(x$value[-1:-2], as.character(1:6))
})

test_that("melt_table skips all comment lines", {
  x <- melt_table("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)

  y <- melt_table("#comment1\n#comment2\nfoo bar\n1   2\n3   4\n5   6\n", progress = FALSE, comment = "#")

  expect_equal(x, y)
})

test_that("missing lines are not skipped", {
   # first
  expect_equal(max(melt_table("a   b\n\n\n12 34")$row), 4)

   # middle
  expect_equal(max(melt_table("a   b\n12 34\n\n\n23 45")$row), 5)

  # last (trailing \n is ignored)
  expect_equal(max(melt_table("a   b\n12 34\n\n\n")$row), 4)
})

test_that("melt_table can read from a pipe", {
  x <- melt_table(pipe("echo a b c && echo 1 2 3 && echo 4 5 6"), progress = FALSE)
  expect_equal(x$value[-1:-3], as.character(1:6))
})

test_that("melt_table can read a truncated file without crashing", {
  expect_warning(expect_error(melt_table("table-crash"), NA))
})

test_that("melt_table returns an empty data.frame on an empty file", {
   empty_df <- tibble::data_frame(row = double(), col = double(),
                                  data_type = character(), value = character())
   expect_true(all.equal(melt_table("empty-file", progress = FALSE), empty_df))
})

# melt_table2 -------------------------------------------------------------------

test_that("melt_table2 silently reads ragged columns", {
  x <- melt_table2("foo bar\n1 2\n3   4\n5     6\n", progress = FALSE)
  expect_equal(x$value[-1:-2], as.character(1:6))
})

test_that("melt_table2 skips all comment lines", {
  x <- melt_table2("foo bar\n1   2\n3   4\n5   6\n", progress = FALSE)

  y <- melt_table2("#comment1\n#comment2\nfoo bar\n1   2\n3   4\n5   6\n", progress = FALSE, comment = "#")

  expect_equal(x, y)
})

test_that("melt_table2 can read from a pipe", {
  x <- melt_table2(pipe("echo a b c&& echo 1 2 3&& echo 4 5 6"), progress = FALSE)
  expect_equal(x$value[-1:-3], as.character(1:6))
})

test_that("melt_table2 does not duplicate header rows for leading whitespace", {
  x <- melt_table2("foo bar\n1   2\n")
  expect_equal(nrow(x), 4L)
  expect_equal(x$value[-1:-2], as.character(1:2))
})

test_that("melt_table2 ignores blank lines at the end of a file", {
  expect_warning(x <- melt_table2("x y\n1 2\n\n"), NA)
  expect_equal(nrow(x), 5L)
  expect_equal(x$value[3:4], as.character(1:2))
})

test_that("melt_table2 returns an empty data.frame on an empty file", {
   empty_df <- tibble::data_frame(row = double(), col = double(),
                                  data_type = character(), value = character())
   expect_true(all.equal(melt_table2("empty-file", progress = FALSE), empty_df))
})

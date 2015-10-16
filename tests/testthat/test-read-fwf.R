context("read_fwf")

test_that("trailing spaces ommitted", {
  spec <- fwf_empty("fwf-trailing.txt")
  expect_equal(spec$begin, c(0, 4))
  expect_equal(spec$end, c(3, 7))

  df <- read_fwf("fwf-trailing.txt", spec)
  expect_equal(df$X1, df$X2)
})

test_that("passing \"\" to read_fwf's 'na' option", {
  expect_equal(read_fwf('foobar\nfoo   ', fwf_widths(c(3, 3)), na = "")[[2]],
               c("bar", NA))
})

test_that("ragged last column silently expanded", {
  x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, 1)))
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 0)
})

test_that("ragged last column shrunk with warning", {
  expect_warning(x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, 3))))
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 2)
})

# read_table -------------------------------------------------------------------

test_that("read_table silently reads ragged last column", {
  x <- read_table("foo bar\n1   2\n3   4\n5   6\n")
  expect_equal(x$foo, c(1, 3, 5))
})

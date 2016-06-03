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

test_that("ragged last column expanded with NA", {
  x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, NA)))
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 0)
})

test_that("ragged last column shrunk with warning", {
  expect_warning(x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, 3))))
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 2)
})

test_that("read all columns with positions, non ragged", {
  col_pos <- fwf_positions(c(1,3,6),c(2,5,6))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos)
  expect_equal(x$X3, c("A", "B", "C"))
  expect_equal(n_problems(x), 0)
})

test_that("read subset columns with positions", {
  col_pos <- fwf_positions(c(1,3),c(2,5))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(n_problems(x), 0)
})

test_that("read columns with positions, ragged", {
  col_pos <- fwf_positions(c(1,3,6),c(2,5,NA))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(x$X3, c('A', 'BBBBBBBBB', 'C'))
  expect_equal(n_problems(x), 0)
})

test_that("read columns with width, ragged", {
  col_pos <- fwf_widths(c(2,3,NA))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(x$X3, c('A', 'BBBBBBBBB', 'C'))
  expect_equal(n_problems(x), 0)
})

# read_table -------------------------------------------------------------------

test_that("read_table silently reads ragged last column", {
  x <- read_table("foo bar\n1   2\n3   4\n5   6\n")
  expect_equal(x$foo, c(1, 3, 5))
})

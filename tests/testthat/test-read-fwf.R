context("read_fwf")

test_that("trailing spaces ommitted", {
  spec <- fwf_empty("fwf-trailing.txt")
  expect_equal(spec$begin, c(0, 4))
  expect_equal(spec$end, c(3, NA))

  df <- read_fwf("fwf-trailing.txt", spec, progress = FALSE)
  expect_equal(df$X1, df$X2)
})

test_that("skipping column doesn't pad col_names", {
  x <- "1 2 3\n4 5 6"

  out1 <- read_fwf(x, fwf_empty(x), col_types = 'd-d')
  expect_named(out1, c("X1", "X3"))

  names <- c("a", "b", "c")
  out2 <- read_fwf(x, fwf_empty(x, col_names = names), col_types = 'd-d')
  expect_named(out2, c("a", "c"))
})

test_that("fwf_empty can skip comments", {
  x <- "COMMENT\n1 2 3\n4 5 6"

  out1 <- read_fwf(x, fwf_empty(x, comment = "COMMENT"), comment = "COMMENT")
  expect_equal(dim(out1), c(2, 3))
})

test_that("passing \"\" to read_fwf's 'na' option", {
  expect_equal(read_fwf('foobar\nfoo   ', fwf_widths(c(3, 3)), na = "", progress = FALSE)[[2]],
               c("bar", NA))
})

test_that("ragged last column expanded with NA", {
  x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, NA)), progress = FALSE)
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 0)
})

test_that("ragged last column shrunk with warning", {
  expect_warning(x <- read_fwf("1a\n2ab\n3abc", fwf_widths(c(1, 3)), progress = FALSE))
  expect_equal(x$X2, c("a", "ab", "abc"))
  expect_equal(n_problems(x), 2)
})

test_that("read all columns with positions, non ragged", {
  col_pos <- fwf_positions(c(1,3,6),c(2,5,6))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos, progress = FALSE)
  expect_equal(x$X3, c("A", "B", "C"))
  expect_equal(n_problems(x), 0)
})

test_that("read subset columns with positions", {
  col_pos <- fwf_positions(c(1,3),c(2,5))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos, progress = FALSE)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(n_problems(x), 0)
})

test_that("read columns with positions, ragged", {
  col_pos <- fwf_positions(c(1,3,6),c(2,5,NA))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos, progress = FALSE)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(x$X3, c('A', 'BBBBBBBBB', 'C'))
  expect_equal(n_problems(x), 0)
})

test_that("read columns with width, ragged", {
  col_pos <- fwf_widths(c(2,3,NA))
  x <- read_fwf('12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos, progress = FALSE)
  expect_equal(x$X1, c(12, 67, 54))
  expect_equal(x$X2, c(345, 890, 321))
  expect_equal(x$X3, c('A', 'BBBBBBBBB', 'C'))
  expect_equal(n_problems(x), 0)
})

test_that("read_fwf returns an empty data.frame on an empty file", {
   expect_true(all.equal(read_fwf("empty-file", progress = FALSE), tibble::data_frame()))
})

test_that("check for line breaks in between widths", {
  txt1 <- paste(
    "1 1",
    "2",
    "1 1 ",
    sep = "\n"
  )
  expect_warning(out1 <- read_fwf(txt1, fwf_empty(txt1)))
  expect_equal(n_problems(out1), 2)

  txt2 <- paste(
    " 1 1",
    " 2",
    " 1 1 ",
    sep = "\n"
  )
  expect_warning(out2 <- read_fwf(txt2, fwf_empty(txt2)))
  expect_equal(n_problems(out2), 2)

  exp <- tibble::tibble(X1 = c(1L, 2L, 1L), X2 = c(1L, NA, 1L))
  expect_true(all.equal(out1, exp))
  expect_true(all.equal(out2, exp))

})

test_that("ignore commented lines anywhere in file", {
  col_pos <- fwf_positions(c(1,3,6),c(2,5,6))
  x1 <- read_fwf('COMMENT\n12345A\n67890BBBBBBBBB\n54321C',col_positions = col_pos, comment = "COMMENT", progress = FALSE)
  x2 <- read_fwf('12345A\n67890BBBBBBBBB\nCOMMENT\n54321C',col_positions = col_pos, comment = "COMMENT", progress = FALSE)
  x3 <- read_fwf('12345A\n67890BBBBBBBBB\n54321C\nCOMMENT',col_positions = col_pos, comment = "COMMENT", progress = FALSE)
  x4 <- read_fwf('COMMENT\n12345A\nCOMMENT\n67890BBBBBBBBB\n54321C\nCOMMENT',col_positions = col_pos, comment = "COMMENT", progress = FALSE)

  expect_identical(x1, x2)
  expect_identical(x1, x3)
  expect_identical(x1, x4)

  expect_equal(x1$X3, c("A", "B", "C"))
  expect_equal(n_problems(x1), 0)
})

test_that("error on empty spec (#511, #519)", {
  txt = "foo\n"
  pos = fwf_positions(start = numeric(0), end = numeric(0))
  expect_error(read_fwf(txt, pos), "Zero-length.*specifications not supported")
})

test_that("error on overlapping spec (#534)", {
  expect_error(
    read_fwf("2015a\n2016b", fwf_positions(c(1, 3, 5), c(4, 4, 5))),
    "Overlap.*"
    )
})

# fwf_cols
test_that("fwf_cols produces correct fwf_positions object with elements of length 2", {
  expected <- fwf_positions(c(1L, 9L, 4L), c(2L, 12L, 6L), c("a", "b", "d"))
  expect_equivalent(fwf_cols(a = c(1, 2), b = c(9, 12), d = c(4, 6)), expected)
})

test_that("fwf_cols produces correct fwf_positions object with elements of length 1", {
  expected <- fwf_widths(c(2L, 4L, 3L), c("a", "b", "c"))
  expect_equivalent(fwf_cols(a = 2, b = 4, c = 3), expected)
})


test_that("fwf_cols throws error when arguments are not length 1 or 2", {
  expect_error(fwf_cols(a = 1:3, b = 4:5))
  expect_error(fwf_cols(a = c(), b = 4:5))
})

test_that("fwf_cols works with unnamed columns", {
  expect_equivalent(
    fwf_cols(c(1, 2), c(9, 12), c(4, 6)),
    fwf_positions(c(1L, 9L, 4L), c(2L, 12L, 6L), c("X1", "X2", "X3"))
  )
  expect_equivalent(
    fwf_cols(a = c(1, 2), c(9, 12), c(4, 6)),
    fwf_positions(c(1L, 9L, 4L), c(2L, 12L, 6L), c("a", "X2", "X3"))
  )
})

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

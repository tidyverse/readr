test_that("trailing spaces ommitted", {
  withr::local_options(lifecycle_verbosity = "quiet")
  spec <- fwf_empty("fwf-trailing.txt")
  expect_equal(spec$begin, c(0, 4))
  expect_equal(spec$end, c(3, NA))

  df <- melt_fwf("fwf-trailing.txt", spec)
  expect_true(all(df$value == "123"))
})

test_that("respects the trim_ws argument", {
  withr::local_options(lifecycle_verbosity = "quiet")
  x <- "a11 b22 c33\nd   e   f  "
  out1 <- melt_fwf(x, fwf_empty(I(x)), trim_ws = FALSE)
  expect_equal(out1$value, c("a11", "b22", "c33", "d  ", "e  ", "f  "))

  out2 <- melt_fwf(x, fwf_empty(I(x)), trim_ws = TRUE)
  expect_equal(out2$value, c("a11", "b22", "c33", "d", "e", "f"))
})

test_that("respects the trim_ws argument with empty fields", {
  withr::local_options(lifecycle_verbosity = "quiet")
  x <- "a11 b22 c33\nd       f  "
  out1 <- melt_fwf(x, fwf_empty(I(x)), trim_ws = FALSE)
  expect_equal(out1$value, c("a11", "b22", "c33", "d  ", "   ", "f  "))

  out2 <- melt_fwf(x, fwf_empty(I(x)), trim_ws = TRUE, na = "NA")
  expect_equal(out2$value, c("a11", "b22", "c33", "d", "", "f"))
})

test_that("fwf_empty can skip comments", {
  withr::local_options(lifecycle_verbosity = "quiet")
  x <- "COMMENT\n1 2 3\n4 5 6"

  out1 <- melt_fwf(x, fwf_empty(I(x), comment = "COMMENT"), comment = "COMMENT")
  expect_equal(dim(out1), c(6, 4))
})

test_that("missing lines are not skipped", {
  withr::local_options(lifecycle_verbosity = "quiet")
  # first
  x <- "a b\n\n\n1 2"
  expect_equal(max(melt_fwf(x, fwf_empty(I(x)))$row), 4)

  # middle
  x <- "a b\n1 2\n\n\n2 3"
  expect_equal(max(melt_fwf(x, fwf_empty(I(x)))$row), 5)

  # last (trailing \n is ignored)
  x <- "a b\n1 2\n\n\n"
  expect_equal(max(melt_fwf(x, fwf_empty(I(x)))$row), 4)
})

test_that("passing \"\" to melt_fwf's 'na' option", {
  withr::local_options(lifecycle_verbosity = "quiet")
  expect_equal(
    melt_fwf("foobar\nfoo   ", fwf_widths(c(3, 3)), na = "")$value,
    c("foo", "bar", "foo", NA)
  )
})

test_that("ragged last column expanded with NA", {
  withr::local_options(lifecycle_verbosity = "quiet")
  x <- melt_fwf("1a\n2ab\n3abc", fwf_widths(c(1, NA)))
  expect_equal(x$value[c(2, 4, 6)], c("a", "ab", "abc"))
  expect_equal(n_problems(x), 0)
})

test_that("ragged last column shrunk with warning", {
  withr::local_options(lifecycle_verbosity = "quiet")
  expect_warning(x <- melt_fwf("1a\n2ab\n3abc", fwf_widths(c(1, 3))))
  expect_equal(x$value[c(2, 4, 6)], c("a", "ab", "abc"))
  expect_equal(n_problems(x), 2)
})

test_that("melt all columns with positions, non ragged", {
  withr::local_options(lifecycle_verbosity = "quiet")
  col_pos <- fwf_positions(c(1, 3, 6), c(2, 5, 6))
  x <- melt_fwf("12345A\n67890BBBBBBBBB\n54321C", col_positions = col_pos)
  expect_equal(x$value[c(3, 6, 9)], c("A", "B", "C"))
  expect_equal(n_problems(x), 0)
})

test_that("melt subset columns with positions", {
  withr::local_options(lifecycle_verbosity = "quiet")
  col_pos <- fwf_positions(c(1, 3), c(2, 5))
  x <- melt_fwf("12345A\n67890BBBBBBBBB\n54321C", col_positions = col_pos)
  expect_equal(x$value[c(1, 3, 5)], as.character(c(12, 67, 54)))
  expect_equal(x$value[c(2, 4, 6)], as.character(c(345, 890, 321)))
  expect_equal(n_problems(x), 0)
})

test_that("melt columns with positions, ragged", {
  withr::local_options(lifecycle_verbosity = "quiet")
  col_pos <- fwf_positions(c(1, 3, 6), c(2, 5, NA))
  x <- melt_fwf("12345A\n67890BBBBBBBBB\n54321C", col_positions = col_pos)
  expect_equal(x$value[c(1, 4, 7)], as.character(c(12, 67, 54)))
  expect_equal(x$value[c(2, 5, 8)], as.character(c(345, 890, 321)))
  expect_equal(x$value[c(3, 6, 9)], c("A", "BBBBBBBBB", "C"))
  expect_equal(n_problems(x), 0)
})

test_that("melt columns with width, ragged", {
  withr::local_options(lifecycle_verbosity = "quiet")
  col_pos <- fwf_widths(c(2, 3, NA))
  x <- melt_fwf("12345A\n67890BBBBBBBBB\n54321C", col_positions = col_pos)
  expect_equal(x$value[c(1, 4, 7)], as.character(c(12, 67, 54)))
  expect_equal(x$value[c(2, 5, 8)], as.character(c(345, 890, 321)))
  expect_equal(x$value[c(3, 6, 9)], c("A", "BBBBBBBBB", "C"))
  expect_equal(n_problems(x), 0)
})

test_that("melt_fwf returns an empty data.frame on an empty file", {
  withr::local_options(lifecycle_verbosity = "quiet")
  empty_df <- tibble::tibble(
    row = double(), col = double(),
    data_type = character(), value = character()
  )
  expect_true(all.equal(melt_fwf("empty-file"), empty_df))
})

test_that("check for line breaks in between widths", {
  withr::local_options(lifecycle_verbosity = "quiet")
  txt1 <- paste(
    "1 1",
    "2",
    "1 1 ",
    sep = "\n"
  )
  expect_warning(out1 <- melt_fwf(txt1, fwf_empty(I(txt1))))
  expect_equal(n_problems(out1), 1)

  txt2 <- paste(
    " 1 1",
    " 2",
    " 1 1 ",
    sep = "\n"
  )
  expect_warning(out2 <- melt_fwf(txt2, fwf_empty(I(txt2))))
  expect_equal(n_problems(out2), 1)

  exp <- tibble::tibble(
    row = c(1, 1, 2, 3, 3),
    col = c(1, 2, 1, 1, 2),
    data_type = "integer",
    value = as.character(c(1, 1, 2, 1, 1))
  )
  expect_true(all.equal(out1, exp, check.attributes = FALSE))
  expect_true(all.equal(out2, exp, check.attributes = FALSE))
})

test_that("ignore commented lines anywhere in file", {
  withr::local_options(lifecycle_verbosity = "quiet")
  col_pos <- fwf_positions(c(1, 3, 6), c(2, 5, 6))
  x1 <- melt_fwf("COMMENT\n12345A\n67890BBBBBBBBB\n54321C", col_positions = col_pos, comment = "COMMENT")
  x2 <- melt_fwf("12345A\n67890BBBBBBBBB\nCOMMENT\n54321C", col_positions = col_pos, comment = "COMMENT")
  x3 <- melt_fwf("12345A\n67890BBBBBBBBB\n54321C\nCOMMENT", col_positions = col_pos, comment = "COMMENT")
  x4 <- melt_fwf("COMMENT\n12345A\nCOMMENT\n67890BBBBBBBBB\n54321C\nCOMMENT", col_positions = col_pos, comment = "COMMENT")

  expect_identical(x1, x2)
  expect_identical(x1, x3)
  expect_identical(x1, x4)

  expect_equal(x1$value[c(3, 6, 9)], c("A", "B", "C"))
  expect_equal(n_problems(x1), 0)
})

test_that("error on empty spec", {
  withr::local_options(lifecycle_verbosity = "quiet")
  txt <- "foo\n"
  pos <- fwf_positions(start = numeric(0), end = numeric(0))
  expect_error(melt_fwf(txt, pos), "Zero-length.*specifications not supported")
})

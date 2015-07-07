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

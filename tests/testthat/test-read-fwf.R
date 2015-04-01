context("read_fwf")

test_that("trailing spaces ommitted", {
  spec <- fwf_empty("fwf-trailing.txt")
  expect_equal(spec$begin, c(0, 4))
  expect_equal(spec$end, c(3, 7))

  df <- read_fwf("fwf-trailing.txt", spec)
  expect_equal(df$X1, df$X2)
})

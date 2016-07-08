context("Encoding")
test_that("guess_encoding() works", {
  x <- guess_encoding(system.file("extdata/mtcars.csv", package = "readr"))
  expect_equal(as.character(x$encoding), "ASCII")
  expect_equal(x$confidence, 1)

  x <- guess_encoding("a\n\u00b5\u00b5")
  expect_equal(as.character(x$encoding), "UTF-8")
  expect_equal(x$confidence, 8)
})

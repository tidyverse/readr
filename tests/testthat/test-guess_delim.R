context("test-guess_delim")

test_that("guess_delim identifies delim that is repeated same number of times in all rows", {
  delim <- guess_delim("./tests/testthat/basic-df.csv")
  expect_equal(delim, ",")
  expect_is(delim, "character")
  expect_length(delim, 1)
})

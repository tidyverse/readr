context("test-source.R")

test_that("standardise_path works", {
  expect_error(standardise_path("https://foo/bar.bz2"), "compressed files is not supported")
})

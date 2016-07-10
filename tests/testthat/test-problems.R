context("problems")

test_that("stop_for_problems throws error", {
  expect_warning(x <- parse_integer("1.234"))
  expect_error(stop_for_problems(x), "1 parsing failure")
})

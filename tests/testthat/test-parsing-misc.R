context("Parsing, misc")

test_that("euro double parses negative numbers", {
  expect_equal(parse_euro_double("-16,1"), -16.1)
})

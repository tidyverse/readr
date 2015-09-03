context("Parsing: numeric")

test_that("non-numeric integer/double matches fail", {
  expect_true(is.na(parse_double("d")))
  expect_true(is.na(parse_integer("d")))
})

test_that("partial integer/double matches fail", {
  expect_true(is.na(parse_double("3d")))
  expect_true(is.na(parse_integer("3d")))
})

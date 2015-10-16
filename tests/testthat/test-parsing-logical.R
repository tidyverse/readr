context("Parsing, logical")

test_that("TRUE and FALSE parsed", {
  expect_equal(parse_logical(c("TRUE", "FALSE")), c(TRUE, FALSE))
})

test_that("T and F parsed", {
  expect_equal(parse_logical(c("T", "F")), c(TRUE, FALSE))
})

test_that("other values generate warnings", {
  expect_warning(out <- parse_logical(c("A", "AB", "ABCD", "ABCDE", "NA")))
  expect_equivalent(out, rep(NA, 5))
  expect_equal(n_problems(out), 4)
})

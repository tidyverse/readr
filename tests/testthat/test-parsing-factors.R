context("Parsing, factors")

test_that("strings mapped to levels", {
  x <- parse_factor(c("a", "b"), levels = c("a", "b"))
  expect_equal(x, factor(c("a", "b")))
})

test_that("can generate ordered factor", {
  x <- parse_factor(c("a", "b"), levels = c("a", "b"), ordered = TRUE)
  expect_equal(x, ordered(c("a", "b")))
})

test_that("warning if value not in levels", {
  expect_warning(x <- parse_factor(c("a", "b", "c"), levels = c("a", "b")))
  expect_equal(n_problems(x), 1)
  expect_equal(is.na(x), c(FALSE, FALSE, TRUE))
})

test_that("NAs silently passed along", {
  x <- parse_factor(c("a", "b", "NA"), levels = c("a", "b"))
  expect_equal(n_problems(x), 0)
  expect_equal(x, factor(c("a", "b", NA)))
})


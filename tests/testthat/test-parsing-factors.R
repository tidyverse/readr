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
  x <- parse_factor(c("a", "b", "NA"), levels = c("a", "b"), include_na = FALSE)
  expect_equal(n_problems(x), 0)
  expect_equal(x, factor(c("a", "b", NA)))
})

test_that("levels = NULL (497)", {
  x <- parse_factor(c("a", "b", "c", "b"), levels = NULL)

  expect_equal(n_problems(x), 0)
  expect_equal(x, factor(c("a", "b", "c", "b")))
})

test_that("NAs included in levels if desired", {
  x <- parse_factor(c("NA", "b", "a"), levels = c("a", "b", NA))
  expect_equal(x, factor(c(NA, "b", "a"), levels = c("a", "b", NA), exclude = NULL))

  x <- parse_factor(c("NA", "b", "a"), levels = c("a", "b"), include_na = TRUE)
  expect_equal(x, factor(c(NA, "b", "a"), levels = c("a", "b", NA), exclude = NULL))

  x <- parse_factor(c("NA", "b", "a"), levels = c("a", "b"), include_na = FALSE)
  expect_equal(x, factor(c(NA, "b", "a")))

  x <- parse_factor(c("NA", "b", "a"), levels = NULL, include_na = FALSE)
  expect_equal(x, factor(c("NA", "b", "a"), levels = c("b", "a")))

  x <- parse_factor(c("NA", "b", "a"), levels = NULL, include_na = TRUE)
  expect_equal(x, factor(c("NA", "b", "a"), levels = c(NA, "b", "a"), exclude = NULL))
})

test_that("Factors handle encodings properly (#615)", {
  x <- read_csv(encoded("test\nA\n\xC4\n", "latin1"),
    col_types = cols(col_factor(c("A", "\uC4"))),
    locale = locale(encoding = "latin1"), progress = FALSE)

  expect_is(x$test, "factor")
  expect_equal(x$test, factor(c("A", "\uC4")))
})

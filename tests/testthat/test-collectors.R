context("Collectors")

test_that("guess for empty strings is character", {
  expect_equal(collector_guess(c("", "")), "character")
})

test_that("guess for missing vector is character", {
  expect_equal(collector_guess(NA_character_), "character")
})

test_that("empty + NA ignored when determining type", {
  expect_equal(collector_guess(c("1", "")), "integer")
  expect_equal(collector_guess(c("1", NA)), "integer")
})

test_that("guess decimal commas with correct locale", {
  expect_equal(collector_guess("1,300"), "number")
  expect_equal(collector_guess("1,300", locale(decimal_mark = ",")), "double")
})

# Numbers -----------------------------------------------------------------

test_that("only accept numbers with grouping mark", {
  expect_equal(collector_guess("1,300"), "number")
  expect_equal(collector_guess("1,300.00"), "number")
})

# Concise collectors specification ----------------------------------------

test_that("_ or - skips column", {
  out1 <- read_csv("x,y\n1,2\n3,4", col_types = "-i")
  out2 <- read_csv("x,y\n1,2\n3,4", col_types = "_i")

  expect_equal(names(out1), "y")
  expect_equal(names(out2), "y")
})

test_that("? guesses column type", {
  out1 <- read_csv("x,y\n1,2\n3,4", col_types = "?i")
  expect_equal(out1$x, c(1L, 3L))
})

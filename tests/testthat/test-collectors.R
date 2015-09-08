context("Collectors")

test_that("guess for empty strings is character", {
  expect_equal(collectorGuess(c("", ""), locale()), "character")
})

test_that("guess for missing vector is character", {
  expect_equal(collectorGuess(NA_character_, locale()), "character")
})

test_that("empty + NA ignored when determining type", {
  expect_equal(collectorGuess(c("1", ""), locale()), "integer")
  expect_equal(collectorGuess(c("1", NA), locale()), "integer")
})

test_that("guess decimal commas with correct locale", {
  expect_equal(collectorGuess("1,3", locale()), "character")
  expect_equal(collectorGuess("1,3", locale(decimal_mark = ",")), "double")
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

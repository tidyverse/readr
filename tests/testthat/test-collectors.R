test_that("guess for empty strings is logical", {
  expect_equal(guess_parser(c("", "")), "logical")
})

test_that("guess for missing vector is logical", {
  expect_equal(guess_parser(NA_character_), "logical")
})

test_that("empty + NA ignored when determining type", {
  expect_equal(guess_parser(c("1", "")), "double")
  expect_equal(guess_parser(c("1", NA)), "double")
})

test_that("guess decimal commas with correct locale", {
  expect_equal(guess_parser("1,300"), "number")
  expect_equal(guess_parser("1,300", locale(decimal_mark = ",")), "double")
})

# Numbers -----------------------------------------------------------------

test_that("only accept numbers with grouping mark", {
  expect_equal(guess_parser("1,300"), "number")
  expect_equal(guess_parser("1,300.00"), "number")
})

# Concise collectors specification ----------------------------------------

test_that("_ or - skips column", {
  out1 <- read_csv(I("x,y\n1,2\n3,4"), col_types = "-i")
  out2 <- read_csv(I("x,y\n1,2\n3,4"), col_types = "_i")

  expect_equal(names(out1), "y")
  expect_equal(names(out2), "y")
})

test_that("? guesses column type", {
  out1 <- read_csv(I("x,y\n1,2\n3,4"), col_types = "?i")
  expect_equal(out1$x, c(1L, 3L))
})

test_that("f parses factor (#810)", {
  out <- read_csv(I("x,y\na,2\nb,4"), col_types = "fi")
  expect_s3_class(out$x, "factor")
})

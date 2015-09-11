context("Parsing, character")

test_that("ws dropped by default", {
  df <- read_csv("x\n a \n    b\n")
  expect_equal(df$x, c("a", "b"))
})

test_that("trim_ws = FALSE keeps ws", {
  df <- read_csv("x\n a\nb \n", trim_ws = FALSE)
  expect_equal(df$x, c(" a", "b "))
})


# Encoding ----------------------------------------------------------------

test_that("locale encoding affects parsing", {
  x <- c("août", "élève", "ça va")
  # expect_equal(Encoding(x), rep("UTF-8", 3))

  y <- iconv(x, "UTF-8", "latin1")
  # expect_equal(Encoding(x), rep("latin1", 3))

  fr <- locale("fr", encoding = "latin1")
  z <- parse_character(y, locale = fr)
  # expect_equal(Encoding(z), rep("UTF-8", 3))

  # identical coerces encodings to match, so need to compare raw values
  as_raw <- function(x) lapply(x, charToRaw)
  expect_identical(as_raw(x), as_raw(z))
})

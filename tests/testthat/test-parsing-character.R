context("Parsing, character")

test_that("ws dropped by default", {
  df <- read_csv("x\n a \n    b\n")
  expect_equal(df$x, c("a", "b"))
})

test_that("trim_ws = FALSE keeps ws", {
  df <- read_csv("x\n a\nb \n", trim_ws = FALSE)
  expect_equal(df$x, c(" a", "b "))
})


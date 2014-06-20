context("Parsers")

read_abc <- function(parser, ...) {
  read_csv("abc.csv", col_names = "x", parsers = list(parser), ...)
}

test_that("factor parser respects levels", {
  df1 <- read_abc(factor_parser(c("a", "b", "c")))
  df2 <- read_abc(factor_parser(c("c", "b", "a")))

  expect_equal(df1$x, factor(c("a", "b", "c")))
  expect_equal(df2$x, factor(c("a", "b", "c"), levels = c("c", "b", "a")))
})

test_that("factor parser respects ordered", {
  df <- read_abc(factor_parser(c("a", "b", "c"), ordered = TRUE))
  expect_equal(df$x, ordered(c("a", "b", "c")))
})

test_that("factor parser complains when it sees unknown level", {
  expect_error(read_abc(factor_parser("a")), "not in list")
})


read_csv("inst/tests/abc.csv", col_names = "x", parsers = list(factor_parser(c("a", "b", "c"))))
read_csv("inst/tests/abc.csv", col_names = "x", parsers = list(factor_parser(c("a", "b"))))

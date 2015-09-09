context("Parsing, numeric")

test_that("non-numeric integer/double matches fail", {
  expect_true(is.na(parse_double("d")))
  expect_true(is.na(parse_integer("d")))
})

test_that("partial integer/double matches fail", {
  expect_true(is.na(parse_double("3d")))
  expect_true(is.na(parse_integer("3d")))
})

test_that("parse functions converts NAs", {
  expect_equal(parse_double(c("1.5", "NA")), c(1.5, NA))
})

test_that("leading/trailing ws ignored when parsing", {
  expect_equal(parse_double(c(" 1.5", "1.5", "1.5 ")), rep(1.5, 3))
  expect_equal(read_csv("x\n 1.5\n1.5\n1.5 \n")$x, rep(1.5, 3))
})


# Decimal comma -----------------------------------------------------------

es_MX <- locale("es", decimal_mark = ",")

test_that("parse_vector passes along decimal_mark", {
  expect_equal(parse_vector("1,5", col_double(), locale = es_MX), 1.5)
})

test_that("type_convert passes along decimal_mark", {
  df <- data.frame(x = "1,5", stringsAsFactors = FALSE)
  out <- type_convert(df, locale = es_MX)

  expect_equal(out$x, 1.5)
})

test_that("read_tsv passes on decimal_mark", {
  out <- read_tsv("x\n1,5", locale = es_MX)
  expect_equal(out$x, 1.5)
})

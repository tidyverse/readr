context("Parsing, numeric")

test_that("non-numeric integer/double matches fail", {
  expect_equal(n_problems(parse_double("d")), 1)
  expect_equal(n_problems(parse_integer("d")), 1)
})

test_that("partial integer/double matches fail", {
  expect_equal(n_problems(parse_double("3d")), 1)
  expect_equal(n_problems(parse_integer("3d")), 1)
})

test_that("parse functions converts NAs", {
  expect_equal(parse_double(c("1.5", "NA")), c(1.5, NA))
})

test_that("leading/trailing ws ignored when parsing", {
  expect_equal(parse_double(c(" 1.5", "1.5", "1.5 ")), rep(1.5, 3))
  expect_equal(read_csv("x\n 1.5\n1.5\n1.5 \n")$x, rep(1.5, 3))
})


# Leading zeros -----------------------------------------------------------

test_that("leading zeros are not numbers", {
  expect_equal(collector_guess("0"), "integer")
  expect_equal(collector_guess("0."), "double")
  expect_equal(collector_guess("0001"), "character")
})

# Flexible number parsing -------------------------------------------------
es_MX <- locale("es", decimal_mark = ",")

test_that("col_number only takes first number", {
  expect_equal(parse_number("XYZ 123,000 BLAH 456"), 123000)
})

test_that("col_number helps with currency", {
  expect_equal(parse_number("$1,000,000.00"), 1e6)
  expect_equal(parse_number("$1.000.000,00", locale = es_MX), 1e6)
})

test_that("invalid numbers don't parse", {
  expect_warning(x <- parse_number(c("..", "--", "3.3.3", "4-1")))
  expect_equal(n_problems(x), 4)
  expect_equal(is.na(x), c(TRUE, TRUE, TRUE, TRUE))
})

# Decimal comma -----------------------------------------------------------

test_that("parse_vector passes along decimal_mark", {
  expect_equal(parse_double("1,5", locale = es_MX), 1.5)
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

context("Parsing, numeric")
es_MX <- locale("es", decimal_mark = ",")

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
  expect_equal(read_csv("x\n 1.5\n1.5\n1.5 \n", progress = FALSE)$x, rep(1.5, 3))
})

test_that("lone - or decimal marks are not numbers", {
  expect_equal(guess_parser("-"), "character")
  expect_equal(guess_parser("."), "character")
  expect_equal(guess_parser(",", locale = es_MX), "character")

  expect_equal(n_problems(parse_number(c(".", "-"))), 2)
})

test_that("Numbers with trailing characters are parsed as characters", {
  expect_equal(guess_parser("13T"), "character")
  expect_equal(guess_parser(c("13T", "13T", "10N")), "character")
})

test_that("problems() returns the full failed string if parsing fails (548)", {
  probs <- problems(read_tsv("x\n1\nx", na = "", col_types = "n"))
  expect_equal(probs$row, 2)
  expect_equal(probs$expected, "a number")
  expect_equal(probs$actual, "x")
})

# Leading zeros -----------------------------------------------------------

test_that("leading zeros are not numbers", {
  expect_equal(guess_parser("0"), "integer")
  expect_equal(guess_parser("0."), "double")
  expect_equal(guess_parser("0001"), "character")
})

# Flexible number parsing -------------------------------------------------
test_that("col_number only takes first number", {
  expect_equal(parse_number("XYZ 123,000 BLAH 456"), 123000)
})

test_that("col_number helps with currency", {
  expect_equal(parse_number("$1,000,000.00"), 1e6)
  expect_equal(parse_number("$1.000.000,00", locale = es_MX), 1e6)
})

test_that("invalid numbers don't parse", {
  expect_warning(x <- parse_number(c("..", "--", "3.3.3", "4-1")))
  expect_equal(n_problems(x), 2)
  expect_equal(c(x), c(NA, NA, 3.3, 4.0))
})

test_that("number not guess if leading/trailing", {
  expect_equal(guess_parser("X1"), "character")
  expect_equal(parse_number("X1"), 1)

  expect_equal(guess_parser("1X"), "character")
  expect_equal(parse_number("1X"), 1)
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
  out <- read_tsv("x\n1,5", locale = es_MX, progress = FALSE)
  expect_equal(out$x, 1.5)
})

# Negative numbers -----------------------------------------------------------

test_that("negative numbers return negative values", {
  expect_equal(parse_number("-2"), -2)

  expect_equal(parse_number("-100,000.00"), -100000)
})

# Large numbers -------------------------------------------------------------

test_that("large numbers are parsed properly", {
  expect_equal(parse_double("100000000000000000000"), 1e20)

  expect_equal(parse_double("1267650600228229401496703205376"), 1.267650600228229401496703205376e+30)

  expect_equal(parse_double("100000000000000000000", locale = es_MX), 1e20)

  expect_equal(parse_double("1267650600228229401496703205376", locale = es_MX), 1.267650600228229401496703205376e+30)
})

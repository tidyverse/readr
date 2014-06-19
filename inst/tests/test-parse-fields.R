context("Parse fields")

abc <- c("a", "b", "c")
test_that("simple delimiters parsed as expected", {
  expect_equal(parse_delimited_fields("a,b,c"), abc)
  expect_equal(parse_delimited_fields("a|b|c", "|"), abc)
})

test_that("quotes not included in output", {
  expect_equal(parse_delimited_fields('"a",b,"c"'), abc)
})

test_that("not split on delimiters in strings", {
  expect_equal(parse_delimited_fields('a,"b,c"'), c("a", "b,c"))
})

test_that("escaped quote doesn't terminate string", {
  expect_equal(
    parse_delimited_fields('a,"b""c', double_escape = TRUE),
    c("a", "b\"c")
  )
  expect_equal(
    parse_delimited_fields('a,"b\\"c', backslash_escape = TRUE),
    c("a", "b\\\"c")
  )
})

test_that("can escape delim if backslash_escape = TRUE", {
  expect_equal(
    parse_delimited_fields("a,b\\,c", backslash_escape = TRUE),
    c("a", "b\\,c")
  )
})

test_that("in strict mode, errors if escapes or strings unterminated", {
  expect_error(
    parse_delimited_fields("a\\", backslash_escape = TRUE, strict = TRUE),
    "Unterminated escape"
  )
  expect_error(
    parse_delimited_fields('"a', double_escape = TRUE, strict = TRUE),
    "Unterminated string"
  )
})

test_that("trailing delim leads to empty last value", {
  expect_equal(parse_delimited_fields(","), c("", ""))
})

test_that("parsing empty string gives length 0 output", {
  expect_equal(parse_delimited_fields(""), character())
})

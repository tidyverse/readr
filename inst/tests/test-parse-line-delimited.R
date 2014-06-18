context("parse_line_delimited")

abc <- c("a", "b", "c")
test_that("simple delimiters parsed as expected", {
  expect_equal(parse_line_delimited("a,b,c"), abc)
  expect_equal(parse_line_delimited("a|b|c", "|"), abc)
})

test_that("quotes not included in output", {
  expect_equal(parse_line_delimited('"a",b,"c"'), abc)
})

test_that("not split on delimiters in strings", {
  expect_equal(parse_line_delimited('a,"b,c"'), c("a", "b,c"))
})

test_that("can escape delim if backslash_escape = TRUE", {
  expect_equal(
    parse_line_delimited("a,b\\,c", backslash_escape = TRUE),
    c("a", "b,c")
  )
})


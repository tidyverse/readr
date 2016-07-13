context("TokenizerDelim")
# Tests tokenizing and unescaping

parse_b <- function(x, ...) {
  tok <- tokenizer_delim(",", escape_double = FALSE, escape_backslash = TRUE, ...)
  tokenize(datasource_string(x, 0), tok)
}
parse_d <- function(x, ...) {
  tok <- tokenizer_delim(",", escape_double = TRUE, escape_backslash = FALSE, ...)
  tokenize(datasource_string(x, 0), tok)
}

test_that("simple sequence parsed correctly", {
  expect_equal(parse_d('1,2,3'), list(c("1", "2", "3")))
})

test_that("newlines are not tokenised", {
  expect_equal(parse_d('1\n2'), list("1", "2"))
})

test_that("quotes in strings are dropped", {
  expect_equal(parse_d('"abc",abc'), list(c("abc", "abc")))
  expect_equal(parse_b('"abc",abc'), list(c("abc", "abc")))

  expect_equal(parse_b("'abc',abc", quote = "'"), list(c("abc", "abc")))
  expect_equal(parse_d("'abc',abc", quote = "'"), list(c("abc", "abc")))
})

test_that("problems if unterminated string", {
  p1 <- problems(parse_d('1,2,"3'))
  p2 <- problems(parse_b('1,2,"3'))

  expect_equal(p1$col, 3)
  expect_equal(p2$col, 3)

  expect_equal(p1$expected, "closing quote at end of file")
  expect_equal(p2$expected, "closing quote at end of file")
})

test_that("problem if unterminated escape", {
  p <- problems(parse_b('1\\'))

  expect_equal(p$row, 1)
  expect_equal(p$col, 1)
})

test_that("empty fields become empty strings", {
  expect_equal(parse_d(',\n,'), list(c("[EMPTY]", "[EMPTY]"), c("[EMPTY]", "[EMPTY]")))
  expect_equal(parse_d(',\n,\n'), list(c("[EMPTY]", "[EMPTY]"), c("[EMPTY]", "[EMPTY]")))
  expect_equal(parse_d('""'), list("[EMPTY]"))
})

test_that("bare NA becomes missing value", {
  expect_equal(parse_b('NA,"NA"', quoted_na = FALSE), list(c("[MISSING]", "NA")))
  expect_equal(parse_d('NA,"NA"', quoted_na = FALSE), list(c("[MISSING]", "NA")))
})

test_that("quoted NA also becomes missing value", {
  expect_equal(parse_b('NA,"NA"', quoted_na = TRUE), list(c("[MISSING]", "[MISSING]")))
  expect_equal(parse_d('NA,"NA"', quoted_na = TRUE), list(c("[MISSING]", "[MISSING]")))
})

test_that("empty string become missing values", {
  expect_equal(parse_b('NA,""', na = ""), list(c("NA", "[MISSING]")))
})

test_that("NA with spaces becomes missing value", {
  expect_equal(parse_b(' NA '), list(c("[MISSING]")))
})

test_that("string can be ended by new line", {
  expect_equal(parse_d('123,"a"\n'), list(c("123", "a")))
})

test_that("can escape delimeter with backslash", {
  expect_equal(parse_b('1\\,2'), list("1,2"))
})

test_that("doubled quote becomes single quote (with d-escaping)", {
  expect_equal(parse_d('""""'), list('"'))
})

test_that("escaped quoted doesn't terminate string (with b-escaping)", {
  expect_equal(parse_b('"\\""'), list('"'))
})

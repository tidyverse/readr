context("TokenizerDelim")
# Tests tokenizing and unescaping, via CollectorCharacter.

parse_b <- function(x) {
  tok <- tokenizer_delim(",", escape_double = FALSE, escape_backslash = TRUE)
  parse_vector(x, tok, col_character())
}
parse_d <- function(x) {
  tok <- tokenizer_delim(",", escape_double = TRUE, escape_backslash = FALSE)
  parse_vector(x, tok, col_character())
}

test_that("simple sequence parsec correctly", {
  expect_equal(parse_d('1,2,3'), c("1", "2", "3"))
})

test_that("newlines are not tokenised", {
  expect_equal(parse_d('1\n2'), c("1", "2"))
})

test_that("quotes in strings are dropped", {
  expect_equal(parse_d('"abc",abc'), c("abc", "abc"))
  expect_equal(parse_b('"abc",abc'), c("abc", "abc"))
})

test_that("warning if unterminated string", {
  expect_warning(parse_d('1,2,"3'), "Unterminated string")
  expect_warning(parse_b('1,2,"3'), "Unterminated string")
})

test_that("warning if unterminated escape", {
  expect_warning(parse_b('1\\'), "Unterminated escape")
})

test_that("empty fields become empty strings", {
  expect_equal(parse_d(',\n,'), rep("", 4))
  expect_equal(parse_d(',\n,\n'), rep("", 4))
  expect_equal(parse_d('""'), rep("", 1))
})

test_that("bare NA becomes missing value", {
  expect_equal(parse_b('NA,"NA"'), c(NA, "NA"))
  expect_equal(parse_d('NA,"NA"'), c(NA, "NA"))
})

test_that("string can be ended by new line", {
  expect_equal(parse_d('123,"a"\n'), c("123", "a"))
})

test_that("can escape delimeter with backslash", {
  expect_equal(parse_b('1\\,2'), "1,2")
})

test_that("doubled quote becomes single quote (with d-escaping)", {
  expect_equal(parse_d('""""'), '"')
})

test_that("escaped quoted doesn't terminate string (with b-escaping)", {
  expect_equal(parse_b('"\\""'), '"')
})

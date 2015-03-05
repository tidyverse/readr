context("TokeniserDelimited")

tokenize_simple <- function(x) unlist(tokenize(text = x))

test_that("simple sequence tokenised correctly", {
  expect_equal(tokenize_simple('1,2,3'), c("1", "2", "3"))
})

test_that("newlines are not tokenised", {
  expect_equal(tokenize_simple('1\n2'), c("1", "2"))
})

test_that("quotes in strings are dropped", {
  expect_equal(tokenize_simple('"abc",abc'), c("abc", "abc"))
})

test_that("warning if unterminated string", {
  expect_warning(tokenize_simple('1,2,"3'), "Unterminated string")
})

test_that("empty fields get special token", {
  expect_equal(tokenize_simple(',\n,'), rep("[EMPTY]", 4))
  expect_equal(tokenize_simple(',\n,\n'), rep("[EMPTY]", 4))
  expect_equal(tokenize_simple('""'), rep("[EMPTY]", 1))
})

test_that("bare NA tokenised to missing", {
  expect_equal(tokenize_simple('NA,"NA"'), c("[MISSING]", "NA"))
})

test_that("string can be ended by new line", {
  expect_equal(tokenize_simple('123,"a"\n'), c("123", "a"))
})

context("TokeniserDelimited")

test_that("simple sequence tokenised correctly", {
  expect_equal(tokenizeString('1,2,3'), c("1", "2", "3"))
})

test_that("newlines are not tokenised", {
  expect_equal(tokenizeString('1\n2'), c("1", "2"))
})

test_that("quotes in strings are dropped", {
  expect_equal(tokenizeString('"abc",abc'), c("abc", "abc"))
})

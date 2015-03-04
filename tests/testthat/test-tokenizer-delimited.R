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

test_that("escapes are removed from strings", {
  expect_equal(tokenizeString('""""'), '"')
})


test_that("warning if unterminated string", {
  expect_warning(tokenizeString('1,2,"3'), "Unterminated string")
})

test_that("empty fields get special token", {
  expect_equal(tokenizeString(',\n,'), rep("[EMPTY]", 4))
  expect_equal(tokenizeString(',\n,\n'), rep("[EMPTY]", 4))
  expect_equal(tokenizeString('""'), rep("[EMPTY]", 1))
})

test_that("bare NA tokenised to missing", {
  expect_equal(tokenizeString('NA,"NA"'), c("[MISSING]", "NA"))
})


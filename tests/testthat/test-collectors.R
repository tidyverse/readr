context("Collectors")

test_that("guess for empty vector is character", {
  expect_equal(collectorGuess(c("", "")), "character")
})

test_that("guess for missing vector is character", {
  expect_equal(collectorGuess(NA_character_), "character")
})

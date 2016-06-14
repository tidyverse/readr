context("type_convert")

test_that("missing values removed before guessing col type", {
  df1 <- data.frame(x = c("NA", "10"), stringsAsFactors = FALSE)
  df2 <- type_convert(df1)

  expect_equal(df2$x, c(NA, 10L))
})

test_that("requires data.frame input", {
  not_df <- matrix(letters[1:4], nrow = 2)
  expect_error(type_convert(not_df), "is.data.frame")
})

test_that("character specifications of col_types not allowed", {
  expect_error(type_convert(mtcars, col_types = "dididddiiii"), "must be `NULL` or a `cols` specification")
})

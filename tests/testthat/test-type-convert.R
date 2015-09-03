context("type_convert")

test_that("missing values removed before guessing col type", {
  df1 <- data.frame(x = c("NA", "10"), stringsAsFactors = FALSE)
  df2 <- type_convert(df1)

  expect_equal(df2$x, c(NA, 10L))
})

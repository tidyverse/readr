test_that("missing values removed before guessing col type", {
  df1 <- data.frame(x = c("NA", "10"), stringsAsFactors = FALSE)
  df2 <- type_convert(df1)

  expect_equal(df2$x, c(NA, 10L))
})

test_that("requires data.frame input", {
  not_df <- matrix(letters[1:4], nrow = 2)
  expect_error(type_convert(not_df), "is.data.frame")
})

test_that("col_types accepts character specifications", {
  df <- data.frame(x = 1:3, y = "3", z = "a", stringsAsFactors = FALSE)
  df_conv <- data.frame(x = 1:3, y = 3L, z = "a", stringsAsFactors = FALSE)

  expect_error(type_convert(df, col_types = "i"), "must have consistent lengths")

  expect_error(type_convert(df, col_types = c("i", "b")), "must be a single string")

  expect_equal(type_convert(df, col_types = "_ic"), df_conv)
})
test_that("col_types accepts cols specifications", {
  df <- data.frame(x = 1:3, y = "3", z = "a", stringsAsFactors = FALSE)
  df_conv <- data.frame(x = 1:3, y = 3L, z = "a", stringsAsFactors = FALSE)

  expect_equal(type_convert(df, col_types = cols(y = "i")), df_conv)

  expect_equal(type_convert(df, col_types = cols(y = col_integer(), z = col_character())), df_conv)

  # non-character cols silently ignored
  expect_equal(type_convert(df, col_types = cols(x = "c", y = "i")), df_conv)
})
test_that("spec attribute is removed", {
  df1 <-
    read_csv(
      readr_example("mtcars.csv"),
      col_types = cols(.default = col_character())
    )

  df2 <- type_convert(df1)

  # The spec attribute should exist initially (b/c it's set by `read_csv()`).
  expect_false(is.null(attr(df1, "spec")))

  # The spec attribute should be cleared by `type_convert()`.
  expect_null(attr(df2, "spec"))
})

test_that("warning is thrown if there are no character columns (1020)", {
  expect_warning(type_convert(mtcars), "only converts columns")
})

test_that("guess_integer is implemented", {
  df <- data.frame(
    a = c("a", "b", "c"),
    b = c("1", "0", "-12"),
    c = c("1", "0", ".00001"),
    stringsAsFactors = FALSE
  )

  exp <- data.frame(
    a = c("a", "b", "c"),
    b = c(1L, 0L, -12L),
    c = c(1, 0, .00001),
    stringsAsFactors = FALSE
  )

  expect_identical(type_convert(df, guess_integer = TRUE), exp)
})

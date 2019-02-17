context("test-read-builtin")

test_that("read_builtin works", {
  # fails with unquoted symbol (like data(storms, package = "dplyr"))
  expect_error(read_builtin(storms, "dplyr"))

  # fails with warning if namespace is not attached
  expect_error(
    expect_warning(
      read_builtin("storms")
    )
  )
  # fails with warning if data set doesn't exist in package
  expect_error(
    expect_warning(
      read_builtin("nasa", "readr")
    )
  )
  # works if data set exists in package
  expect_true(is.data.frame(read_builtin("storms", "dplyr")))
  # works if data set package is loaded
  library(dplyr)
  expect_true(is.data.frame(read_builtin("storms")))
})

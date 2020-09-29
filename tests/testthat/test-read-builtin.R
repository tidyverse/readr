test_that("read_builtin works", {
  skip_if(interactive())
  # fails with unquoted symbol (like data(storms, package = "dplyr"))
  expect_error(read_builtin(storms, "dplyr"))

  # fails with error if the dataset namespace is not attached
  unloadNamespace("dplyr")
  expect_error(
    read_builtin("storms")
  )
  # fails with an error if data set doesn't exist in package
  expect_error(
    read_builtin("nasa", "readr")
  )
  # works if data set exists in package
  expect_true(is.data.frame(read_builtin("storms", "dplyr")))
  # works if data set package is loaded
  library(dplyr)
  expect_true(is.data.frame(read_builtin("storms")))
})

test_that("read_builtin works", {
  # fails with unquoted symbol
  expect_error(read_builtin(AirPassengers, "datasets"))

  # fails with an error if data set doesn't exist in package
  expect_error(read_builtin("nasa", "readr"))

  # fails with error if the dataset namespace is not attached
  if (!"dplyr" %in% loadedNamespaces()) {
    expect_error(read_builtin("starwars"))
  }

  # works if data set exists in package
  expect_true(is.data.frame(read_builtin("BOD", "datasets")))

  # works if data set package is loaded
  if ("datasets" %in% loadedNamespaces()) {
    expect_true(is.data.frame(read_builtin("BOD")))
  }
})

test_that("check_string() works", {
  expect_null(check_string("string"))
  expect_null(check_string(NULL, optional = TRUE))

  # remove once testthat starts to use rlang 1.0.0 unconditionally if
  # rlang 1.0.0 is indeed installed
  withr::local_options("testthat:::rlang_dep" = "1.0.0")

  expect_snapshot(error = TRUE, {
    name <- 1
    check_string(name)
    check_string(name, nm = "NAME!")
  })
})

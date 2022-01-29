test_that("check_string() works", {
  expect_null(check_string("string"))
  expect_null(check_string(NULL, optional = TRUE))

  expect_snapshot(error = TRUE, {
    name <- 1
    check_string(name)
    check_string(name, nm = "NAME!")
  })
})

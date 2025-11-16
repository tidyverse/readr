test_that("standardise_path works", {
  expect_snapshot(
    standardise_path("https://foo/bar.bz2"),
    error = TRUE
  )
})

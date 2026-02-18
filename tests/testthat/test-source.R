test_that("datasource() treats I() input as literal data", {
  ds <- datasource(I("a,b,c"))
  expect_s3_class(ds, "source_string")

  ds <- datasource(I(c("a,b,c", "1,2,3")))
  expect_s3_class(ds, "source_string")
})

test_that("count_fields() works with I() input (#1581)", {
  expect_equal(
    count_fields(I('"foo","bar","baz"'), tokenizer_csv()),
    3
  )
})

test_that("standardise_path works", {
  expect_snapshot(
    standardise_path("https://foo/bar.bz2"),
    error = TRUE
  )
})

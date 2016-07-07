context("locale")

test_that("setting decimal mark overrides grouping mark", {
  expect_equal(locale(decimal_mark = ".")$grouping_mark, ",")
  expect_equal(locale(decimal_mark = ",")$grouping_mark, ".")
})

test_that("setting grouping mark overrides decimal mark", {
  expect_equal(locale(grouping_mark = ".")$decimal_mark, ",")
  expect_equal(locale(grouping_mark = ",")$decimal_mark, ".")
})

test_that("grouping and decimal marks must be different", {
  expect_error(
    locale(grouping_mark = ".", decimal_mark = "."),
    "must be different"
  )
})

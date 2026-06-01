test_that("setting decimal mark overrides grouping mark", {
  expect_equal(locale(decimal_mark = ".")$grouping_mark, ",")
  expect_equal(locale(decimal_mark = ",")$grouping_mark, ".")
})

test_that("setting grouping mark overrides decimal mark", {
  expect_equal(locale(grouping_mark = ".")$decimal_mark, ",")
  expect_equal(locale(grouping_mark = ",")$decimal_mark, ".")
})

test_that("grouping and decimal marks must be different", {
  expect_snapshot(
    locale(grouping_mark = ".", decimal_mark = "."),
    error = TRUE
  )
})

test_that("locale() accepts date_order parameter", {
  loc <- locale(date_order = "mdy")
  expect_equal(loc$date_order, "mdy")

  loc2 <- locale(date_order = "dmy_hms")
  expect_equal(loc2$date_order, "dmy_hms")

  loc3 <- locale()
  expect_null(loc3$date_order)
})

test_that("locale() rejects invalid date_order", {
  expect_error(locale(date_order = "ymd_xyz"), "date_order")
  expect_error(locale(date_order = "bad"), "date_order")
})

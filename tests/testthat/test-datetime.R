context("datetime")

test_that("utctime is equivalent to R conversion", {
  year <- seq(0, 4000)
  mon <- rep(3, length(year))
  day <- rep(1, length(year))
  zero <- rep(0, length(year))

  expect_equal(
    ISOdatetime(year, mon, day, zero, zero, zero, tz = "UTC"),
    utctime(year, mon, day, zero, zero, zero, zero)
  )

})

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

# Parsing ----------------------------------------------------------------------

r_parse <- function(x, fmt) as.POSIXct(strptime(x, fmt, tz = "UTC"))

test_that("%d, %m and %y", {
  target <- utctime(2010, 2, 3, 0, 0, 0, 0)

  expect_equal(parse_date("10-02-03", "%y-%m-%d"), target)
  expect_equal(parse_date("10-03-02", "%y-%d-%m"), target)
  expect_equal(parse_date("03/02/10", "%d/%m/%y"), target)
  expect_equal(parse_date("02/03/10", "%m/%d/%y"), target)
})

test_that("%y matches R behaviour", {
  expect_equal(
    parse_date("01-01-69", "%d-%m-%y"),
    r_parse("01-01-69", "%d-%m-%y")
  )
  expect_equal(
    parse_date("01-01-68", "%d-%m-%y"),
    r_parse("01-01-68", "%d-%m-%y")
  )
})

test_that("%e allows leading space", {
  expect_equal(parse_date("201010 1", "%Y%m%e"), utctime(2010, 10, 1, 0, 0, 0, 0))
})

test_that("%OS captures partial seconds", {
  x <- parse_date("2001-01-01 00:00:01.125", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.125)

  x <- parse_date("2001-01-01 00:00:01.333", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.333, tol = 1e-6)
})

test_that("invalid dates return NA", {
  expect_true(is.na(parse_date("2010-02-30", "%Y-%m-%d")))
})

test_that("failed parsing returns NA", {
  expect_true(is.na(parse_date("2010-02", "%Y-%m-%d")))
  expect_true(is.na(parse_date("2010-02-ab", "%Y-%m-%d")))
  expect_true(is.na(parse_date("2010/02-ab", "%Y-%m-%d")))
})

test_that("invalid specs returns NA", {
  expect_true(is.na(parse_date("2010-02-02", "%Y-%m-%m")))
})


# Time zones ------------------------------------------------------------------

test_that("same times with different offsets parsed as same time", {
  # From http://en.wikipedia.org/wiki/ISO_8601#Time_offsets_from_UTC
  same_time <- paste("2010-02-03", c("18:30Z", "22:30+04", "1130-0700", "15:00-03:30"))
  parsed <- parse_date(same_time)

  expect_equal(parsed, rep(utctime(2010, 2, 3, 18, 30, 0, 0), 4))
})

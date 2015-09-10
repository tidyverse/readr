context("Parsing, datetime")

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

  expect_equal(parse_datetime("10-02-03", "%y-%m-%d"), target)
  expect_equal(parse_datetime("10-03-02", "%y-%d-%m"), target)
  expect_equal(parse_datetime("03/02/10", "%d/%m/%y"), target)
  expect_equal(parse_datetime("02/03/10", "%m/%d/%y"), target)
})

test_that("Compound formats work", {
  target <- utctime(2010, 2, 3, 0, 0, 0, 0)

  expect_equal(parse_datetime("02/03/10", "%D"), target)
  expect_equal(parse_datetime("2010-02-03", "%F"), target)
  expect_equal(parse_datetime("10/02/03", "%x"), target)
})

test_that("%y matches R behaviour", {
  expect_equal(
    parse_datetime("01-01-69", "%d-%m-%y"),
    r_parse("01-01-69", "%d-%m-%y")
  )
  expect_equal(
    parse_datetime("01-01-68", "%d-%m-%y"),
    r_parse("01-01-68", "%d-%m-%y")
  )
})

test_that("%e allows leading space", {
  expect_equal(parse_datetime("201010 1", "%Y%m%e"), utctime(2010, 10, 1, 0, 0, 0, 0))
})

test_that("%OS captures partial seconds", {
  x <- parse_datetime("2001-01-01 00:00:01.125", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.125)

  x <- parse_datetime("2001-01-01 00:00:01.333", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.333, tol = 1e-6)
})

test_that("invalid dates return NA", {
  expect_true(is.na(parse_datetime("2010-02-30", "%Y-%m-%d")))
})

test_that("failed parsing returns NA", {
  expect_true(is.na(parse_datetime("2010-02", "%Y-%m-%d")))
  expect_true(is.na(parse_datetime("2010-02-ab", "%Y-%m-%d")))
  expect_true(is.na(parse_datetime("2010/02-ab", "%Y-%m-%d")))
})

test_that("invalid specs returns NA", {
  expect_true(is.na(parse_datetime("2010-02-02", "%Y-%m-%m")))
})

test_that("ISO8601 partial dates are not parsed", {
  expect_true(is.na(parse_datetime("20")))
  expect_true(is.na(parse_datetime("2001")))
  expect_true(is.na(parse_datetime("2001-01")))
})

test_that("%p detects AM/PM", {
  am <- parse_datetime(c("2015-01-01 01:00 AM", "2015-01-01 01:00 am"), "%F %R %p")
  pm <- parse_datetime(c("2015-01-01 01:00 PM", "2015-01-01 01:00 pm"), "%F %R %p")

  expect_equal(pm, am + 12 * 3600)
})

test_that("%b and %B are case insensitve", {
  ref <- parse_date("2001-01-01")

  expect_equal(parse_date("2001 JAN 01", "%Y %b %d"), ref)
  expect_equal(parse_date("2001 JANUARY 01", "%Y %B %d"), ref)
})


# Locales -----------------------------------------------------------------

test_that("locale affects months", {
  jan1 <- as.Date("2010-01-01")

  fr <- locale("fr")
  expect_equal(parse_date("1 janv. 2010", "%d %b %Y", locale = fr), jan1)
  expect_equal(parse_date("1 janvier 2010", "%d %B %Y", locale = fr), jan1)
})

test_that("locale affects am/pm", {
  a <- parse_time("1:30 PM", "%H:%M %p")
  b <- parse_time("오후 1시 30분", "%p %H시 %M분", locale = locale("ko"))
  expect_equal(a, b)
})

# Time zones ------------------------------------------------------------------

test_that("same times with different offsets parsed as same time", {
  # From http://en.wikipedia.org/wiki/ISO_8601#Time_offsets_from_UTC
  same_time <- paste("2010-02-03", c("18:30Z", "22:30+04", "1130-0700", "15:00-03:30"))
  parsed <- parse_datetime(same_time)

  expect_equal(parsed, rep(utctime(2010, 2, 3, 18, 30, 0, 0), 4))
})

test_that("offsets can cross date boundaries", {
  expect_equal(
    parse_datetime("2015-01-31T2000-0500"),
    parse_datetime("2015-02-01T0100Z")
  )
})

test_that("unambiguous times with and without daylight savings", {
  melb <- locale(tz = "Australia/Melbourne")
  # Melbourne had daylight savings in 2015 that ended the morning of 2015-04-05
  expect_equal(
    parse_datetime(c("2015-04-04 12:00:00", "2015-04-06 12:00:00"), locale = melb),
    as.POSIXct(c("2015-04-04 12:00:00", "2015-04-06 12:00:00"),
               tz = "Australia/Melbourne")
  )
  # Japan didn't have daylight savings in 2015
  ja <- locale(tz = "Japan")
  expect_equal(
    parse_datetime(c("2015-04-04 12:00:00", "2015-04-06 12:00:00"), locale = ja),
    as.POSIXct(c("2015-04-04 12:00:00", "2015-04-06 12:00:00"), tz = "Japan")
  )
})


# Guessing ---------------------------------------------------------------------

test_that("DDDD-DD not parsed as date (i.e. doesn't trigger partial date match)", {
  expect_equal(collectorGuess(c("1989-90", "1990-91"), locale()), "character")
})

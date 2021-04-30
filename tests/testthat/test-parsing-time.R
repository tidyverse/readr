test_that("default format captures cases", {
  late_night <- hms::hms(seconds = 22 * 3600 + 20 * 60)
  expect_equal(parse_time("22:20"), late_night)
  expect_equal(parse_time("10:20 pm"), late_night)

  expect_equal(parse_time("22:20:05"), hms::as_hms(late_night + 5))
  expect_equal(parse_time("10:20:05 pm"), hms::as_hms(late_night + 5))
})

test_that("twelve o'clock is parsed properly", {
  morning <- hms::hms(seconds = 0 * 3600 + 1 * 60)
  midday <- hms::hms(seconds = 12 * 3600 + 1 * 60)

  expect_equal(parse_time("12:01 AM"), morning)
  expect_equal(parse_time("12:01 PM"), midday)
  expect_equal(parse_time("12:01"), midday)
})

test_that("accepts single digit hour", {
  early_morn <- hms::hms(seconds = 1 * 3600 + 20 * 60)
  expect_equal(parse_time("1:20 am"), early_morn)
})

test_that("parses NA/empty correctly", {
  out <- parse_time(c("NA", ""))
  exp <- hms::hms(seconds = c(NA_real_, NA_real_))
  expect_equal(out, exp)

  expect_equal(
    parse_time("TeSt", na = "TeSt"),
    hms::hms(seconds = NA_real_)
  )
})

test_that("times are guessed as expected", {
  expect_equal(guess_parser("12:01"), "time")

  expect_equal(
    guess_parser("12:01:01"), "time"
  )

  expect_equal(
    guess_parser(c("04:00:00", "04:30:00", "14:00:22")), "time"
  )

  expect_equal(
    guess_parser("25:01:01"), "time"
  )
})

test_that("durations", {
  expect_warning(parse_time("25:00:00", format = "%H:%M:%S"))
  expect_equal(parse_time("25:00:00", format = "%h:%M:%S"), hms::hms(hours = 25))
  expect_equal(parse_time("1000000000:00:00", format = "%h:%M:%S"), hms::hms(hours = 1e9))
  expect_equal(parse_time("-1:23:45", format = "%h:%M:%S"), hms::as_hms(-hms::hms(45, 23, 1)))
  expect_equal(parse_time("-1:23:45.67", format = "%h:%M:%OS"), hms::as_hms(-hms::hms(45.67, 23, 1)))
})

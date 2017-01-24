context("Parsing, time")

test_that("default format captures cases", {
  late_night <- hms::hms(seconds = 22 * 3600 + 20 * 60)
  expect_equal(parse_time("22:20"), late_night)
  expect_equal(parse_time("10:20 pm"), late_night)

  expect_equal(parse_time("22:20:05"), hms::as.hms(late_night + 5))
  expect_equal(parse_time("10:20:05 pm"), hms::as.hms(late_night + 5))
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

  expect_equal(parse_time("TeSt", na = "TeSt"),
    hms::hms(seconds = NA_real_))
})

test_that("times are guessed as expected", {
  expect_equal(guess_parser("12:01"), "time")

  expect_equal(
    guess_parser("12:01:01"), "time")

  expect_equal(
    guess_parser(c("04:00:00", "04:30:00", "14:00:22")), "time")
})

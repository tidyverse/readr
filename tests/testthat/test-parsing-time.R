context("Parsing, time")

test_that("default format captures cases", {
  late_night <- structure(22 * 3600 + 20 * 60, class = "time")
  expect_equal(parse_time("2220"), late_night)
  expect_equal(parse_time("22:20"), late_night)
  expect_equal(parse_time("10:20 pm"), late_night)

  expect_equal(parse_time("222005"), late_night + 5)
  expect_equal(parse_time("22:20:05"), late_night + 5)
  expect_equal(parse_time("10:20:05 pm"), late_night + 5)
})

test_that("parses NA/empty correctly", {
  out <- parse_time(c("NA", ""))
  exp <- structure(c(NA_real_, NA_real_), class = "time")
  expect_equal(out, exp)

  expect_equal(parse_time("TeSt", na = "TeSt"),
    structure(NA_real_, class = "time"))
})

test_that("utctime is equivalent to R conversion", {
  year <- seq(0, 4000)
  mon <- rep(3L, length(year))
  day <- rep(1L, length(year))
  zero_i <- rep(0L, length(year))
  zero_d <- rep(0, length(year))

  expect_equal(
    utctime(year, mon, day, zero_i, zero_i, zero_i, zero_d),
    ISOdatetime(year, mon, day, zero_i, zero_i, zero_i, tz = "UTC")
  )
})

# Parsing ----------------------------------------------------------------------

r_parse <- function(x, fmt) as.POSIXct(strptime(x, fmt, tz = "UTC"))

test_that("%d, %m and %y", {
  target <- utctime(2010L, 2L, 3L, 0L, 0L, 0L, 0)

  expect_equal(parse_datetime("10-02-03", "%y-%m-%d"), target)
  expect_equal(parse_datetime("10-03-02", "%y-%d-%m"), target)
  expect_equal(parse_datetime("03/02/10", "%d/%m/%y"), target)
  expect_equal(parse_datetime("02/03/10", "%m/%d/%y"), target)
})

test_that("Compound formats work", {
  target <- utctime(2010L, 2L, 3L, 0L, 0L, 0L, 0)

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
  expect_equal(
    parse_datetime("201010 1", "%Y%m%e"),
    utctime(2010L, 10L, 1L, 0L, 0L, 0L, 0)
  )
})

test_that("%OS captures partial seconds", {
  x <- parse_datetime("2001-01-01 00:00:01.125", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.125)

  x <- parse_datetime("2001-01-01 00:00:01.333", "%Y-%m-%d %H:%M:%OS")
  expect_equal(as.POSIXlt(x)$sec, 1.333, tolerance = 1e-6)
})

test_that("%y requries 4 digits", {
  expect_warning(parse_date("003-01-01", "%Y-%m-%d"), "parsing failure")
  expect_warning(parse_date("03-01-01", "%Y-%m-%d"), "parsing failure")
  expect_warning(parse_date("00003-01-01", "%Y-%m-%d"), "parsing failure")
})

test_that("invalid dates return NA", {
  expect_warning(x <- parse_datetime("2010-02-30", "%Y-%m-%d"))
  expect_true(is.na(x))
})

test_that("failed parsing returns NA", {
  expect_warning({
    x <- parse_datetime(c("2010-02-ab", "2010-02", "2010/02/01"), "%Y-%m-%d")
  })
  expect_equal(is.na(x), c(TRUE, TRUE, TRUE))
  expect_equal(n_problems(x), 3)
})

test_that("invalid specs returns NA", {
  expect_warning(x <- parse_datetime("2010-02-20", "%Y-%m-%m"))
  expect_equal(is.na(x), TRUE)
  expect_equal(n_problems(x), 1)
})

test_that("ISO8601 partial dates are not parsed", {
  expect_equal(n_problems(parse_datetime("20")), 1)
  expect_equal(n_problems(parse_datetime("2001")), 1)
  expect_equal(n_problems(parse_datetime("2001-01")), 1)
})

test_that("Year only gets parsed", {
  expect_equal(parse_datetime("2010", "%Y"), ISOdate(2010, 1, 1, 0, tz = "UTC"))
  expect_equal(
    parse_datetime("2010-06", "%Y-%m"),
    ISOdate(2010, 6, 1, 0, tz = "UTC")
  )
})

test_that("%p detects AM/PM", {
  am <- parse_datetime(
    c("2015-01-01 01:00 AM", "2015-01-01 01:00 am"),
    "%F %I:%M %p"
  )
  pm <- parse_datetime(
    c("2015-01-01 01:00 PM", "2015-01-01 01:00 pm"),
    "%F %I:%M %p"
  )

  expect_equal(pm, am + 12 * 3600)

  expect_equal(
    parse_datetime("12/31/1991 12:01 AM", "%m/%d/%Y %I:%M %p"),
    POSIXct(694137660, "UTC")
  )

  expect_equal(
    parse_datetime("12/31/1991 12:01 PM", "%m/%d/%Y %I:%M %p"),
    POSIXct(694180860, "UTC")
  )

  expect_equal(
    parse_datetime("12/31/1991 1:01 AM", "%m/%d/%Y %I:%M %p"),
    POSIXct(694141260, "UTC")
  )

  expect_warning(
    x <- parse_datetime(
      c("12/31/1991 00:01 PM", "12/31/1991 13:01 PM"),
      "%m/%d/%Y %I:%M %p"
    )
  )
  expect_equal(n_problems(x), 2)
})

test_that("%b and %B are case insensitve", {
  ref <- parse_date("2001-01-01")

  expect_equal(parse_date("2001 JAN 01", "%Y %b %d"), ref)
  expect_equal(parse_date("2001 JANUARY 01", "%Y %B %d"), ref)
})

test_that("%. requires a value", {
  ref <- parse_date("2001-01-01")
  expect_equal(parse_date("2001?01?01", "%Y%.%m%.%d"), ref)

  expect_warning(
    out <- parse_date("20010101", "%Y%.%m%.%d")
  )
  expect_equal(n_problems(out), 1)
})

test_that("%Z detects named time zones", {
  ref <- POSIXct(1285912800, "America/Chicago")
  ct <- locale(tz = "America/Chicago")

  expect_equal(parse_datetime("2010-10-01 01:00", locale = ct), ref)
  expect_equal(
    parse_datetime(
      "2010-10-01 01:00 America/Chicago",
      "%Y-%m-%d %H:%M %Z",
      locale = ct
    ),
    ref
  )
})

test_that("parse_date returns a double like as.Date()", {
  ref <- parse_date("2001-01-01")

  expect_type(parse_datetime("2001-01-01"), "double")
})

test_that("parses NA/empty correctly", {
  expect_equal(parse_datetime(""), POSIXct(NA_real_))
  expect_equal(parse_date(""), as.Date(NA))

  expect_equal(parse_datetime("NA"), POSIXct(NA_real_))
  expect_equal(parse_date("NA"), as.Date(NA))

  expect_equal(parse_datetime("TeSt", na = "TeSt"), POSIXct(NA_real_))
  expect_equal(parse_date("TeSt", na = "TeSt"), as.Date(NA))
})

# Locales -----------------------------------------------------------------

test_that("locale affects months", {
  jan1 <- as.Date("2010-01-01")

  fr <- locale("fr")
  expect_equal(parse_date("1 janv. 2010", "%d %b %Y", locale = fr), jan1)
  expect_equal(parse_date("1 janvier 2010", "%d %B %Y", locale = fr), jan1)
})

test_that("locale affects day of week", {
  a <- parse_datetime("2010-01-01")
  b <- parse_date("2010-01-01")
  fr <- locale("fr")
  expect_equal(
    parse_datetime("Ven. 1 janv. 2010", "%a %d %b %Y", locale = fr),
    a
  )
  expect_equal(parse_date("Ven. 1 janv. 2010", "%a %d %b %Y", locale = fr), b)
  expect_warning(parse_datetime("Fri 1 janv. 1020", "%a %d %b %Y", locale = fr))
  expect_warning(parse_date("Fri 1 janv. 2010", "%a %d %b %Y", locale = fr))
})

test_that("locale affects am/pm", {
  a <- parse_time("1:30 PM", "%H:%M %p")
  b <- parse_time("오후 1시 30분", "%p %H시 %M분", locale = locale("ko"))
  expect_equal(a, b)
})

test_that("locale affects both guessing and parsing", {
  out <- parse_guess("01/02/2013", locale = locale(date_format = "%m/%d/%Y"))
  expect_equal(out, as.Date("2013-01-02"))
})

test_that("na affects both guessing and parsing (#1041)", {
  out <- parse_guess(c("123", "NA"), na = "NA")
  expect_equal(out, c(123, NA_real_))
})

test_that("text re-encoded before strings are parsed", {
  skip_on_cran() # need to figure out why this fails
  skip_on_os("solaris")

  x <- "1 f\u00e9vrier 2010"
  y <- iconv(x, from = "UTF-8", to = "ISO-8859-1")
  feb01 <- as.Date(ISOdate(2010, 02, 01))

  expect_equal(
    parse_date(x, "%d %B %Y", locale = locale("fr")),
    feb01
  )

  expect_equal(
    parse_date(y, "%d %B %Y", locale = locale("fr", encoding = "ISO-8859-1")),
    feb01
  )
})

# Time zones ------------------------------------------------------------------

test_that("same times with different offsets parsed as same time", {
  # From http://en.wikipedia.org/wiki/ISO_8601#Time_offsets_from_UTC
  same_time <- paste(
    "2010-02-03",
    c("18:30Z", "22:30+04", "1130-0700", "15:00-03:30")
  )
  parsed <- parse_datetime(same_time)

  expect_equal(parsed, rep(utctime(2010L, 2L, 3L, 18L, 30L, 0L, 0), 4))
})

test_that("offsets can cross date boundaries", {
  expect_equal(
    parse_datetime("2015-01-31T2000-0500"),
    parse_datetime("2015-02-01T0100Z")
  )
})

test_that("unambiguous times with and without daylight savings", {
  skip_on_cran() # need to figure out why this fails

  melb <- locale(tz = "Australia/Melbourne")
  # Melbourne had daylight savings in 2015 that ended the morning of 2015-04-05
  expect_equal(
    parse_datetime(
      c("2015-04-04 12:00:00", "2015-04-06 12:00:00"),
      locale = melb
    ),
    POSIXct(c(1428109200, 1428285600), "Australia/Melbourne")
  )
  # Japan didn't have daylight savings in 2015
  ja <- locale(tz = "Japan")
  expect_equal(
    parse_datetime(
      c("2015-04-04 12:00:00", "2015-04-06 12:00:00"),
      locale = ja
    ),
    POSIXct(c(1428116400, 1428289200), "Japan")
  )
})

test_that("ambiguous times always choose the earliest time", {
  ny <- locale(tz = "America/New_York")

  format <- "%Y-%m-%d %H:%M:%S%z"
  expected <- as.POSIXct(
    "1970-10-25 01:30:00-0400",
    tz = "America/New_York",
    format = format
  )

  actual <- parse_datetime("1970-10-25 01:30:00", locale = ny)

  expect_equal(actual, expected)
})

test_that("nonexistent times return NA", {
  ny <- locale(tz = "America/New_York")
  expected <- .POSIXct(NA_real_, tz = "America/New_York")

  actual <- parse_datetime("1970-04-26 02:30:00", locale = ny)

  expect_equal(actual, expected)
})

test_that("can use `tz = ''` for system time zone", {
  withr::local_timezone("Europe/London")

  system <- locale(tz = "")
  expected <- as.POSIXct("1970-01-01 00:00:00", tz = "Europe/London")

  actual <- parse_datetime("1970-01-01 00:00:00", locale = system)

  expect_equal(actual, expected)
})

test_that("can catch faulty system time zones", {
  withr::local_timezone("foo")
  expect_snapshot(locale(tz = ""), error = TRUE)
})


# Guessing ---------------------------------------------------------------------

test_that("DDDD-DD not parsed as date (i.e. doesn't trigger partial date match)", {
  expect_equal(guess_parser(c("1989-90", "1990-91")), "character")
})

test_that("leading zeros don't get parsed as date without explicit separator", {
  expect_equal(guess_parser("00010203"), "character")
  expect_equal(guess_parser("0001-02-03"), "date")
})

test_that("must have either two - or none", {
  expect_equal(guess_parser("2000-10-10"), "date")
  expect_equal(guess_parser("2000-1010"), "character")
  expect_equal(guess_parser("200010-10"), "character")
  expect_equal(guess_parser("20001010"), "double")
})

test_that("Invalid formats error", {
  expect_snapshot(
    parse_date("2020-11-17", "%%Y-%m-%d"),
    error = TRUE
  )
})

# --- date_order tests ---
test_that("guess_parser detects MDY dates with explicit date_order", {
  loc_mdy <- locale(date_order = "mdy")
  expect_equal(
    guess_parser(c("10/02/2024", "03/15/2024"), locale = loc_mdy),
    "date"
  )
})

test_that("guess_parser detects DMY dates with explicit date_order", {
  loc_dmy <- locale(date_order = "dmy")
  expect_equal(
    guess_parser(c("02/10/2024", "15/03/2024"), locale = loc_dmy),
    "date"
  )
})

test_that("guess_parser detects MDY datetime with explicit date_order", {
  loc <- locale(date_order = "mdy_hms")
  expect_equal(guess_parser(c("10/02/2024 14:30:00"), locale = loc), "datetime")
})

test_that("guess_parser auto-detects year-last date without date_order", {
  # 15/03/2024: part1=15 > 12, unambiguously DMY
  expect_equal(guess_parser(c("15/03/2024", "20/01/2024")), "date")
})

test_that("guess_parser auto-detects ambiguous year-last as MDY by default", {
  # 10/02/2024: ambiguous, defaults to MDY — still detected as date
  expect_equal(guess_parser(c("10/02/2024", "03/15/2024")), "date")
})

test_that("parse_date parses MDY with locale date_order", {
  loc <- locale(date_order = "mdy")
  result <- parse_date(c("10/02/2024", "03/15/2024"), locale = loc)
  expect_equal(result, as.Date(c("2024-10-02", "2024-03-15")))
})

test_that("parse_datetime parses dmy_hms with locale date_order", {
  loc <- locale(date_order = "dmy_hms")
  result <- parse_datetime(c("02/10/2024 14:30:00"), locale = loc)
  expect_equal(result, as.POSIXct("2024-10-02 14:30:00", tz = "UTC"))
})

# --- 2-digit-year (M/D/YY) auto-detection ---

test_that("read_csv() auto-detects 2-digit-year MDY dates", {
  csv <- "id,date\n1,5/29/26\n2,5/31/26\n3,12/25/26"
  result <- read_csv(I(csv), show_col_types = FALSE)
  expect_s3_class(result$date, "Date")
  expect_equal(result$date, as.Date(c("2026-05-29", "2026-05-31", "2026-12-25")))
})

test_that("read_csv() auto-detects 2-digit-year DMY dates", {
  # 29 > 12 in the first part: unambiguously day-first
  csv <- "id,date\n1,29/5/26\n2,20/1/26"
  result <- read_csv(I(csv), show_col_types = FALSE)
  expect_s3_class(result$date, "Date")
  expect_equal(result$date, as.Date(c("2026-05-29", "2026-01-20")))
})

test_that("type_convert() materializes year-last dates (guesser and collector agree)", {
  df <- data.frame(date = c("5/29/2026", "3/15/2026"), stringsAsFactors = FALSE)
  result <- type_convert(df, guess_integer = FALSE)
  expect_s3_class(result$date, "Date")
  expect_equal(result$date, as.Date(c("2026-05-29", "2026-03-15")))
})

test_that("read_csv() applies the %y pivot to 2-digit years", {
  csv <- "id,date\n1,5/29/68\n2,5/29/69"
  result <- read_csv(I(csv), show_col_types = FALSE)
  expect_s3_class(result$date, "Date")
  expect_equal(result$date, as.Date(c("2068-05-29", "1969-05-29")))
})

test_that("guess_parser detects 2-digit-year year-last dates", {
  expect_equal(guess_parser(c("5/29/26", "5/31/26"), locale()), "date")
})

test_that("read_csv() does not treat invalid or 3-digit-year values as year-last dates", {
  for (v in c("13/25/26", "100/200/300")) {
    result <- read_csv(I(paste0("x\n", v, "\n")), show_col_types = FALSE)
    expect_type(result$x, "character")
  }
})

test_that("read_csv() auto-detects 2-digit-year MDY datetimes", {
  csv <- "id,dt\n1,5/29/26 14:30:00\n2,12/25/26 23:59:59"
  result <- read_csv(I(csv), show_col_types = FALSE)
  expect_s3_class(result$dt, "POSIXct")
  expect_equal(
    result$dt,
    as.POSIXct(c("2026-05-29 14:30:00", "2026-12-25 23:59:59"), tz = "UTC")
  )
})

test_that("read_csv() auto-detects 4-digit-year MDY datetimes", {
  csv <- "id,dt\n1,5/29/2026 14:30:00\n2,10/15/2024 09:00:00"
  result <- read_csv(I(csv), show_col_types = FALSE)
  expect_s3_class(result$dt, "POSIXct")
  expect_equal(
    result$dt,
    as.POSIXct(c("2026-05-29 14:30:00", "2024-10-15 09:00:00"), tz = "UTC")
  )
})

test_that("parse_date parses 2-digit-year MDY/DMY with locale date_order", {
  expect_equal(
    parse_date("5/29/26", locale = locale(date_order = "mdy")),
    as.Date("2026-05-29")
  )
  expect_equal(
    parse_date("29/5/26", locale = locale(date_order = "dmy")),
    as.Date("2026-05-29")
  )
})

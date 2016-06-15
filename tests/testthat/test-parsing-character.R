context("Parsing, character")

test_that("ws dropped by default", {
  df <- read_csv("x\n a \n    b\n", progress = FALSE)
  expect_equal(df$x, c("a", "b"))
})

test_that("trim_ws = FALSE keeps ws", {
  df <- read_csv("x\n a\nb \n", trim_ws = FALSE, progress = FALSE)
  expect_equal(df$x, c(" a", "b "))
})


# Encoding ----------------------------------------------------------------

test_that("locale encoding affects parsing", {
  x <- c("août", "élève", "ça va")
  # expect_equal(Encoding(x), rep("UTF-8", 3))

  y <- iconv(x, "UTF-8", "latin1")
  # expect_equal(Encoding(x), rep("latin1", 3))

  fr <- locale("fr", encoding = "latin1")
  z <- parse_character(y, locale = fr)
  # expect_equal(Encoding(z), rep("UTF-8", 3))

  # identical coerces encodings to match, so need to compare raw values
  as_raw <- function(x) lapply(x, charToRaw)
  expect_identical(as_raw(x), as_raw(z))
})

test_that("Unicode Byte order marks are stripped from output", {

  # UTF-8
  expect_equal(
    charToRaw(read_lines(
      as.raw(c(0xef, 0xbb, 0xbf, # BOM
          0x41, # A
          0x0A # newline
          )))),
    as.raw(0x41))

  # UTF-16 Big Endian
  expect_equal(
    charToRaw(read_lines(
      as.raw(c(0xfe, 0xff, # BOM
          0x41, # A
          0x0A # newline
          )))),
    as.raw(0x41))

  # UTF-16 Little Endian
  expect_equal(
    charToRaw(read_lines(
      as.raw(c(0xff, 0xfe, # BOM
          0x41, # A
          0x0A # newline
          )))),
    as.raw(0x41))

  # UTF-32 Big Endian
  expect_equal(
    charToRaw(read_lines(
      as.raw(c(0x00, 0x00, 0xfe, 0xff, # BOM
          0x41, # A
          0x0A # newline
          )))),
    as.raw(0x41))

  # UTF-32 Little Endian
  expect_equal(
    charToRaw(read_lines(
      as.raw(c(0xff, 0xfe, 0x00, 0x00, # BOM
          0x41, # A
          0x0A # newline
          )))),
    as.raw(0x41))

  # Vectors shorter than the BOM are handled safely
  expect_equal(charToRaw(read_lines(
        as.raw(c(0xef, 0xbb)))),
    as.raw(c(0xef, 0xbb)))

  expect_equal(charToRaw(read_lines(
        as.raw(c(0xfe)))),
    as.raw(c(0xfe)))

  expect_equal(charToRaw(read_lines(
        as.raw(c(0xff)))),
    as.raw(c(0xff)))
})

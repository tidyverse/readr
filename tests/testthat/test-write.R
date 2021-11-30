test_that("strings are only quoted if needed", {
  x <- c("a", ",")

  csv <- format_delim(data.frame(x), delim = ",", col_names = FALSE)
  expect_equal(csv, 'a\n\",\"\n')
  ssv <- format_delim(data.frame(x), delim = " ", col_names = FALSE)
  expect_equal(ssv, "a\n,\n")
})

test_that("a literal NA is quoted", {
  expect_equal(format_csv(data.frame(x = "NA")), "x\n\"NA\"\n")
})

test_that("na argument modifies how missing values are written", {
  df <- data.frame(x = c(NA, "x", "."), y = c(1, 2, NA))
  expect_equal(format_csv(df, na = "."), "x,y\n.,1\nx,2\n\".\",.\n")
})

test_that("read_delim/csv/tsv and write_delim round trip special chars", {
  x <- c("a", '"', ",", "\n", "at\t")

  output <- data.frame(x)
  input <- read_delim(I(format_delim(output, delim = " ")), delim = " ", trim_ws = FALSE)
  input_csv <- read_csv(I(format_delim(output, delim = ",")), trim_ws = FALSE)
  input_tsv <- read_tsv(I(format_delim(output, delim = "\t")), trim_ws = FALSE)
  expect_equal(input$x, input_csv$x)
  expect_equal(input_tsv$x, x)
})

test_that("special floating point values translated to text", {
  df <- data.frame(x = c(NaN, NA, Inf, -Inf))
  expect_equal(format_csv(df), "x\nNA\nNA\nInf\n-Inf\n")
})

test_that("logical values give long names", {
  df <- data.frame(x = c(NA, FALSE, TRUE))
  expect_equal(format_csv(df), "x\nNA\nFALSE\nTRUE\n")
})

test_that("roundtrip preserved floating point numbers", {
  input <- data.frame(x = runif(100))
  output <- read_delim(I(format_delim(input, delim = " ")), delim = " ")

  expect_equal(input$x, output$x)
})

test_that("roundtrip preserves dates and datetimes", {
  x <- as.Date("2010-01-01") + 1:10
  y <- as.POSIXct(x)
  attr(y, "tzone") <- "UTC"

  input <- data.frame(x, y)
  output <- read_delim(I(format_delim(input, delim = ",")), delim = ",")

  expect_equal(output$x, x)
  expect_equal(output$y, y)
})

test_that("fails to create file in non-existent directory", {
  expect_error(
    expect_warning(
      write_csv(mtcars, file.path(tempdir(), "/x/y")), "open"
    )
  )
})

test_that("write_excel_csv/csv2 includes a byte order mark", {
  skip_if_edition_first()
  tmp <- tempfile()
  on.exit(unlink(tmp))

  tmp2 <- tempfile()
  on.exit(unlink(tmp2))

  write_excel_csv(mtcars, tmp)
  write_excel_csv2(mtcars, tmp2)

  output <- readBin(tmp, "raw", file.info(tmp)$size)
  output2 <- readBin(tmp2, "raw", file.info(tmp2)$size)

  # BOM is there
  expect_equal(output[1:3], charToRaw("\xEF\xBB\xBF"))
  expect_equal(output2[1:3], charToRaw("\xEF\xBB\xBF"))

  # Rest of file also there
  expect_equal(output[4:8], charToRaw('"mpg"'))
  expect_equal(output2[4:8], charToRaw('"mpg"'))
})

test_that("write_excel_csv/csv2 includes a byte order mark, but not when appending", {
  skip_if_edition_first()
  tmp <- tempfile()
  on.exit(unlink(tmp))

  write_excel_csv(data.frame(a = 1), tmp)
  write_excel_csv(data.frame(a = 2), tmp, append = TRUE)
  output <- readBin(tmp, "raw", file.info(tmp)$size)

  expect_equal(output[1:3], charToRaw("\xEF\xBB\xBF"))

  # But not in the rest of the file
  expect_equal(output[-1:-3], charToRaw('"a"\n1\n2\n'))
})

test_that("does not writes a tailing .0 for whole number doubles", {
  expect_equal(format_tsv(tibble::tibble(x = 1)), "x\n1\n")

  expect_equal(format_tsv(tibble::tibble(x = 0)), "x\n0\n")

  expect_equal(format_tsv(tibble::tibble(x = -1)), "x\n-1\n")

  expect_equal(format_tsv(tibble::tibble(x = 999)), "x\n999\n")

  expect_equal(format_tsv(tibble::tibble(x = -999)), "x\n-999\n")

  expect_equal(format_tsv(tibble::tibble(x = 123456789)), "x\n123456789\n")

  expect_equal(format_tsv(tibble::tibble(x = -123456789)), "x\n-123456789\n")
})

test_that("write_csv can write to compressed files", {
  mt <- read_csv(readr_example("mtcars.csv.bz2"))

  filename <- file.path(tempdir(), "mtcars.csv.bz2")
  on.exit(unlink(filename))
  write_csv(mt, filename)

  expect_true(is_bz2_file(filename))
  expect_equal(mt, read_csv(filename))
})

test_that("write_csv writes large integers without scientific notation #671", {
  x <- data.frame(a = c(60150001022000, 60150001022001))
  filename <- file.path(tempdir(), "test_large_integers.csv")
  on.exit(unlink(filename))
  write_csv(x, filename)
  content <- read_file(filename)
  expect_equal(content, "a\n60150001022000\n60150001022001\n")
})

test_that("write_csv writes large integers without scientific notation up to 1E15 #671", {
  x <- data.frame(a = c(1E13, 1E14, 1E15, 1E16))
  filename <- file.path(tempdir(), "test_large_integers2.csv")
  on.exit(unlink(filename))
  write_csv(x, filename)
  content <- read_file(filename)
  expect_equal(content, "a\n10000000000000\n100000000000000\n1e15\n1e16\n")
  x_exp <- read_csv(filename, col_types = "d")
  expect_equal(x$a, x_exp$a)
})

test_that("write_csv2 and format_csv2 writes ; sep and , decimal mark", {
  df <- tibble::tibble(x = c(0.5, 2, 1.2), y = c("a", "b", "c"))
  expect_equal(format_csv2(df), "x;y\n0,5;a\n2,0;b\n1,2;c\n")

  filename <- tempfile(pattern = "readr", fileext = ".csv")
  on.exit(unlink(filename))
  write_csv2(df, filename)

  expect_equal(c(df), suppressMessages(c(read_csv2(filename))))
})

test_that("write_csv2 and format_csv2 writes NA appropriately", {
  df <- tibble::tibble(x = c(0.5, NA, 1.2), y = c("a", "b", NA))
  expect_equal(format_csv2(df), "x;y\n0,5;a\nNA;b\n1,2;NA\n")
})

test_that("write_csv2 and format_csv2 produce no leading whitespace for numbers", {
  df <- tibble::tibble(x = c(6, 66))
  expect_equal(format_csv2(df), "x\n6\n66\n")
})

test_that("write_csv2 and format_csv2 use same precision as write.csv2 (#1087)", {
  tmp <- tempfile()
  on.exit(unlink(tmp), add = TRUE)

  df <- tibble::tibble(x = c(1234567.1), y = 5)

  con <- file(tmp, "wb")
  write.csv2(df, con, row.names = FALSE, quote = FALSE, eol = "\n")
  close(con)

  expect_equal(format_csv2(df), "x;y\n1234567,1;5\n")
  expect_equal(format_csv2(df), read_file(tmp))
})

test_that("Can change the escape behavior for quotes", {
  df <- data.frame(x = c("a", '"', ",", "\n"))

  expect_error(format_delim(df, "\t", escape = "invalid"), "should be one of")

  expect_equal(format_delim(df, "\t"), "x\na\n\"\"\"\"\n,\n\"\n\"\n")
  expect_equal(format_delim(df, "\t", escape = "double"), "x\na\n\"\"\"\"\n,\n\"\n\"\n")
  expect_equal(format_delim(df, "\t", escape = "backslash"), "x\na\n\"\\\"\"\n,\n\"\n\"\n")
  expect_equal(format_delim(df, "\t", escape = "none"), "x\na\n\"\"\"\n,\n\"\n\"\n")
})

test_that("hms NAs are written without padding (#930)", {
  df <- data.frame(x = hms::as_hms(c(NA, 34.234)))
  expect_equal(format_tsv(df), "x\nNA\n00:00:34.234\n")
})

test_that("Error when writing list columns or matrix columns", {
  df <- data.frame(x = LETTERS[1:4], y = I(list(1, "foo", 2:9, iris)), z = I(matrix(1:16, nrow = 4)))
  expect_error(
    write_csv(df, tempfile()),
    "`x` must not contain list or matrix columns"
  )

  df2 <- data.frame(x = LETTERS[1:4], y = I(matrix(1:40, nrow = 4)))
  expect_error(
    write_csv(df2, tempfile()),
    "`x` must not contain list or matrix columns"
  )
})

test_that("duplicate columns data is duplicated (#1169)", {
  df <- tibble::tibble(x = 1, x2 = 2)
  names(df) <- c("x", "x")

  f <- tempfile()
  on.exit(unlink(f))

  write_csv(df, f)

  expect_equal(readLines(f), c("x,x", "1,2"))
})

test_that("write_ family of functions return input data frame without changes", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  time_strings <- c("2019-11-14 15:44:00", "2019-11-14 15:47:00")
  times <- as.POSIXlt(time_strings, tz = "America/Los_Angeles")
  df <- data.frame(time = times, class = factor(c("a", "b")))

  df_delim <- write_delim(df, tmp)
  expect_identical(df, df_delim)

  df_csv <- write_csv(df, tmp)
  expect_identical(df, df_csv)

  df_csv2 <- write_csv2(df, tmp)
  expect_identical(df, df_csv2)

  df_excel_csv <- write_excel_csv(df, tmp)
  expect_identical(df, df_excel_csv)

  df_excel_csv2 <- write_excel_csv2(df, tmp)
  expect_identical(df, df_excel_csv2)

  df_tsv <- write_tsv(df, tmp)
  expect_identical(df, df_tsv)
})

test_that("write_*() supports writing with windows newlines", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  write_delim(data.frame(x = 1:3), tmp, eol = "\r\n")

  expect_identical(
    readBin(tmp, file.info(tmp)$size, what = "raw"),
    charToRaw("x\r\n1\r\n2\r\n3\r\n")
  )
})

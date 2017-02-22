context("write_delim")

test_that("strings are only quoted if needed", {
  x <- c("a", ',')

  csv <- format_delim(data.frame(x), delim = ",",col_names = FALSE)
  expect_equal(csv, 'a\n\",\"\n')
  ssv <- format_delim(data.frame(x), delim = " ",col_names = FALSE)
  expect_equal(ssv, 'a\n,\n')
})

test_that("a literal NA is quoted", {
  expect_equal(format_csv(data.frame(x = "NA")), "x\n\"NA\"\n")
})

test_that("na argument modifies how missing values are written", {
  df <- data.frame(x = c(NA, "x", "."))
  expect_equal(format_csv(df, na = "."), "x\n.\nx\n\".\"\n")
})

test_that("read_delim/csv/tsv and write_delim round trip special chars", {
  x <- c("a", '"', ",", "\n","at\t")

  output <- data.frame(x)
  input <- read_delim(format_delim(output, delim = " "), delim = " ", progress = FALSE)
  input_csv <- read_csv(format_delim(output, delim = ","), progress = FALSE)
  input_tsv <- read_tsv(format_delim(output, delim = "\t"), progress = FALSE)
  expect_equal(input$x, input_csv$x, input_tsv$x,  x)
})

test_that("special floating point values translated to text", {
  df <- data.frame(x = c(NaN, NA, Inf, -Inf))
  expect_equal(format_csv(df), "x\nNaN\nNA\nInf\n-Inf\n")
})

test_that("logical values give long names", {
  df <- data.frame(x = c(NA, FALSE, TRUE))
  expect_equal(format_csv(df), "x\nNA\nFALSE\nTRUE\n")
})

test_that("roundtrip preserved floating point numbers", {
  input <- data.frame(x = runif(100))
  output <- read_delim(format_delim(input, delim = " "), delim = " ", progress = FALSE)

  expect_equal(input$x, output$x)
})

test_that("roundtrip preserves dates and datetimes", {
  x <- as.Date("2010-01-01") + 1:10
  y <- as.POSIXct(x)
  attr(y, "tzone") <- "UTC"

  input <- data.frame(x, y)
  output <- read_delim(format_delim(input, delim = " "), delim = " ", progress = FALSE)

  expect_equal(output$x, x)
  expect_equal(output$y, y)
})

test_that("fails to create file in non-existent directory", {
  expect_warning(expect_error(write_csv(mtcars, file.path(tempdir(), "/x/y")), "cannot open the connection"), "No such file or directory")
})

test_that("write_excel_csv includes a byte order mark", {
  tmp <- tempfile()
  on.exit(unlink(tmp))

  write_excel_csv(mtcars, tmp)

  output <- readBin(tmp, "raw", file.info(tmp)$size)

  # BOM is there
  expect_equal(output[1:3], charToRaw("\xEF\xBB\xBF"))

  # Rest of file also there
  expect_equal(output[4:6], charToRaw("mpg"))
})


test_that("does not writes a tailing .0 for whole number doubles", {
  expect_equal(format_tsv(tibble::data_frame(x = 1)), "x\n1\n")

  expect_equal(format_tsv(tibble::data_frame(x = 0)), "x\n0\n")

  expect_equal(format_tsv(tibble::data_frame(x = -1)), "x\n-1\n")

  expect_equal(format_tsv(tibble::data_frame(x = 999)), "x\n999\n")

  expect_equal(format_tsv(tibble::data_frame(x = -999)), "x\n-999\n")

  expect_equal(format_tsv(tibble::data_frame(x = 123456789)), "x\n123456789\n")

  expect_equal(format_tsv(tibble::data_frame(x = -123456789)), "x\n-123456789\n")
})

test_that("write_csv can write to compressed files", {
  mt <- read_csv(readr_example("mtcars.csv.bz2"))

  filename <- file.path(tempdir(), "mtcars.csv.bz2")
  on.exit(unlink(filename))
  write_csv(mt, filename)

  expect_true(is_bz2_file(filename))
  expect_equal(mt, read_csv(filename))
})

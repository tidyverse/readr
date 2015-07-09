context("write_delim")

test_that("strings are only quoted if needed", {
  x <- c("a", ',')

  csv <- write_delim(data.frame(x), "", delim = ",",col_names = FALSE)
  expect_equal(csv, 'a\n\",\"\n')
  ssv <- write_delim(data.frame(x), "", delim = " ",col_names = FALSE)
  expect_equal(ssv, 'a\n,\n')
})

test_that("read_delim/csv/tsv and write_delim round trip special chars", {
  x <- c("a", '"', ",", "\n","at\t")

  output <- data.frame(x)
  input <- read_delim(write_delim(output, "", delim = " "), delim = " ")
  input_csv <- read_csv(write_delim(output, "", delim = ","))
  input_tsv <- read_tsv(write_delim(output, "", delim = "\t"))
  expect_equal(input$x, input_csv$x, input_tsv$x,  x)
})

test_that("roundtrip preserved floating point numbers", {
  input <- data.frame(x = runif(100))
  output <- read_delim(write_delim(input, "", delim = " "), delim = " ")

  expect_equal(input$x, output$x)
})

test_that("roundtrip preserves dates and datetimes", {
  x <- as.Date("2010-01-01") + 1:10
  y <- as.POSIXct(x)
  attr(y, "tzone") <- "UTC"

  input <- data.frame(x, y)
  output <- read_delim(write_delim(input, "", delim = " "), delim = " ")

  expect_equal(output$x, x)
  expect_equal(output$y, y)
})

test_that("fails to create file in non-existent direction", {
  expect_error(write_csv(mtcars, file.path(tempdir(), "/x/y")), "Failed to open")
})

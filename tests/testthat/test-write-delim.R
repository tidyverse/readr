context("write_delim")

test_that("strings are only quoted if needed", {
  x <- c("a", ',')

  csv <- write_delim(data.frame(x), "", delim = " ",col_names = FALSE)
  expect_equal(csv, 'a\n,\n')
})

test_that("read_delim and write_delim round trip special chars", {
  x <- c("a", '"', ",", "\n","at\t")

  output <- data.frame(x)
  input <- read_delim(write_delim(output, "", delim = " "), delim = " ")

  expect_equal(input$x, x)
})

test_that("roundtrip preserved floating point numbers", {
  input <- data.frame(x = runif(100))
  output <- read_delim(write_delim(input, ""), delim = " ")

  expect_equal(input$x, output$x)
})

test_that("roundtrip preserves dates and datetimes", {
  x <- as.Date("2010-01-01") + 1:10
  y <- as.POSIXct(x)
  attr(y, "tzone") <- "UTC"

  input <- data.frame(x, y)
  output <- read_delim(write_delim(input, ""), delim = " ")

  expect_equal(output$x, x)
  expect_equal(output$y, y)
})

context("write_tsv")

test_that("strings are only quoted if needed", {
  x <- c("a", ',', "at\t")

  tsv <- write_tsv(data.frame(x), "", col_names = FALSE)
  expect_equal(tsv, 'a\n\",\"\n\"at\t\"\n')
})

test_that("read_tsv and write_tsv round trip special chars", {
  x <- c("a", '"', ",", "\n", "at\t")

  output <- data.frame(x)
  input <- read_tsv(write_tsv(output, ""))

  expect_equal(input$x, x)
})

test_that("roundtrip preserved floating point numbers", {
  input <- data.frame(x = runif(100))
  output <- read_tsv(write_tsv(input, ""))

  expect_equal(input$x, output$x)
})

test_that("roundtrip preserves dates and datetimes", {
  x <- as.Date("2010-01-01") + 1:10
  y <- as.POSIXct(x)
  attr(y, "tzone") <- "UTC"

  input <- data.frame(x, y)
  output <- read_tsv(write_tsv(input, ""))

  expect_equal(output$x, x)
  expect_equal(output$y, y)
})

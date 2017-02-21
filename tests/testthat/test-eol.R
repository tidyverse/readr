context("EOL")

if (FALSE) {
  df <- data.frame(x = 1:3, y = letters[1:3], stringsAsFactors = FALSE)
  write.csv(df, "tests/testthat/eol-lf.csv", row.names = FALSE, eol = "\n")
  write.csv(df, "tests/testthat/eol-cr.csv", row.names = FALSE, eol = "\r")
  write.csv(df, "tests/testthat/eol-crlf.csv", row.names = FALSE, eol = "\r\n")

  write.fwf <- function(x, path, ...) {
    write.table(x, path, row.names = FALSE, quote = FALSE)
  }
  write.fwf(df, "tests/testthat/eol-lf.txt", row.names = FALSE, eol = "\n")
  write.fwf(df, "tests/testthat/eol-cr.txt", row.names = FALSE, eol = "\r")
  write.fwf(df, "tests/testthat/eol-crlf.txt", row.names = FALSE, eol = "\r\n")
}

test_that("read_csv standardises line breaks", {
  expect_equal(read_csv("eol-lf.csv", progress = FALSE)$y, letters[1:3])
  expect_equal(read_csv("eol-cr.csv", progress = FALSE)$y, letters[1:3])
  expect_equal(read_csv("eol-crlf.csv", progress = FALSE)$y, letters[1:3])
})

test_that("read_lines standardises line breaks", {
  lf <- read_lines("eol-lf.csv", progress = FALSE)
  expect_equal(read_lines("eol-cr.csv", progress = FALSE), lf)
  expect_equal(read_lines("eol-crlf.csv", progress = FALSE), lf)
})

test_that("read_fwf/read_table standardises line breaks", {
  expect_equal(read_table("eol-lf.txt", progress = FALSE)$y, letters[1:3])
  expect_equal(read_table("eol-cr.txt", progress = FALSE)$y, letters[1:3])
  expect_equal(read_table("eol-crlf.txt", progress = FALSE)$y, letters[1:3])
})

test_that("read_table2 standardises line breaks", {
  expect_equal(read_table2("eol-lf.txt", progress = FALSE)$y, letters[0:3])
  expect_equal(read_table2("eol-cr.txt", progress = FALSE)$y, letters[1:3])
  expect_equal(read_table2("eol-crlf.txt", progress = FALSE)$y, letters[1:3])
})

context("EOL")

if (FALSE) {
  df <- data.frame(x = 1:3, y = letters[1:3], stringsAsFactors = FALSE)
  write.csv(df, "tests/testthat/eol-lf.csv", row.names = FALSE, eol = "\n")
  write.csv(df, "tests/testthat/eol-cr.csv", row.names = FALSE, eol = "\r")
  write.csv(df, "tests/testthat/eol-crlf.csv", row.names = FALSE, eol = "\r\n")
}

test_that("read_csv standardises line breaks", {
  expect_equal(read_csv("eol-lf.csv")$y, letters[1:3])
  expect_equal(read_csv("eol-cr.csv")$y, letters[1:3])
  expect_equal(read_csv("eol-crlf.csv")$y, letters[1:3])
})

test_that("read_lines standardises line breaks", {
  lf <- read_lines("eol-lf.csv")
  expect_equal(read_lines("eol-cr.csv"), lf)
  expect_equal(read_lines("eol-crlf.csv"), lf)
})

context("read_file")

# df <- dplyr::data_frame(français = "élève")
# write.csv(df,
#   "tests/testthat/enc-iso-8859-1.txt",
#   fileEncoding = "ISO-8859-1",
#   row.names = FALSE,
#   quote = FALSE)

test_that("read_file respects encoding", {
  x <- read_file("enc-iso-8859-1.txt", locale(encoding = "ISO-8859-1"))
  expect_equal(substr(x, 5, 5), "\u00e7")
})

sample_text_str <- "abc\n123" # contents of sample_text.txt
eol_cr_text <- "x y\n1 a\n2 b\n3 c\n" # contents of eol_cr.txt

test_that("read_file works with a local text file passed as character", {
  expect_equal(read_file("sample_text.txt"), sample_text_str)
})

test_that("read_file works with a local text file, skipping one line", {
  expect_equal(
    read_file(datasource("sample_text.txt", skip = 1)),
    paste(tail(strsplit(sample_text_str,"\n")[[1]], -1), collapse = "\n")
  )
})

test_that("read_file works with a character datasource", {
  expect_equal(read_file(sample_text_str), sample_text_str)
})

test_that("read_file works with a connection to a local file", {
  con <- file("sample_text.txt", "rb")
  on.exit(close(con), add = TRUE)
  expect_equal(read_file(con), sample_text_str)
})

test_that("read_file works with a raw datasource", {
  expect_equal(read_file(charToRaw(sample_text_str)), sample_text_str)
})

test_that("read_file works with compressed files", {
  expect_equal(read_file("eol-cr.txt.gz"), eol_cr_text)
  expect_equal(read_file("eol-cr.txt.bz2"), eol_cr_text)
  expect_equal(read_file("eol-cr.txt.xz"), eol_cr_text)
  expect_equal(read_file("eol-cr.txt.zip"), eol_cr_text)
})

test_that("read_file works via https", {
  url <- "https://raw.githubusercontent.com/tidyverse/readr/master/tests/testthat/eol-cr.txt"
  expect_equal(read_file(url), eol_cr_text)
})

test_that("read_file works via https on gz file", {
  url <- "https://raw.githubusercontent.com/tidyverse/readr/master/tests/testthat/eol-cr.txt.gz"
  expect_equal(read_file(url), eol_cr_text)
})

test_that("read_file returns \"\" on an empty file", {
   expect_equal(read_file("empty-file"), "")
})

# read_file_raw ---------------------------------------------------------------

test_that("read_file_raw works with a local text file", {
  expect_equal(read_file_raw("sample_text.txt"), charToRaw("abc\n123"))
})

test_that("read_file_raw works with a character datasource", {
  expect_equal(read_file_raw("abc\n123"), charToRaw("abc\n123"))
})

test_that("read_file_raw returns raw() on an empty file", {
  expect_equal(read_file_raw("empty-file"), raw())
})

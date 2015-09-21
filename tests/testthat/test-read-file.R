context("read_file")

test_that("read_file respects encoding", {
  x <- read_file("enc-iso-8859-1.txt", locale(encoding = "ISO-8859-1"))
  expect_equal(substr(x, 5, 5), "ç")
})

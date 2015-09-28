context("read_lines")

test_that("read_lines respects encoding", {
  x <- read_lines("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"))
  expect_equal(x, c("fran\u00e7ais", "\u00e9l\u00e8ve"))
})

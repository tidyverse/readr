context("read_file")

# df <- dplyr::data_frame(français = "élève")
# write.csv(df,
#   "tests/testthat/enc-iso-8859-1.txt",
#   fileEncoding = "ISO-8859-1",
#   row.names = FALSE,
#   quote = FALSE)

test_that("read_file respects encoding", {
  x <- read_file("enc-iso-8859-1.txt", locale(encoding = "ISO-8859-1"))
  expect_equal(substr(x, 5, 5), "ç")
})

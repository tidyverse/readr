context("read file")

test_that( "read_file works", {
  file <- file.path(R.home("doc"), "COPYING")

  read_file1 <- function(path) {
    paste0(paste0(readLines(path), collapse = "\n"), "\n")
  }
  expect_equal(
    gsub("\r", "", read_file(file)), # needed for testing on windows...
    read_file1(file)
  )

})


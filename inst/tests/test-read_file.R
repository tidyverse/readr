context("read file")

test_that( "read_file works", {
  file <- file.path(R.home("doc"), "COPYING")
  
  read_file1 <- function(path) {
    paste0(paste0(readLines(path), collapse = "\n"), "\n")
  }
  expect_equal( 
    read_file(file), 
    read_file1(file) 
  ) 
  
})


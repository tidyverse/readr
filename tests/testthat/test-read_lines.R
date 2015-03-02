context("read lines")

test_that( "read_lines works", {
  file <- file.path(R.home("doc"), "COPYING")
  
  expect_equal( 
    readLines(file), 
    read_lines(file) 
  ) 
  
})


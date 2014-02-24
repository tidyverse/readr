context("parse_text")

test_that( "parser skips quotes and spaces", {
  expect_equal( parse_text( "'1.0'", "double" ), 1.0 )
  expect_equal( parse_text( '"1.0"', "double" ), 1.0 )
  expect_equal( parse_text( ' " 1.0"', "double" ), 1.0 )
  
  expect_equal( parse_text( "'1'", "int" ), 1L )
  expect_equal( parse_text( '"1"', "int" ), 1L )
  expect_equal( parse_text( ' " 1"', "int" ), 1L )
  
})


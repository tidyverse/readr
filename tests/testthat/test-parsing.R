context("Parsing")

test_that("trimmed before NA detection", {
  expect_equal(parse_logical(c(" TRUE ", "FALSE", " NA ")), c(TRUE, FALSE, NA))
})

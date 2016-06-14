context("Parsing, deparsed")

test_that("parsing failures fail", {
  expect_error(parse_deparsed("list(1"))
  expect_error(parse_deparsed("{c(1)"))
})

test_that("parsing evaluates the expressions", {
  t1 <- paste(collapse = "", deparse(head(iris)))
  expect_equal(parse_deparsed(c("c(1, 2, 3)", t1)),
      list(c(1, 2, 3),
        head(iris)))
})

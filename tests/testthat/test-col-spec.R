context("col_spec")

test_that("supplied col names must match non-skipped col types", {
  out <- col_spec_standardise(col_types = "c_c", col_names = c("a", "c"))
  expect_equal(names(out), c("a", "", "c"))
})

test_that("supplied col names matches to non-skipped col types", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = "i_i")
  expect_equal(names(out), c("a", "b", "c"))
})

test_that("guess col names matches all col types", {
  out <- col_spec_standardise("a,b,c\n", col_types = "i_i")
  expect_equal(names(out), c("a", "b", "c"))
  expect_equal(out[[2]], col_skip())
})

test_that("col_names expanded to col_types with dummy names", {
  expect_warning(
    out <- col_spec_standardise("1,2,3\n", c("a", "b"), "iii"),
    "Insufficient `col_names`"
  )
  expect_equal(names(out), c("a", "b", "X3"))
})

test_that("col_types expanded to col_names by guessing", {
  expect_warning(
    out <- col_spec_standardise("1,2,3\n", c("a", "b", "c"), "ii"),
    "Insufficient `col_types`"
  )
  expect_equal(names(out), c("a", "b", "c"))
  expect_equal(out[[3]], col_integer())
})

test_that("defaults expanded to match names", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = cols(.default = "c"))
  expect_equal(out, list(
    a = col_character(),
    b = col_character(),
    c = col_character()
  ))
})

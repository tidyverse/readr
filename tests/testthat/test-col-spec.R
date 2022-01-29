test_that("supplied col names must match non-skipped col types", {
  out <- col_spec_standardise(col_types = "c_c", col_names = c("a", "c"))
  expect_equal(names(out[[1]]), c("a", "", "c"))
})

test_that("supplied col names matches to non-skipped col types", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = "i_i")
  expect_equal(names(out[[1]]), c("a", "b", "c"))
})

test_that("guess col names matches all col types", {
  out <- col_spec_standardise("a,b,c\n", col_types = "i_i")
  expect_equal(names(out[[1]]), c("a", "b", "c"))
  expect_equal(out[[1]][[2]], col_skip())
})

test_that("col_names expanded to col_types with dummy names", {
  expect_warning(
    out <- col_spec_standardise("1,2,3,4\n", c("a", "b"), "iiii"),
    "Insufficient `col_names`"
  )
  expect_equal(names(out[[1]]), c("a", "b", "X3", "X4"))
})

test_that("col_names expanded to match col_types, with skipping", {
  expect_warning(
    out <- col_spec_standardise(col_types = "c_c", col_names = "a"),
    "Insufficient `col_names`"
  )
  expect_equal(names(out[[1]]), c("a", "", "X2"))
})

test_that("col_types expanded to col_names by guessing", {
  skip_if(edition_first())
  expect_warning(
    out <- col_spec_standardise("1,2,3\n", c("a", "b", "c"), "ii"),
    "Insufficient `col_types`"
  )
  expect_equal(names(out[[1]]), c("a", "b", "c"))
  expect_equal(out[[1]][[3]], col_double())
})

test_that("defaults expanded to match names", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = cols(.default = "c"))
  expect_equal(out[[1]], list(
    a = col_character(),
    b = col_character(),
    c = col_character()
  ))
})

test_that("col_spec_standardise works properly with 1 row inputs and no header columns (#333)", {
  expect_s3_class(col_spec_standardise("1\n", col_names = FALSE)[[1]]$X1, "collector_double")
})

test_that("warns about duplicated names", {
  expect_warning(col_spec_standardise("a,a\n1,2"), "Duplicated column names")
  expect_warning(
    col_spec_standardise("1,2\n1,2", col_names = c("X", "X")),
    "Duplicated column names"
  )
})

test_that("warn about missing col names and fill in", {
  expect_warning(col_spec_standardise(",\n1,2"), "Missing column names")
  expect_warning(
    col_spec_standardise("1,2\n1,2", col_names = c("X", NA)),
    "Missing column names"
  )
})

test_that("spec object attached to read data", {
  skip_if(edition_first())

  test_data <- read_csv(test_path("basic-df.csv"), col_types = NULL, col_names = TRUE)
  sp <- spec(test_data)
  sp$skip <- NULL

  expect_equal(
    sp,
    cols(
      .delim = ",",
      a = col_logical(),
      b = col_double(),
      c = col_double(),
      d = col_character()
    )
  )
})

test_that("guess_types errors on invalid inputs", {
  expect_error(col_spec_standardise("a,b,c\n", guess_max = NA), "`guess_max` must be a positive integer")
  expect_error(col_spec_standardise("a,b,c\n", guess_max = -1), "`guess_max` must be a positive integer")

  expect_warning(col_spec_standardise("a,b,c\n", guess_max = Inf), "`guess_max` is a very large value")
})

test_that("check_guess_max errors on invalid inputs", {
  expect_error(check_guess_max(NULL), "`guess_max` must be a positive integer")
  expect_error(check_guess_max("test"), "`guess_max` must be a positive integer")
  expect_error(check_guess_max(letters), "`guess_max` must be a positive integer")
  expect_error(check_guess_max(1:2), "`guess_max` must be a positive integer")
  expect_error(check_guess_max(NA), "`guess_max` must be a positive integer")
  expect_error(check_guess_max(-1), "`guess_max` must be a positive integer")

  expect_warning(check_guess_max(Inf), "`guess_max` is a very large value")
})

test_that("as.col_types can handle named character input", {
  expect_equal(as.col_spec(c(a = "c")), cols(a = col_character()))
})

test_that("as.col_types can convert data.frame", {
  spec <- as.col_spec(iris)
  exp <- cols(
    Sepal.Length = col_double(),
    Sepal.Width = col_double(),
    Petal.Length = col_double(),
    Petal.Width = col_double(),
    Species = col_factor(levels = c("setosa", "versicolor", "virginica"), ordered = FALSE, include_na = FALSE)
  )
  expect_equal(spec, exp)
})

test_that("as.character() works on col_spec objects", {
  spec <- as.col_spec(iris)
  expect_equal(as.character(spec), "ddddf")
})

# Printing ----------------------------------------------------------------

test_that("print(col_spec) with guess_parser", {
  expect_snapshot(col_spec_standardise("a,b,c\n1,2,3"))
})

test_that("print(col_spec) with collector_skip", {
  expect_snapshot(cols_only(a = col_integer(), c = col_integer()))
})

test_that("print(col_spec) with truncated output", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = cols(.default = "c"))
  expect_snapshot(
    print(out, n = 2, condense = FALSE)
  )
})

test_that("print(col_spec) works with dates", {
  out <- col_spec_standardise("a,b,c\n",
    col_types = cols(
      a = col_date(format = "%Y-%m-%d"),
      b = col_date(),
      c = col_date()
    )
  )
  expect_snapshot(out)
})

test_that("print(col_spec) with unnamed columns", {
  expect_snapshot(
    col_spec_standardise(col_types = "c_c", col_names = c("a", "c"))
  )
})

test_that("print(cols_only()) prints properly", {
  expect_snapshot(
    cols_only(a = col_character(), c = col_integer())
  )
})

test_that("print(col_spec) with n == 0 prints nothing", {
  expect_silent(print(col_spec_standardise("a,b,c\n1,2,3"), n = 0))
})

test_that("print(cols_condense(col_spec)) condenses the spec", {
  expect_snapshot(
    cols_condense(col_spec_standardise("a,b,c,d\n1,2,3,a"))
  )
  expect_snapshot(
    cols_condense(col_spec_standardise("a,b,c,d\n1,2,3,4"))
  )
})

test_that("print(col_spec) with no columns specified", {
  expect_snapshot(cols())
  expect_snapshot(cols(.default = col_character()))
})

test_that("print(col_spec) and condense edge cases", {
  expect_snapshot(print(
    cols(a = col_integer(), b = col_integer(), c = col_double()),
    n = 1,
    condense = TRUE,
    colour = FALSE
  ))
})

test_that("print(col_spec) with colors", {
  local_reproducible_output(crayon = TRUE)

  out <- col_spec_standardise(
    "a,b,c,d,e,f,g,h,i\n1,2,F,a,2018-01-01,2018-01-01 12:01:01,12:01:01,foo,blah",
    col_types = c(b = "i", h = "f", i = "_")
  )
  expect_snapshot_output(out)
})

test_that("non-syntatic names are escaped", {
  expect_snapshot(
    col_spec_standardise("a b,_c,1,a`b\n1,2,3,4")
  )
})

# https://github.com/tidyverse/readr/issues/597
test_that("long spec declarations can be formatted", {
  expect_snapshot(
    cols(a = col_factor(
      levels = c("apple", "pear", "banana", "peach", "apricot", "orange", "plum"),
      ordered = TRUE
    ))
  )
})

test_that("options(readr.show_col_types) controls col spec printing", {
  # skip is temporarily necessary as of January 29 2022, due to the very
  # recent release of rlang 1.0.0
  # Windows binaries aren't available yet and the different rlang versions
  # make it challenging to form test snapshots that work for whole GHA
  # build matrix
  skip_if_edition_first_windows()

  withr::local_options(list(readr.show_col_types = TRUE))
  expect_snapshot(
    out <- read_csv(readr_example("mtcars.csv")),
    variant = edition_variant()
  )

  withr::local_options(list(readr.show_col_types = FALSE))
  expect_silent(out <- read_csv(readr_example("mtcars.csv")))
})

test_that("`show_col_types` controls col spec printing", {
  # skip is temporarily necessary as of January 29 2022, due to the very
  # recent release of rlang 1.0.0
  # Windows binaries aren't available yet and the different rlang versions
  # make it challenging to form test snapshots that work for whole GHA
  # build matrix
  skip_if_edition_first_windows()

  expect_snapshot(
    out <- read_csv(readr_example("mtcars.csv"), show_col_types = TRUE),
    variant = edition_variant()
  )
  expect_silent(out <- read_csv(readr_example("mtcars.csv"), show_col_types = FALSE))
})

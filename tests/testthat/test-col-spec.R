context("col_spec")

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
  expect_warning(
    out <- col_spec_standardise("1,2,3\n", c("a", "b", "c"), "ii"),
    "Insufficient `col_types`"
  )
  expect_equal(names(out[[1]]), c("a", "b", "c"))
  expect_equal(out[[1]][[3]], col_integer())
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
  expect_is(col_spec_standardise("1\n", col_names = FALSE)[[1]]$X1, "collector_integer")
})

test_that("warns about duplicated names", {
  expect_warning(col_spec_standardise("a,a\n1,2"), "Duplicated column names")
  expect_warning(col_spec_standardise("X2,\n1,2"), "Duplicated column names")
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

# Printing ----------------------------------------------------------------

regex_escape <- function(x) {
  chars <- c("*", ".", "?", "^", "+", "$", "|", "(", ")", "[", "]", "{", "}", "\\")
  gsub(paste0("([\\", paste0(collapse = "\\", chars), "])"), "\\\\\\1", x, perl = TRUE)
}

test_that("print(col_spec) with guess_parser", {
  out <- col_spec_standardise("a,b,c\n1,2,3")
  expect_output(print(out),
    regex_escape(
"cols(
  a = col_integer(),
  b = col_integer(),
  c = col_integer()
)"))
})

test_that("print(col_spec) with collector_skip", {
  out <- cols_only(a = col_integer(), c = col_integer())
  expect_output(print(out),
    regex_escape(
"cols_only(
  a = col_integer(),
  c = col_integer()
)"))
})

test_that("print(col_spec) with truncated output", {
  out <- col_spec_standardise("a,b,c\n1,2,3", col_types = cols(.default = "c"))
  expect_output(print(out, n = 2, condense = FALSE),
    regex_escape(
"cols(
  .default = col_character(),
  a = col_character(),
  b = col_character()
  # ... with 1 more columns
)"))
})

test_that("spec object attached to read data", {

  test_data <- read_csv("basic-df.csv", col_types = NULL, col_names = TRUE, progress = FALSE)

  expect_equal(spec(test_data),
    cols(
       a = col_logical(),
       b = col_integer(),
       c = col_double(),
       d = col_character()))
})


test_that("print(col_spec) works with dates", {
  out <- col_spec_standardise("a,b,c\n",
    col_types = cols(a = col_date(format = "%Y-%m-%d"),
      b = col_date(),
      c = col_date()))

  expect_output(print(out),
    regex_escape(
"cols(
  a = col_date(format = \"%Y-%m-%d\"),
  b = col_date(format = \"\"),
  c = col_date(format = \"\")
)"))
})

test_that("print(col_spec) with unnamed columns", {
  out <- col_spec_standardise(col_types = "c_c", col_names = c("a", "c"))
  expect_output(print(out),
    regex_escape(
"cols(
  a = col_character(),
  col_skip(),
  c = col_character()
)"))
})

test_that("print(cols_only()) prints properly", {
  out <- cols_only(
    a = col_character(),
    c = col_integer())
  expect_output(print(out),
    regex_escape(
"cols_only(
  a = col_character(),
  c = col_integer()
)"))
})

test_that("print(col_spec) with n == 0 prints nothing", {
  out <- col_spec_standardise("a,b,c\n1,2,3")
  expect_silent(print(out, n = 0))
})

test_that("print(col_spec, condense = TRUE) condenses the spec", {
  out <- col_spec_standardise("a,b,c,d\n1,2,3,a")
  expect_output(print(cols_condense(out)),
    regex_escape(
"cols(
  .default = col_integer(),
  d = col_character()
)"))

  out <- col_spec_standardise("a,b,c,d\n1,2,3,4")
  expect_output(print(cols_condense(out)),
    regex_escape(
"cols(
  .default = col_integer()
)"))
})

test_that("print(col_spec) with no columns specified", {
  out <- cols()
  expect_output(print(out), regex_escape("cols()"))

  out <- cols(.default = col_character())
  expect_output(print(out), regex_escape(
"cols(
  .default = col_character()
)"))
})

test_that("print(col_spec) and condense edge cases", {
  out <- cols(a = col_integer(), b = col_integer(), c = col_double())

  expect_equal(format(out, n = 1, condense = TRUE),
"cols(
  .default = col_integer(),
  c = col_double()
)
")
})

test_that("non-syntatic names are escaped", {
  x <- read_csv("a b,_c,1,a`b\n1,2,3,4")
  expect_equal(format(spec(x)),
"cols(
  `a b` = col_integer(),
  `_c` = col_integer(),
  `1` = col_integer(),
  `a\\`b` = col_integer()
)
")
})

test_that("long expressions are wrapped (597)", {
  expect_equal(format(cols(a = col_factor(levels = c("apple", "pear", "banana", "peach", "apricot", "orange", "plum"), ordered = TRUE))),
'cols(
  a = col_factor(levels = c("apple", "pear", "banana", "peach", "apricot", "orange", "plum"
    ), ordered = TRUE, include_na = FALSE)
)
')
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

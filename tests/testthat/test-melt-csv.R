context("melt_csv")

test_that("read_csv type imputation and NA detection works", {
  melt_data <- melt_csv("non-tabular.csv", na = "NA")
  expect_equal(melt_data$data_type[7:11],
    c("missing", "empty", "character", "integer", "double"))
})

test_that("read_tsv works on a simple file", {
  melt_data <- melt_tsv("a\tb\n1\t2")
  expect_equal(melt_data$data_type, rep(c("character", "integer"), each = 2))
})

test_that("melt_csv's 'NA' option genuinely changes the NA values", {
  expect_equal(melt_csv("z\n", na = "z")$data_type, "missing")
})

test_that("melt_csv's 'NA' option works with multiple NA values", {
  expect_equal(melt_csv("NA\nmiss\n13", na = c("13", "miss"))$data_type,
               c("character", "missing", "missing"))
})

test_that('passing character() to melt_csv\'s "NA" option reads "" correctly', {
  expect_equal(melt_csv("foo\n", na = character())$value, "foo")
})

test_that("passing \"\" to melt_csv's 'NA' option reads \"\" correctly", {
  expect_equal(melt_csv("foo,bar\nfoo,\n", na = "")$value,
               c("foo", "bar", "foo", NA))
})

test_that("changing melt_csv's 'quote' argument works correctly", {
  test_data <- melt_csv("basic-df.csv")
  test_data_singlequote <- melt_csv("basic-df-singlequote.csv", quote="'")
  expect_identical(test_data, test_data_singlequote)
})

test_that("melt_csv's 'skip' option allows for skipping'", {
  test_data <- melt_csv("basic-df.csv", skip = 1)
  expect_equal(nrow(test_data), 40)
})

test_that("melt_csv's 'n_max' allows for a maximum number of records and does not corrupt any", {
  test_data <- melt_csv("basic-df.csv", n_max = 7)
  expect_equal(nrow(test_data), 28)
  expect_equal(sum(test_data$data_type == "missing"), 0)
})

test_that("can read more than 100 columns", {
  set.seed(2015-3-13)
  x <- as.data.frame(matrix(rbinom(300, 2, .5), nrow = 2))
  y <- format_csv(x)
  expect_equal(max(melt_csv(y)$col), 150)
})

test_that("encoding affects text", {
  x <- melt_csv("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"))
  expect_identical(x$value[2], "\u00e9l\u00e8ve")
})

test_that("nuls are dropped with a warning", {
  expect_warning(x <- melt_csv("raw.csv"))
  expect_equal(readr:::n_problems(x), 1)
  expect_equal(x$value[3], "ab")
})

test_that("can read from the clipboard", {
  skip_on_cran()
  skip_if_no_clipboard()
  clipr::write_clip("a,b,c\n1,2,3")
  expect_identical(melt_csv(clipboard()), melt_csv("a,b,c\n1,2,3"))
})

test_that("can read from a multi-line character vector", {
  expect_identical(max(melt_csv(c("a,b,c", "1,2,3"))$row), 2)
})

# Column warnings ---------------------------------------------------------

test_that("missing lines are not skipped", {
   # first
  expect_equal(max(melt_csv("a,b\n\n\n1,2")$row), 4)

   # middle
  expect_equal(max(melt_csv("a,b\n1,2\n\n\n2,3\n")$row), 5)

  # last (trailing \n is ignored)
  expect_equal(max(melt_csv("a,b\n1,2\n\n\n")$row), 4)
})

# read_csv2 ---------------------------------------------------------------

test_that("decimal mark automatically set to ,", {
  expect_message(
    x <- melt_csv2("x\n1,23"),
    if (default_locale()$decimal_mark == ".") "decimal .*grouping .*mark" else NA)
  expect_equal(x$data_type[2], "double")
})

# Zero rows ---------------------------------------------------------------

test_that("n_max 0 gives zero row data frame", {
  x <- melt_csv("a,b\n1,2", n_max = 0)
  expect_equal(dim(x), c(0, 4))
})

# Comments ----------------------------------------------------------------

test_that("comments are ignored regardless of where they appear", {
  out1 <- melt_csv('x\n1#comment',comment = "#")
  out2 <- melt_csv('x\n1#comment\n#comment', comment = "#")
  out3 <- melt_csv('x\n"1"#comment', comment = "#")

  chk1 <- tibble::data_frame(
    row = c(1, 2),
    col = c(1, 1),
    data_type = c("character", "integer"),
    value = c("x", "1"))

  expect_true(all.equal(chk1, out1))
  expect_true(all.equal(chk1, out2))
  expect_true(all.equal(chk1, out3))

  out5 <- melt_csv("x1,x2,x3\nA2,B2,C2\nA3#,B2,C2\nA4,A5,A6", comment = "#", progress = FALSE)
  out6 <- melt_csv("x1,x2,x3\nA2,B2,C2\nA3,#B2,C2\nA4,A5,A6", comment = "#", progress = FALSE)
  out7 <- melt_csv("x1,x2,x3\nA2,B2,C2\nA3,#B2,C2\n#comment\nA4,A5,A6", comment = "#", progress = FALSE)

  chk2 <- tibble::data_frame(
    row = c(1, 1, 1, 2, 2, 2, 3, 4, 4, 4),
    col = c(1, 2, 3, 1, 2, 3, 1, 1, 2, 3),
    data_type = "character",
    value = c("x1", "x2", "x3", "A2", "B2", "C2", "A3", "A4", "A5", "A6"))

  expect_true(all.equal(chk2, out5))
  expect_true(all.equal(chk2, out6))
  expect_true(all.equal(chk2, out7))
})

test_that("escaped/quoted comments are ignored", {
  out1 <- melt_delim('x\n\\#', comment = "#", delim = ",",
    escape_backslash = TRUE, escape_double = FALSE)
  out2 <- melt_csv('x\n"#"', comment = "#")

  expect_equal(out1$value[2], "#")
  expect_equal(out2$value[2], "#")
})

test_that("leading comments are ignored", {
  out <- melt_csv("#a\n#b\nx\n1", comment = "#")

  expect_equal(nrow(out), 2)
  expect_equal(out$value[2], "1")
})

test_that("skip respects comments", {
  melt_x <- function(...) {
    melt_csv("#a\nb\nc", ...)$value
  }

  expect_equal(melt_x(), c("#a", "b", "c"))
  expect_equal(melt_x(skip = 1), c("b", "c"))
  expect_equal(melt_x(comment = "#"), c("b", "c"))
  expect_equal(melt_x(comment = "#", skip = 2), c("c"))
})

test_that("melt_csv returns a four-col zero-row data.frame on an empty file", {
   expect_equal(dim(melt_csv("empty-file")), c(0, 4))
})

test_that("melt_delim errors on length 0 delimiter", {
  expect_error(melt_delim("a b\n1 2\n", delim = ""),
    "`delim` must be at least one character, use `melt_table\\(\\)` for whitespace delimited input\\.")
})

test_that("melt_csv handles whitespace between delimiters and quoted fields", {
  x <- melt_csv('1, \"hi,there\"\n3,4')
  expect_equal(x$value[2:3], c("hi,there", "3"))
})

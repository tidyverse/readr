test_that("read_lines respects encoding", {
  skip_on_os("solaris")

  x <- read_lines("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"))
  expect_equal(x, c("fran\u00e7ais", "\u00e9l\u00e8ve"))
})

test_that("read_lines returns an empty character vector on an empty file", {
  expect_equal(read_lines("empty-file"), character())
})

test_that("read_lines handles embedded nuls", {
  skip_if_edition_first()
  expect_warning(res <- read_lines(test_path("null-file"), lazy = FALSE))
  expect_equal(res, c("a,b,c", "1,2,", "3,4,5"))
})

test_that("read_lines uses na argument", {
  expect_equal(read_lines(I("abc\n123")), c("abc", "123"))
  expect_equal(read_lines(I("abc\n123"), na = "abc"), c(NA_character_, "123"))
  expect_equal(read_lines(I("abc\n123"), na = "123"), c("abc", NA_character_))
  expect_equal(read_lines(I("abc\n123"), na = c("abc", "123")), c(NA_character_, NA_character_))
})

test_that("blank lines are passed unchanged", {
  expect_equal(read_lines(I("abc\n\n123")), c("abc", "", "123"))
  expect_equal(read_lines(I("abc\n\n123"), na = ""), c("abc", NA, "123"))
})

test_that("read_lines can skip blank lines (#923)", {
  x <-
    I("1
2
3

foo
bar
baz
")

  expect_equal(read_lines(x), c("1", "2", "3", "", "foo", "bar", "baz"))
  expect_equal(read_lines(x, skip_empty_rows = TRUE), c("1", "2", "3", "foo", "bar", "baz"))
  expect_equal(read_lines(x, skip = 1), c("2", "3", "", "foo", "bar", "baz"))
  expect_equal(read_lines(x, skip = 2), c("3", "", "foo", "bar", "baz"))
  expect_equal(read_lines(x, skip = 3), c("", "foo", "bar", "baz"))
  expect_equal(read_lines(x, skip = 4), c("foo", "bar", "baz"))
  expect_equal(read_lines(x, skip = 5), c("bar", "baz"))
  expect_equal(read_lines(x, skip = 6), c("baz"))
  expect_equal(read_lines(x, skip = 7), character())
})

test_that("allocation works as expected", {
  tmp <- tempfile(fileext = ".gz")
  on.exit(unlink(tmp))

  x <- rep(paste(rep("a", 2^10), collapse = ""), 2^11)
  writeLines(x, tmp)
  expect_equal(length(read_lines(tmp)), 2^11)
})

test_that("read_lines(skip_empty_rows) works when blank lines are at the end of the file (#968)", {
  skip_on_os("windows")

  tmp <- tempfile()
  on.exit(unlink(tmp))

  writeLines(
    con = tmp,
    "test
"
  )

  expect_equal(read_lines(tmp, skip_empty_rows = TRUE), "test")
})

test_that("read_lines(skip_empty_rows) works if there are double quotes in the lines (#991)", {
  # TODO: turn on test
  skip_if_edition_second()
  data <-
    "a\"b
cde
f\"g
hij"

  expect_equal(
    read_lines(data, skip = 1),
    c(
      "cde",
      "f\"g",
      "hij"
    )
  )
})

# These tests are slow so are commented out
# test_that("long vectors are supported", {
# tmp <- tempfile(fileext = ".gz")
# on.exit(unlink(tmp))

# x <- rep(paste(rep("a", 2 ^ 16), collapse = ''), 2 ^ 15)
# con <- gzfile(tmp, open = "w", compression = 0)
# writeLines(x, con)
# close(con)

# expect_equal(length(read_lines(tmp)), 2^15)

# expect_equal(length(read_lines_raw(tmp)), 2^15)
# })

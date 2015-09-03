context("read_csv parameter testing")

test_that("read_csv col imputation, col_name detection and NA detection works", {
  test_data <- read_csv("basic-df.csv", col_types = NULL, col_names = TRUE)
  expect_equal(unname(unlist(lapply(test_data, class))),
    c("logical", "integer", "numeric", "character"))
  expect_equal(names(test_data), c("a", "b", "c", "d"))
  expect_equal(sum(is.na(test_data$d)), 1)
})

test_that("read_csv's 'NA' option genuinely changes the NA values", {
  expect_equal(read_csv("a\nz", na = "z")$a, NA_character_)
})

test_that("read_csv's 'NA' option works with multiple NA values", {
  expect_equal(read_csv("a\nNA\n\nmiss\n13", na = c("13", "miss"))$a,
               c("NA", "", NA, NA))
})

test_that('passing character() to read_csv\'s "NA" option reads "" correctly', {
  expect_equal(read_csv("a\nfoo\n\n", na = character())$a, c("foo", ""))
})

test_that("passing \"\" to read_csv's 'NA' option reads \"\" correctly", {
  expect_equal(read_csv("a\nfoo\n\n", na = "")$a, c("foo", NA))
})

test_that("read_csv's 'skip' option allows for skipping'", {
  test_data <- read_csv("basic-df.csv", skip = 1)
  expect_equal(nrow(test_data), 9)
})

test_that("read_csv's 'skip' option allows for skipping when no header row is present'", {
  test_data <- read_csv("basic-df.csv", skip = 1, col_names = FALSE)
  expect_equal(nrow(test_data), 10)
})

test_that("read_csv's 'n_max' allows for a maximum number of records and does not corrupt any", {
  test_data <- read_csv("basic-df.csv", n_max = 7)
  expect_equal(nrow(test_data), 7)
  expect_equal(sum(is.na(test_data)), 0)
})

test_that("n_max also affects column guessing", {
  df <- read_csv(n_max = 1, 'x,y,z
    1,2,3
    1,2,3,4'
  )
  expect_equal(dim(df), c(1, 3))
})

test_that("can read more than 100 columns", {
  set.seed(2015-3-13)
  x <- as.data.frame(matrix(rbinom(300, 2, .5), nrow = 2))
  y <- write_csv(x, "")

  expect_equal(ncol(read_csv(y)), 150)
})

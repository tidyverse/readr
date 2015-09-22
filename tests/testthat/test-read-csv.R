context("read_csv")

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

test_that("encoding affects text and headers", {
  x <- read_csv("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"))
  expect_identical(names(x), "français")
  expect_identical(x[[1]], "élève")
})

test_that("nuls are silently dropped", {
  x <- read_csv("raw.csv")
  expect_equal(names(x), c("ab", "def"))
})

# Column warnings ---------------------------------------------------------

test_that("warnings based on number of columns (not output columns)", {
  out1 <- readr::read_csv("1,2,3\n4,5,6", c("", "", "z"), "__i")
  out2 <- readr::read_csv("1,2,3\n4,5,6", FALSE, cols_only(X3 = "i"))

  expect_equal(n_problems(out1), 0)
  expect_equal(n_problems(out2), 0)
})

# read_csv2 ---------------------------------------------------------------

test_that("decimal mark automatically set to ,", {
  x <- read_csv2("x\n1,23")
  expect_equal(x[[1]], 1.23)
})

# Zero rows ---------------------------------------------------------------

test_that("header only df gets character columns", {
  x <- read_csv("a,b\n")
  expect_equal(dim(x), c(0, 2))
  expect_equal(class(x$a), "character")
  expect_equal(class(x$b), "character")
})

test_that("n_max 0 gives zero row data frame", {
  x <- read_csv("a,b\n1,2", n_max = 0)
  expect_equal(dim(x), c(0, 2))
  expect_equal(class(x$a), "integer")
  expect_equal(class(x$b), "integer")
})

test_that("empty file with col_names and col_types creates correct columns", {
  x <- read_csv(datasource_string("", 0), c("a", "b"), "ii")
  expect_equal(dim(x), c(0, 2))
  expect_equal(class(x$a), "integer")
  expect_equal(class(x$b), "integer")
})

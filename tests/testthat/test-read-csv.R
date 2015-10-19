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
  y <- format_csv(x)

  expect_equal(ncol(read_csv(y)), 150)
})

test_that("encoding affects text and headers", {
  x <- read_csv("enc-iso-8859-1.txt", locale = locale(encoding = "ISO-8859-1"))
  expect_identical(names(x), "fran\u00e7ais")
  expect_identical(x[[1]], "\u00e9l\u00e8ve")
})

test_that("nuls are dropped with a warning", {
  expect_warning(x <- read_csv("raw.csv"))
  expect_equal(n_problems(x), 1)
  expect_equal(x$abc, "ab")
})

# Column warnings ---------------------------------------------------------

test_that("warnings based on number of columns (not output columns)", {
  out1 <- readr::read_csv("1,2,3\n4,5,6", "z", "__i")
  out2 <- readr::read_csv("1,2,3\n4,5,6", FALSE, cols_only(X3 = "i"))

  expect_equal(n_problems(out1), 0)
  expect_equal(n_problems(out2), 0)
})

test_that("missing last field generates warning", {
  expect_warning(out <- read_csv("a,b\n2"))
  expect_equal(problems(out)$expected, "2 columns")
})

test_that("missing lines generates warning", {
  # first
  expect_warning(out <- read_csv("a,b\n\n\n1,2"))
  expect_equal(problems(out)$expected, rep("2 columns", 2))

  # middle
  expect_warning(out <- read_csv("a,b\n1,2\n\n\n2,3\n"))
  expect_equal(problems(out)$expected, rep("2 columns", 2))

  # last (trailing \n is ngored)
  expect_warning(out <- read_csv("a,b\n1,2\n\n\n"))
  expect_equal(problems(out)$expected, rep("2 columns", 2))
})

test_that("extra columns generates warnings", {
  expect_warning(out1 <- read_csv("a,b\n1,2,3\n"))
  expect_warning(out2 <- read_csv("a,b\n1,2,3", col_types = "ii"))
  expect_warning(out3 <- read_csv("1,2,3\n", c("a", "b")))
  expect_warning(out4 <- read_csv("1,2,3\n", c("a", "b"), "ii"))

  expect_equal(problems(out1)$expected, "2 columns")
  expect_equal(problems(out2)$expected, "2 columns")
  expect_equal(problems(out3)$expected, "2 columns")
  expect_equal(problems(out4)$expected, "2 columns")
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


# Comments ----------------------------------------------------------------

test_that("comments are ignored regardless of where they appear", {
  out1 <- read_csv('x\n1#comment',comment = "#")
  out2 <- read_csv('x\n1#comment\n#comment', comment = "#")
  out3 <- read_csv('x\n"1"#comment', comment = "#")

  expect_equal(out1$x, 1)
  expect_equal(out2$x, 1)
  expect_equal(out3$x, 1)

  expect_warning(out4 <- read_csv('x,y\n1,#comment', comment = "#"))
  expect_equal(out4$y, NA_character_)
})

test_that("escaped/quoted comments are ignored", {
  out1 <- read_delim('x\n\\#', comment = "#", delim = ",",
    escape_backslash = TRUE, escape_double = FALSE)
  out2 <- read_csv('x\n"#"', comment = "#")

  expect_equal(out1$x, "#")
  expect_equal(out2$x, "#")
})

test_that("leading comments are ignored", {
  out <- read_csv("#a\n#b\nx\n1", comment = "#")

  expect_equal(ncol(out), 1)
  expect_equal(out$x, 1L)
})

test_that("skip respects comments", {
  read_x <- function(...) {
    read_csv("#a\nb\nc", col_names = FALSE, ...)[[1]]
  }

  expect_equal(read_x(), c("#a", "b", "c"))
  expect_equal(read_x(skip = 1), c("b", "c"))
  expect_equal(read_x(comment = "#"), c("b", "c"))
  expect_equal(read_x(comment = "#", skip = 1), c("c"))
})


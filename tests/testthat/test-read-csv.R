context("read_csv parameter testing")

#Formatting for column imputation, col_name detection and NA detection.
test_data <- read_csv(file.path(getwd(),"/basic-df.csv"), col_types = NULL, col_names = TRUE)

test_that("read_csv automatic column type imputation works",{
  expect_that(unname(unlist(lapply(test_data,class))), equals(c("logical","integer","numeric","character")))
})

test_that("read_csv's col_names = TRUE actually picks up col_names",{
  expect_that(names(test_data), equals(c("a","b","c","d")))
})

test_that("read_csv detects NA values",{
  expect_that(sum(is.na(test_data$d)), equals(1))
})

test_that("read_csv's 'NA' option genuinely changes the NA values",{
  test_data <- read_csv(file.path(getwd(),"/basic-df.csv"), na = "turnip")
  expect_that(nrow(test_data[test_data$d == "turnip",]), equals(1))
})

test_that("read_csv's 'skip' option allows for skipping'",{
  test_data <- read_csv(file.path(getwd(),"/basic-df.csv"), skip = 1)
  expect_that(nrow(test_data), equals(9))
})

#n_max testing
test_data <- read_csv(file.path(getwd(),"/basic-df.csv"), n_max = 7)

test_that("read_csv's 'n_max' allows for a maximum number of records",{
  expect_that(nrow(test_data), equals(7))
})

test_that("'n_max' does not corrupt records",{
  expect_that(sum(is.na(test_data)), equals(1))
})

context("problems")

test_that("stop_for_problems throws error", {
  expect_warning(x <- parse_integer("1.234"))
  expect_error(stop_for_problems(x), "1 parsing failure")
})

test_that("skipping columns gives incorrect problem column (#573)", {
  delim.skip0 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "dcc"))
  delim.skip1 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "_dc"))
  delim.skip2 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "--d"))
  expect_equal(delim.skip0$col, "X1")
  expect_equal(delim.skip1$col, "X2")
  expect_equal(delim.skip2$col, "X3")

  delim.sk0.2 <- problems(read_tsv("aa\tbb\tcc\n", col_names = F, col_types = "dcd"))
  delim.sk1.2 <- problems(read_tsv("aa\tbb\tcc\n", col_names = F, col_types = "_dd"))
  expect_equal(delim.sk0.2$col, c("X1", "X3"))
  expect_equal(delim.sk1.2$col, c("X2", "X3"))


  fwf.pos <- fwf_widths(c(2, 2, 2))
  fwf.skip0 <- problems(read_fwf("aabbcc\n", fwf.pos, col_types = "dcc"))
  fwf.skip1 <- problems(read_fwf("aabbcc\n", fwf.pos, col_types = "_dc"))
  fwf.skip2 <- problems(read_fwf("aabbcc\n", fwf.pos, col_types = "--d"))
  fwf.sk0.2 <- problems(read_fwf("aabbcc\n", fwf.pos, col_types = "dcd"))
  fwf.sk1.2 <- problems(read_fwf("aabbcc\n", fwf.pos, col_types = "d-d"))
  expect_equal(fwf.skip0$col, "X1")
  expect_equal(fwf.skip1$col, "X2")
  expect_equal(fwf.skip2$col, "X3")
  expect_equal(fwf.sk0.2$col, c("X1", "X3"))
  expect_equal(fwf.sk1.2$col, c("X1", "X3"))
})

test_that("problems returns the filename (#581)", {
  files <- problems(read_csv(readr_example("mtcars.csv"), col_types = cols(mpg = col_integer())))$file

  expect_equal(length(files), 28L)
  expect_equal("mtcars.csv'", basename(files)[[1L]])
})

test_that("stop_for_problems throws error", {
  expect_warning(x <- parse_integer("1.234"))
  expect_error(stop_for_problems(x), "1 parsing failure")
})

test_that("skipping columns gives incorrect problem column (#573)", {
  skip_if_edition_first()

  delim.skip0 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "dcc", lazy = FALSE))
  delim.skip1 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "_dc", lazy = FALSE))
  delim.skip2 <- problems(read_csv("aa,bb,cc\n", col_names = F, col_types = "--d", lazy = FALSE))
  expect_equal(delim.skip0$col, 1)
  expect_equal(delim.skip1$col, 2)
  expect_equal(delim.skip2$col, 3)

  skip_if_edition_second()
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
  skip_if_edition_first()
  files <- problems(read_csv(readr_example("mtcars.csv"), col_types = cols(mpg = col_integer()), lazy = FALSE))$file

  expect_equal(length(files), 28L)
  expect_equal(basename(files)[[1L]], "mtcars.csv")
})

test_that("problems returns full original field (#444)", {
  probs <- problems(read_tsv("X\n-$12,500\n$2,000\n-$5,000\n$1,000\n-$3,000\n", col_types = list(.default = col_number()), lazy = FALSE))

  expect_equal(NROW(probs), 3)
  expect_equal(probs$actual, c("-$12,500", "-$5,000", "-$3,000"))
})

test_that("warn_problems should not fail when parsing non-ASCII characters (#1152)", {
  expect_warning(probs <- warn_problems(readRDS("test-non-ascii-1152.rds")))
  expect_equal(NROW(probs), 10)
})

context("Parsing, count_fields")

test_that("counts correct number of fields based on supplied tokenizer", {
  string <- "1,a,NA\n2,b,NA\n"
  res_csv <- count_fields(string, tokenizer_csv())
  res_tsv <- count_fields(string, tokenizer_tsv())
  expect_equal(res_csv, c(3, 3))
  expect_equal(res_tsv, c(1, 1))
})

test_that("maximum lines counted is respected", {
  string <- "1,a,NA\n2,b,NA\n"
  res_csv <- count_fields(string, tokenizer_csv(), n_max = 1)
  expect_equal(res_csv, 3)
})

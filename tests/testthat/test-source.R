context("Source")
# Tests the Source class

test_that("Encoding is trivially retreived", {
  ds <- datasource("a b\n1 2", encoding = "UTF-8")
  expect_equal(source_encoding(ds), "UTF-8")
})

test_that("UTF-16 is identified as UTF-16LE or UTF-16BE", {
  bom_le <- as.raw(c(0xFF, 0xFE))
  # Convert text to UTF-16LE (without BOM) and append BOM manually so it becomes
  # UTF-16 (with BOM). The Source class should skip the BOM automatically and
  # report UTF-16LE
  text <- iconv("a b\n1 2", from = "UTF-8", to = "UTF-16LE", toRaw = TRUE)[[1]]
  ds <- datasource(c(bom_le, text), encoding = "UTF-16")
  expect_equal(source_encoding(ds), "UTF-16LE")

  # Do the same with UTF-16
  bom_be <- as.raw(c(0xFE, 0xFF))
  text <- iconv("a b\n1 2", from = "UTF-8", to = "UTF-16BE", toRaw = TRUE)[[1]]
  ds <- datasource(c(bom_be, text), encoding = "UTF-16")
  expect_equal(source_encoding(ds), "UTF-16BE")
})

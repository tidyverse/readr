library(testthat)
library(readr)

if (requireNamespace("xml2")) {
  test_check("readr", reporter = MultiReporter$new(reporters = list(JunitReporter$new(file = "test-results.xml"), CheckReporter$new())))
} else {
  test_check("readr")
}

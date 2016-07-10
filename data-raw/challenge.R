set.seed(1014)
x <- c(sample(5000, 1000, replace = TRUE), runif(1000))
y <- as.Date("2010-01-01") + c(rep(NA, 1000), sample(5000, 1000, replace = TRUE))

trouble <- tibble::tibble(x, y)
write_csv(trouble, "inst/extdata/challenge.csv")

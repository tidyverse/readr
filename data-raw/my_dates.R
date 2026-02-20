data <- as.character(sample(
  seq(
    as.Date("2020/01/01"),
    as.Date("2022/12/31"),
    by = "day"
  ), 1001
))

dates <- tibble::tibble(dates = data)

dates[1000, ] <- "20220907"
write_csv(dates, "inst/extdata/my_dates.csv")

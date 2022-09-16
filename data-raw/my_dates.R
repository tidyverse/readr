dates <- tibble::tibble(dates = as.character(sample(seq(as.Date("2020/01/01"),
                                           as.Date("2022/12/31"), by = "day"), 1001)))

# readr/vroom will use rows 1-999 + 1001 for guessing
dates[1000,] <- "20220907"
write_csv(dates, "inst/extdata/my_dates.csv")
df1 <- read_csv("inst/extdata/my_dates.csv")

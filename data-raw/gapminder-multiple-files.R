library(gapminder)
library(tidyverse)

gapminder |>
  filter(year == 1952) |>
  group_by(continent) |>
  slice_head(n = 6) |>
  arrange(continent, country) |>
  group_walk(
    ~ write_csv(.x, str_glue("inst/extdata/mini-gapminder-{tolower(.y$continent)}.csv")
    )
  )

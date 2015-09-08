library(stringi)

locs <- stri_locale_list()
base <- stri_split_fixed(locs, "_", n = 2, simplify = TRUE)[, 1]

locale_info <- function(x) {

  full <- stri_datetime_symbols(x, context = "format", width = "wide")
  abbr <- stri_datetime_symbols(x, context = "format", width = "abbreviated")

  list(
    month = full$Month,
    month_abbr = abbr$Month,
    day = full$Weekday,
    day_abbr = abbr$Weekday
  )
}

locs_info <- lapply(locs, locale_info)
names(locs_info) <- locs

same_as_base <- mapply(identical, locs_info, locs_info[base])

needed <- locs[!same_as_base | locs %in% base]
date_symbols <- locs_info[needed]

devtools::use_data(date_symbols, internal = TRUE, overwrite = TRUE)

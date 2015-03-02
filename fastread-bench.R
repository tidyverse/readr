mixbev <- list(
  path = "~/Desktop/mixedbev//raw//bev01-22.csv",
  col_names = c("tabc", "name", "address", "city", "state", "zip", "county",
    "na", "period", "tax"),
  parsers = list(
    tabc = character_parser(),
    name = character_parser(),
    address = character_parser(),
    city = character_parser(),
    zip = integer_parser(),
    county = integer_parser(),
    period = character_parser(),
    tax = double_parser()
  )
)

system.time(read_csv(mixbev$path, col_names = mixbev$col_names))
system.time(read_csv(mixbev$path, col_names = mixbev$col_names,
  parsers = mixbev$parsers))
system.time(read.csv(mixbev$path, header = FALSE))

taxi <- list(
  path = "~/Dropbox (RStudio)/14-nyc-taxi/faredata2013/trip_fare_1.csv",
  col_names = c("medallion", "hack_license", "vendor_id", "pickup_datetime",
    "payment_type", "fare_amount", "surcharge", "mta_tax", "tip_amount",
    "tolls_amount", "total_amount"),
  parsers = list(
    medallion = character_parser(),
    hack_license = character_parser(),
    vendor_id = character_parser(),
    pickup_datetime = character_parser(),
    payment_type = character_parser(),
    fare_amount = double_parser(),
    surcharge = double_parser(),
    mta_tax = double_parser(),
    tip_amount = integer_parser(),
    tolls_amount = double_parser(),
    total_amount = double_parser()
  )
)

system.time(read_csv(taxi$path))
system.time(read_csv(taxi$path, col_names = taxi$col_names,
  parsers = taxi$parsers))
system.time(read.csv(taxi$path))

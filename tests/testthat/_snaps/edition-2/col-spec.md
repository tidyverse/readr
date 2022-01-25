# options(readr.show_col_types) controls col spec printing

    Code
      out <- read_csv(readr_example("mtcars.csv"))
    Message <vroom_dim_message>
      Rows: 32 Columns: 11
    Message <vroom_spec_message>
      -- Column specification --------------------------------------------------------
      Delimiter: ","
      dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
      
      i Use `spec()` to retrieve the full column specification for this data.
      i Specify the column types or set `show_col_types = FALSE` to quiet this message.

# `show_col_types` controls col spec printing

    Code
      out <- read_csv(readr_example("mtcars.csv"), show_col_types = TRUE)
    Message <vroom_dim_message>
      Rows: 32 Columns: 11
    Message <vroom_spec_message>
      -- Column specification --------------------------------------------------------
      Delimiter: ","
      dbl (11): mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb
      
      i Use `spec()` to retrieve the full column specification for this data.
      i Specify the column types or set `show_col_types = FALSE` to quiet this message.


# options(readr.show_col_types) controls col spec printing

    Code
      out <- read_csv(readr_example("mtcars.csv"))
    Message <readr_spec_message>
      
      -- Column specification --------------------------------------------------------
      cols(
        mpg = col_double(),
        cyl = col_double(),
        disp = col_double(),
        hp = col_double(),
        drat = col_double(),
        wt = col_double(),
        qsec = col_double(),
        vs = col_double(),
        am = col_double(),
        gear = col_double(),
        carb = col_double()
      )

# `show_col_types` controls col spec printing

    Code
      out <- read_csv(readr_example("mtcars.csv"), show_col_types = TRUE)
    Message <readr_spec_message>
      
      -- Column specification --------------------------------------------------------
      cols(
        mpg = col_double(),
        cyl = col_double(),
        disp = col_double(),
        hp = col_double(),
        drat = col_double(),
        wt = col_double(),
        qsec = col_double(),
        vs = col_double(),
        am = col_double(),
        gear = col_double(),
        carb = col_double()
      )


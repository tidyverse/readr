# comments are ignored regardless of where they appear

    Code
      out4 <- read_csv(I("x,y\n1,#comment"), comment = "#", col_types = "cc")


# warning lines are correct after skipping

    Code
      out3 <- read_csv(I("v1,v2\n\n1,2\n\n3,4"), col_types = "i")
    Warning <simpleWarning>
      Unnamed `col_types` should have the same length as `col_names`. Using smaller of the two.
      2 parsing failures.
      row col  expected    actual         file
        1  -- 1 columns 2 columns literal data
        2  -- 1 columns 2 columns literal data
      

---

    Code
      out4 <- read_csv(I("v1,v2\n#foo\n1,2\n#bar\n3,4"), col_types = "i", comment = "#")
    Warning <simpleWarning>
      Unnamed `col_types` should have the same length as `col_names`. Using smaller of the two.
      2 parsing failures.
      row col  expected    actual         file
        1  -- 1 columns 2 columns literal data
        2  -- 1 columns 2 columns literal data
      

# too few or extra col_types generates warnings

    Code
      out1 <- read_csv(I("v1,v2\n1,2"), col_types = "i", lazy = FALSE)
    Warning <simpleWarning>
      Unnamed `col_types` should have the same length as `col_names`. Using smaller of the two.
      1 parsing failure.
      row col  expected    actual         file
        1  -- 1 columns 2 columns literal data
      

# comments are ignored regardless of where they appear

    Code
      out4 <- read_csv(I("x,y\n1,#comment"), comment = "#", col_types = "cc")
    Warning <simpleWarning>
      1 parsing failure.
      row col  expected    actual         file
        1  -- 2 columns 1 columns literal data
      


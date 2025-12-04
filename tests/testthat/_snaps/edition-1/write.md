# fails to create file in non-existent directory

    Code
      write_csv(mtcars, file.path(tempdir(), "x/y"))
    Condition
      Warning in `open.connection()`:
      cannot open file '<temp>/x/y': No such file or directory
      Error in `open.connection()`:
      ! cannot open the connection

# Can change the escape behavior for quotes

    Code
      format_delim(df, "\t", escape = "invalid")
    Condition
      Error in `match.arg()`:
      ! 'arg' should be one of "double", "backslash", "none"


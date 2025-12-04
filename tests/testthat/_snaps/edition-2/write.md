# fails to create file in non-existent directory

    Code
      write_csv(mtcars, file.path(tempdir(), "x/y"))
    Condition
      Error:
      ! Cannot open file for writing:
      * '<temp>/x/y'

# Can change the escape behavior for quotes

    Code
      format_delim(df, "\t", escape = "invalid")
    Condition
      Error in `vroom::vroom_format()`:
      ! `escape` must be one of "double", "backslash", or "none", not "invalid".


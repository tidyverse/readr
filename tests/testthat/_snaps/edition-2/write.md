# fails to create file in non-existent directory

    Code
      write_csv(mtcars, file.path(tempdir(), "x/y"))
    Condition
      Error:
      ! Cannot open file for writing:
      * '<temp>/x/y'


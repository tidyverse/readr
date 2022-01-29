# check_string() works

    Code
      name <- 1
      check_string(name)
    Condition
      Error:
      ! `name` must be a string.
    Code
      check_string(name, nm = "NAME!")
    Condition
      Error:
      ! `NAME!` must be a string.


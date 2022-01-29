# check_string() works

    Code
      name <- 1
      check_string(name)
    Error <simpleError>
      `name` must be a string.
    Code
      check_string(name, nm = "NAME!")
    Error <simpleError>
      `NAME!` must be a string.


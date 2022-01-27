# check_string() works

    Code
      name <- 1
      check_string(name)
    Error <rlang_error>
      `name` must be a string.
    Code
      check_string(name, nm = "NAME!")
    Error <rlang_error>
      `NAME!` must be a string.


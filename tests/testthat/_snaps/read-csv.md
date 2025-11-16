# read_delim errors on length 0 delimiter (557)

    Code
      read_delim(I("a b\n1 2\n"), delim = "")
    Condition
      Error:
      ! `delim` must be at least one character, use `read_table()` for whitespace delimited input.


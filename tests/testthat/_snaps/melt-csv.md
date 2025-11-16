# melt_delim errors on length 0 delimiter

    Code
      melt_delim("a b\n1 2\n", delim = "")
    Condition
      Error:
      ! `delim` must be at least one character, use `melt_table()` for whitespace delimited input.


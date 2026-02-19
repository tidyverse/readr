# Error when writing list columns or matrix columns

    Code
      write_csv(df, tempfile())
    Condition
      Error in `cli_block()`:
      ! `x` must not contain list or matrix columns:
      x invalid columns at index(s): 2

---

    Code
      write_csv(df2, tempfile())
    Condition
      Error in `cli_block()`:
      ! `x` must not contain list or matrix columns:
      x invalid columns at index(s): 2


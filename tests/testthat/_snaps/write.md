# Can change the escape behavior for quotes

    Code
      format_delim(df, "\t", escape = "invalid")
    Condition
      Error in `vroom::vroom_format()`:
      ! `escape` must be one of "double", "backslash", or "none", not "invalid".

# Error when writing list columns or matrix columns

    Code
      write_csv(df, tempfile())
    Condition
      Error in `cli_block()`:
      ! `x` must not contain list or matrix columns:
      x invalid columns at index(s): 3

---

    Code
      write_csv(df2, tempfile())
    Condition
      Error in `cli_block()`:
      ! `x` must not contain list or matrix columns:
      x invalid columns at index(s): 2


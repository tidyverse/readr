# requires data.frame input

    Code
      type_convert(not_df)
    Condition
      Error in `type_convert()`:
      ! is.data.frame(df) is not TRUE

# col_types accepts character specifications

    Code
      type_convert(df, col_types = "i")
    Condition
      Error:
      ! `df` and `col_types` must have consistent lengths:
        * `df` has length 3
        * `col_types` has length 1

---

    Code
      type_convert(df, col_types = c("i", "b"))
    Condition
      Error:
      ! `col_types` must be a single string.


# fwf_cols throws error when arguments are not length 1 or 2

    Code
      fwf_cols(a = 1:3, b = 4:5)
    Condition
      Error in `recycle_columns()`:
      ! Tibble columns must have compatible sizes.
      * Size 2: Column `b`.
      * Size 3: Column `a`.
      i Only values of size one are recycled.

---

    Code
      fwf_cols(a = c(), b = 4:5)
    Condition
      Error in `recycle_columns()`:
      ! Tibble columns must have compatible sizes.
      * Size 0: Column `a`.
      * Size 2: Column `b`.
      i Only values of size one are recycled.


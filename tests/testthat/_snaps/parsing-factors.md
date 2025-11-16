# factor levels must be null or a character vector (#1140)

    Code
      col_factor(levels = 1:10)
    Condition
      Error:
      ! `levels` must be `NULL` or a character vector:
      - `levels` is a 'integer'


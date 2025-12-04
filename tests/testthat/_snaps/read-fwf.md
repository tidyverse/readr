# fwf_cols throws error when arguments are not length 1 or 2

    Code
      fwf_cols(a = 1:3, b = 4:5)
    Condition
      Error in `vroom::fwf_cols()`:
      ! All inputs must have the same shape.
      x Found inputs with different lengths: 3 and 2.
      i Provide either single values (widths) or pairs of values (positions).

---

    Code
      fwf_cols(a = c(), b = 4:5)
    Condition
      Error in `vroom::fwf_cols()`:
      ! All inputs must have the same shape.
      x Found inputs with different lengths: 0 and 2.
      i Provide either single values (widths) or pairs of values (positions).


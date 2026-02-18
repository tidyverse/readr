# literal data without I() emits deprecation warning (#1611)

    Code
      x <- read_fwf("abcd\nefgh", fwf_widths(c(2, 2)), show_col_types = FALSE)
    Condition <lifecycle_warning_deprecated>
      Warning:
      The `file` argument of `read_fwf()` should use `I()` for literal data as of readr 2.2.0.
        
        # Bad (for example):
        read_csv("x,y\n1,2")
        
        # Good:
        read_csv(I("x,y\n1,2"))


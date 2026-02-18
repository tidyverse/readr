# read_delim errors on length 0 delimiter (557)

    Code
      read_delim(I("a b\n1 2\n"), delim = "")
    Condition
      Error:
      ! `delim` must be at least one character, use `read_table()` for whitespace delimited input.

# literal data without I() emits deprecation warning (#1611)

    Code
      x <- read_csv("x,y\n1,2", show_col_types = FALSE)
    Condition <lifecycle_warning_deprecated>
      Warning:
      The `file` argument of `read_csv()` should use `I()` for literal data as of readr 2.2.0.
        
        # Bad (for example):
        read_csv("x,y\n1,2")
        
        # Good:
        read_csv(I("x,y\n1,2"))

---

    Code
      x <- read_csv2("x;y\n1;2", show_col_types = FALSE)
    Message <cliMessage>
      i Using "','" as decimal and "'.'" as grouping mark. Use `read_delim()` for more control.
    Condition <lifecycle_warning_deprecated>
      Warning:
      The `file` argument of `read_csv2()` should use `I()` for literal data as of readr 2.2.0.
        
        # Bad (for example):
        read_csv("x,y\n1,2")
        
        # Good:
        read_csv(I("x,y\n1,2"))

---

    Code
      x <- read_tsv("x\ty\n1\t2", show_col_types = FALSE)
    Condition <lifecycle_warning_deprecated>
      Warning:
      The `file` argument of `read_tsv()` should use `I()` for literal data as of readr 2.2.0.
        
        # Bad (for example):
        read_csv("x,y\n1,2")
        
        # Good:
        read_csv(I("x,y\n1,2"))

---

    Code
      x <- read_delim("x|y\n1|2", delim = "|", show_col_types = FALSE)
    Condition <lifecycle_warning_deprecated>
      Warning:
      The `file` argument of `read_delim()` should use `I()` for literal data as of readr 2.2.0.
        
        # Bad (for example):
        read_csv("x,y\n1,2")
        
        # Good:
        read_csv(I("x,y\n1,2"))


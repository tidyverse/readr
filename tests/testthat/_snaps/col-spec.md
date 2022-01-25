# print(col_spec) with guess_parser

    Code
      col_spec_standardise("a,b,c\n1,2,3")
    Output
      cols(
        a = col_double(),
        b = col_double(),
        c = col_double()
      )

# print(col_spec) with collector_skip

    Code
      cols_only(a = col_integer(), c = col_integer())
    Output
      cols_only(
        a = col_integer(),
        c = col_integer()
      )

# print(col_spec) with truncated output

    Code
      print(out, n = 2, condense = FALSE)
    Output
      cols(
        .default = col_character(),
        a = col_character(),
        b = col_character()
        # ... with 1 more columns
      )

# print(col_spec) works with dates

    Code
      out
    Output
      cols(
        a = col_date(format = "%Y-%m-%d"),
        b = col_date(format = ""),
        c = col_date(format = "")
      )

# print(col_spec) with unnamed columns

    Code
      col_spec_standardise(col_types = "c_c", col_names = c("a", "c"))
    Output
      cols(
        a = col_character(),
        col_skip(),
        c = col_character()
      )

# print(cols_only()) prints properly

    Code
      cols_only(a = col_character(), c = col_integer())
    Output
      cols_only(
        a = col_character(),
        c = col_integer()
      )

# print(cols_condense(col_spec)) condenses the spec

    Code
      cols_condense(col_spec_standardise("a,b,c,d\n1,2,3,a"))
    Output
      cols(
        .default = col_double(),
        d = col_character()
      )

---

    Code
      cols_condense(col_spec_standardise("a,b,c,d\n1,2,3,4"))
    Output
      cols(
        .default = col_double()
      )

# print(col_spec) with no columns specified

    Code
      cols()
    Output
      cols()

---

    Code
      cols(.default = col_character())
    Output
      cols(
        .default = col_character()
      )

# print(col_spec) and condense edge cases

    Code
      print(cols(a = col_integer(), b = col_integer(), c = col_double()), n = 1,
      condense = TRUE, colour = FALSE)
    Output
      cols(
        .default = col_integer(),
        c = col_double()
      )

# print(col_spec) with colors

    cols(
      a = [32mcol_double()[39m,
      b = [32mcol_integer()[39m,
      c = [33mcol_logical()[39m,
      d = [31mcol_character()[39m,
      e = [34mcol_date(format = "")[39m,
      f = [34mcol_datetime(format = "")[39m,
      g = [34mcol_time(format = "")[39m,
      h = [31mcol_factor(levels = NULL, ordered = FALSE, include_na = FALSE)[39m,
      i = col_skip()
    )

# non-syntatic names are escaped

    Code
      col_spec_standardise("a b,_c,1,a`b\n1,2,3,4")
    Output
      cols(
        `a b` = col_double(),
        `_c` = col_double(),
        `1` = col_double(),
        `a\`b` = col_double()
      )

# long spec declarations can be formatted

    Code
      cols(a = col_factor(levels = c("apple", "pear", "banana", "peach", "apricot",
        "orange", "plum"), ordered = TRUE))
    Output
      cols(
        a = col_factor(levels = c("apple", "pear", "banana", "peach", "apricot", "orange", "plum"
          ), ordered = TRUE, include_na = FALSE)
      )


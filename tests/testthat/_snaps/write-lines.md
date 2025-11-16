# write_file errors if given a character vector of length != 1

    Code
      write_file(character(), tmp)
    Condition
      Error:
      ! Expected string vector of length 1

---

    Code
      write_file(c("foo", "bar"), tmp)
    Condition
      Error:
      ! Expected string vector of length 1


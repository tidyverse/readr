# read_builtin works

    Code
      read_builtin(AirPassengers, "datasets")
    Condition
      Error:
      ! `x` must be a string.

---

    Code
      read_builtin("nasa", "readr")
    Condition
      Error:
      ! data set 'nasa' not found

---

    Code
      read_builtin("starwars")
    Condition
      Error:
      ! data set 'starwars' not found


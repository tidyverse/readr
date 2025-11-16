# can catch faulty system time zones

    Code
      locale(tz = "")
    Condition
      Error:
      ! Unknown TZ foo

# Invalid formats error

    Code
      parse_date("2020-11-17", "%%Y-%m-%d")
    Condition
      Error:
      ! Unsupported format %%Y-%m-%d


# readr 0.1.0.9000

* In `write_csv()`, only use quotes when they're actually needed (#116)

* When guessing field types, and there's no information to go on, use
  character instead of logical (#124, #128).

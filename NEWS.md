# readr 0.1.0.9000

* `read_delim()` now defaults to `escape_backslash = FALSE` and 
`escape_double = TRUE` for consistency.  
  
* Convenient wrapper around base::saveRDS `write_rds()` for saving a single R 
  object (#140, @nicolasCoutin).  
  
* readr now provides `write_delim()` and `write_tsv()` (#135).

* In `write_csv()`, only use quotes when they're actually needed (#116).
  Write the same amount of precision as used by `as.character()` (#117).
  Format POSIXt vectors in ISO8601 compatible format (#134).
  
* Date time columns are no longer incorrectly read as date columns (#136).

* When guessing field types, and there's no information to go on, use
  character instead of logical (#124, #128).

* Compound formats %D, %F, %R, %X, %T, %x are now parsed correctly, instead of
  using the ISO8601 parser (#178, @kmillar)

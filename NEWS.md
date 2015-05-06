# readr 0.1.0.9000

  
* Convenient wrapper around base::saveRDS `write_rds()` for saving a single R 
  object (#140, @nicolasCoutin).  
  
* readr now provides `write_delim()` and `write_tsv()` (#135).

* In `write_csv()`, only use quotes when they're actually needed (#116).
  Write the same amount of precision as used by `as.character()` (#117).
  Format POSIXt vectors in ISO8601 compatible format (#134).
  
* Date time columns are no longer incorrectly read as date columns (#136).

* When guessing field types, and there's no information to go on, use
  character instead of logical (#124, #128).


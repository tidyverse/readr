# readr 0.1.1.9000

* If `read_delim()`, `n_max` now also affects the number of rows read to 
  guess the column types (#224).

* fixed minor double negation bug in `fwf_empty()` causing stopifnot on `col_names` if it was at right length (#222).

* `col_euro_double()` and `parse_euro_double()` now handle negative values 
  (#213).

* Use R's platform independent `iconv` wrapper (#149).

* `write_csv()` no longer fails silently if it can't open the target for
  writing (#193, #172).

* Concise `col_types` specification now understands `?` (guess the type) and
  `-` skip the column (#188).

* Date time parsing now understands `%p` to parse AM/PM (and am/pm) (#126).

* `read_delim()` now defaults to `escape_backslash = FALSE` and 
  `escape_double = TRUE` for consistency.  
  
* `write_rds()` and `read_rds()` wrap around `readRDS()` and `saveRDS()`
  (#140, @nicolasCoutin).
  
* readr now provides `write_delim()` and `write_tsv()` (#135).

* In `write_csv()`, only use quotes when they're actually needed (#116): 
  when the string contains a quote, the delimiter, a new line or NA.
  Write the same amount of precision as used by `as.character()` (#117).
  Format POSIXt vectors in ISO8601 compatible format (#134).
  
* Date time columns are no longer incorrectly read as date columns (#136).
  ISO8601 dates no longer accept partial dates (e.g. 19, 1900, 1900-01).
  These triggered common false positives and after re-reading the spec,
  I believe they actually refer to periods of time, and should not be translated
  in to a specific instant (#228)

* When guessing field types, and there's no information to go on, use
  character instead of logical (#124, #128).

* Multiple strings can now be specified to indicate missing values (#125), and
  the default for missing strings has been changed to `na = c("", "NA")`.
  Specifying `na = ""` now works as expected with character columns (#114).
  
* `read_*()` methods now throw a warning instead of an error is `col_types`
  specifies type for a non-existant column (#145, @alyst).

* Compound formats %D, %F, %R, %X, %T, %x are now parsed correctly, instead of
  using the ISO8601 parser (#178, @kmillar)
  
* Local (non-UTC) times with and without daylight savings are now parsed
  correctly (#120, @andres-s).

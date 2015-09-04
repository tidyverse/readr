# readr 0.1.1.9000

* `read_lines()` gains a progress bar.

* `read_lines()` estimates the number of lines in the file, considerably
  speeding up the reading of large files (60s -> 15s for 1.5 Gb file)

* Specifying the wrong number of column names, or the having rows which
  are different lengths now generates a warning, rather than an error (#189).

* The first five problems are printing out in the problems warning message.

* `type_convert()` gains `NA` and `trim_ws` arguments, and removes missing
  values before determining column types (#)

* `read_delim()` etc gains a `trim_ws` argument that controls whether leading
  and trailing whitespace is automatically removed. It defaults to `TRUE`. (#137)
  
* `parse_*` gain a `na` argument that allows you to specify which values should
  be converted to missing.

* Month and abbreviated month name formats (`%b` and `%B`) now ignore
  case when matching (#219).

* `count_fields()` starts counting from 1, not 0 (#200).

* `write_delim()` gains `na` argument to specify how missing values should be
  written (#187)

* Integer and double parsing is stricter. Previously "3d" was parsed as 
  3 with a warning, now it returns NA (#221)

* If `read_delim()`, `n_max` now also affects the number of rows read to 
  guess the column types (#224).

* fixed minor double negation bug in `fwf_empty()` causing stopifnot on 
  `col_names` if it was at right length (#186, #222).

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

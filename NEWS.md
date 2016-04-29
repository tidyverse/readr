# readr 0.2.2.9000

* Quick hack to return something instead of NA for missing column names
  (#318)

# readr 0.2.2

* Fix bug when checking empty values for missingness (caused valgrind issue
  and random crashes).

# readr 0.2.1

* Fixes so that readr works on Solaris.

# readr 0.2.0

## Internationalisation

readr now has a strategy for dealing with settings that vary from place to place: locales. The default locale is still US centric (because R itself is), but you can now easily override the default timezone, decimal separator, grouping mark, day & month names, date format, and encoding. This has lead to a number of changes:

* `read_csv()`, `read_tsv()`, `read_fwf()`, `read_table()`, 
  `read_lines()`, `read_file()`, `type_convert()`, `parse_vector()` 
  all gain a `locale` argument.
  
* `locale()` controls all the input settings that vary from place-to-place.

* `col_euro_double()` and `parse_euro_double()` have been deprecated.
  Use the `decimal_mark` parameter to `locale()` instead.
  
* The default encoding is now UTF-8. To load files that are not 
  in UTF-8, set the `encoding` parameter of the `locale()` (#40).
  New `guess_encoding()` function uses stringi to help you figure out the
  encoding of a file.
  
* `parse_datetime()` and `parse_date()` with `%B` and `%b` use the
  month names (full and abbreviate) defined in the locale (#242).
  They also inherit the tz from the locale, rather than using an
  explicit `tz` parameter.
  
See `vignette("locales")` for more details.

## File parsing improvements

* `cols()` lets you pick the default column type for columns not otherwise
  explicitly named (#148). You can refer to parsers either with their full 
  name (e.g. `col_character()`) or their one letter abbreviation (e.g. `c`).

* `cols_only()` allows you to load only named columns. You can also choose to 
  override the default column type in `cols()` (#72).

* `read_fwf()` is now much more careful with new lines. If a line is too short, 
  you'll get a warning instead of a silent mistake (#166, #254). Additionally,
  the last column can now be ragged: the width of the last field is silently 
  extended until it hits the next line break (#146). This appears to be a
  common feature of "fixed" width files in the wild.

* In `read_csv()`, `read_tsv()`, `read_delim()` etc:
 
  * `comment` argument allows you to ignore comments (#68).
  
  * `trim_ws` argument controls whether leading and trailing whitespace is 
    removed. It defaults to `TRUE` (#137).
  
  * Specifying the wrong number of column names, or having rows with an 
    unexpected number of columns, generates a warning, rather than an error 
    (#189).

  * Multiple NA values can be specified by passing a character vector to 
    `na` (#125). The default has been changed to `na = c("", "NA")`. Specifying 
    `na = ""` now works as expected with character columns (#114).

## Column parsing improvements

Readr gains `vignette("column-types")` which describes how the defaults work and how to override them (#122).

* `parse_character()` gains better support for embedded nulls: any characters 
  after the first null are dropped with a warning (#202).

* `parse_integer()` and `parse_double()` no longer silently ignore trailing
  letters after the number (#221).

* New `parse_time()` and `col_time()` allows you to parse times (hours, minutes, 
  seconds) into number of seconds since midnight. If the format is omitted, it 
  uses a flexible parser that looks for hours, then optional colon, then 
  minutes, then optional colon, then optional seconds, then optional am/pm 
  (#249).

* `parse_date()` and `parse_datetime()`: 

    * `parse_datetime()` no longer incorrectly reads partial dates (e.g. 19, 
      1900, 1900-01) (#136). These triggered common false positives and after 
      re-reading the ISO8601 spec, I believe they actually refer to periods of 
      time, and should not be translated in to a specific instant (#228). 
      
    * Compound formats "%D", "%F", "%R", "%X", "%T", "%x" are now parsed 
      correctly, instead of using the  ISO8601 parser (#178, @kmillar). 
      
    * "%." now requires a non-digit. New "%+" skips one or more non-digits.
      
    * You can now use `%p` to refer to AM/PM (and am/pm) (#126).
      
    * `%b` and `%B` formats (month and abbreviated month name) ignore case 
      when matching (#219).
      
    * Local (non-UTC) times with and without daylight savings are now parsed
      correctly (#120, @andres-s).

* `parse_number()` is a somewhat flexible numeric parser designed to read
  currencies and percentages. It only reads the first number from a string
  (using the grouping mark defined by the locale). 
  
* `parse_numeric()` has been deprecated because the name is confusing - 
  it's a flexible number parser, not a parser of "numerics", as R collectively
  calls doubles and integers. Use `parse_number()` instead. 

As well as improvements to the parser, I've also made a number of tweaks to the heuristics that readr uses to guess column types:

* New `parse_guess()` and `col_guess()` to explicitly guess column type.

* Bumped up row inspection for column typing guessing from 100 to 1000.

* The heuristics for guessing `col_integer()` and `col_double()` are stricter.
  Numbers with leading zeros now default to being parsed as text, rather than
  as integers/doubles (#266).
  
* A column is guessed as `col_number()` only if it parses as a regular number
  when you ignoring the grouping marks.

## Minor improvements and bug fixes

* Now use R's platform independent `iconv` wrapper, thanks to BDR (#149).

* Pathological zero row inputs (due to empty input, `skip` or `n_max`) now
  return zero row data frames (#119).
  
* When guessing field types, and there's no information to go on, use
  character instead of logical (#124, #128).

* Concise `col_types` specification now understands `?` (guess) and
  `-` (skip) (#188).

* `count_fields()` starts counting from 1, not 0 (#200).

* `format_csv()` and `format_delim()` make it easy to render a csv or 
  delimited file into a string.

* `fwf_empty()` now works correctly when `col_names` supplied (#186, #222).

* `parse_*()` gains a `na` argument that allows you to specify which values 
  should be converted to missing.

* `problems()` now reports column names rather than column numbers (#143).
  Whenever there is a problem, the first five problems are printing out 
  in a warning message, so you can more easily see what's wrong.

* `read_*()` throws a warning instead of an error is `col_types`
  specifies a non-existent column (#145, @alyst).

* `read_*()` can read from a remote gz compressed file (#163).

* `read_delim()` defaults to `escape_backslash = FALSE` and 
  `escape_double = TRUE` for consistency. `n_max` also affects the number 
  of rows read to guess the column types (#224).

* `read_lines()` gains a progress bar. It now also correctly checks for 
  interrupts every 500,000 lines so you can interrupt long running jobs.
  It also correctly estimates the number of lines in the file, considerably
  speeding up the reading of large files (60s -> 15s for a 1.5 Gb file).

* `read_lines_raw()` allows you to read a file into a list of raw vectors,
  one element for each line.

* `type_convert()` gains `NA` and `trim_ws` arguments, and removes missing
  values before determining column types.

* `write_csv()`, `write_delim()`, and `write_rds()` all invisably return their
  input so you can use them in a pipe (#290).

* `write_delim()` generalises `write_csv()` to write any delimited format (#135).
  `write_tsv()` is a helpful wrapper for tab separated files.
  
    * Quotes are only used when they're needed (#116): when the string contains 
      a quote, the delimiter, a new line or NA. 
      
    * Double vectors are saved using same amount of precision as 
      `as.character()` (#117). 
      
    * New `na` argument that specifies how missing values should be written 
      (#187)
    
    * POSIXt vectors are saved in a ISO8601 compatible format (#134). 
    
    * No longer fails silently if it can't open the target for 
      writing (#193, #172).

* `write_rds()` and `read_rds()` wrap around `readRDS()` and `saveRDS()`,
  defaulting to no compression (#140, @nicolasCoutin).

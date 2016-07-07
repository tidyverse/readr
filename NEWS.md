# readr 0.2.2.9000

* `write_lines()` function to write a character vector to a file (#302,
  @jimhester).
* Bugfix in `read_line()` which was not properly ignoring embedded null's in
  strings. (#338, @jimhester).

* `locale()` now automatically sets decimal mark if you set the grouping 
  mark. It throws an error if you accidentally set decimal and grouping marks
  to the same character (#450).
* `read_file_raw()` function to read a complete file into a raw vector (#451,
  @jimhester).
* read_fwf() on an empty file returns an empty tibble (#441, @jimhester).

* Named lists can now be used as input to `col_types()` (#401, @jimhester).

* Column specifications are now printed by default when reading, and can be
  retrieved from objects with `spec()` (#314, @jimhester).
* `write_excel_csv()` can be used to write a csv file with a UTF-8 Byte order
  mark included, which allows Excel to detect that it is UTF-8 encoded. (#375,
  @jimhester).

* Parse doubles with `boost::spirit::qi::long_double` to work around a bug in the
  spirit library when parsing large numbers (#412, @jimhester).

* Supports reading into long vectors (#309, @jimhester).
* `default_locale()` now sets the default locale in `readr.default_locale`
  rather than regenerating it for each call. (#416, @jimhester).

* Printing of double values now uses an
  [implementation](https://github.com/juj/MathGeoLib/blob/master/src/Math/grisu3.c)
  of the [grisu3
  algorithm](http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf)
  which speeds up writing of large numeric data frames by ~10X. (#432,
  @jimhester)

* Negative column widths are now allowed in `fwf_widths()` to facilitate
  compatibility with the `widths` argument in `read.fwf()`. (#380, @leeper)
* `type_convert()` now accepts only `NULL` or a `cols` specification for
  `col_types` (#369, @jimhester).
* If `col_types` is too long, it is subsetted correctly. (#372, @jennybc)
* `read_file()`, `read_lines()` and `read_csv()` now return empty objects
  rather than signaling an error when run on an empty file (#356, @jimhester).

* time objects returned by `parse_time()` are now `hms` objects rather than a
  custom `time` class (#409, @jimhester).

* parse_datetime()` and `parse_time()` now support `%I` for 12 hour time
  format (#340, @jimhester).

* The flexible time parser now requires colons between hours and minutes and
  optional seconds. You can explicitly parse without colons by specifying the
  column type like `col_time("%H%M")` (#424, @jimhester).

* `collector_guess()` now guesses time formats as well (#384, @jimhester).

* Fix bug when guessing type for numbers with a trailing character (#316,
  @jimhester).

* Export `collector_guess()` (#377, @jimhester).

* Fix bug when parsing negative number returns a positive value (#308,
  @jimhester).

* Fix bug in `parse_date()` constructing dates based on integer vectors rather
  than numeric vectors (#357, @jimhester).
* Add `na` arguments to `parse_date()` `parse_time()` and `parse_datetime()`
  (#413, @jimhester).
* Fix bug when parsing negative number returns a positive value (#308,
  @jimhester).

* Fix bug when detecting column types for single row files without headers
  (#333, @jimhester).

* Fix bug in `collector_guess()`, single '-' or '.' are now parsed as
  characters rather than numeric (#297, @jimhester).

* Fix bug in `read_fwf()`, it will now properly read a subset of columns.
  If the final column is ragged, supply an NA as the final end `fwf_positions`
  or final width `fwf_widths` position (#353,@ghaarsma).

* readr now imports tibble so that you get consistent `tbl_df` behaviour 
  (#317, #385).

* When column names are insufficient, the added names are numbered correctly and won't be `NA` (#374, @jennybc).

* `write_delim()` and `write_csv()` now invisibly return the input data frame
  as documented (#363).

* `parse_time("NA")` works as expected (#398).

* Quick hack to return something instead of NA for missing column names
  (#318)
  
* Add support for parsing years with col_date("%Y") or col_datetime("%Y") 

* `parse_logical()` now accepts `0`, `1` as well as lowercase `t`, `f`, `true`, `false`. 

* `read_delim()` gains a `trim_ws` argument (#312, noamross)

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

# Tokenizers.

Explicitly create tokenizer objects. Usually you will not call these
function, but will instead use one of the use friendly wrappers like
[`read_csv()`](https://readr.tidyverse.org/reference/read_delim.md).

## Usage

``` r
tokenizer_delim(
  delim,
  quote = "\"",
  na = "NA",
  quoted_na = TRUE,
  comment = "",
  trim_ws = TRUE,
  escape_double = TRUE,
  escape_backslash = FALSE,
  skip_empty_rows = TRUE
)

tokenizer_csv(
  na = "NA",
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip_empty_rows = TRUE
)

tokenizer_tsv(
  na = "NA",
  quoted_na = TRUE,
  quote = "\"",
  comment = "",
  trim_ws = TRUE,
  skip_empty_rows = TRUE
)

tokenizer_line(na = character(), skip_empty_rows = TRUE)

tokenizer_log(trim_ws)

tokenizer_fwf(
  begin,
  end,
  na = "NA",
  comment = "",
  trim_ws = TRUE,
  skip_empty_rows = TRUE
)

tokenizer_ws(na = "NA", comment = "", skip_empty_rows = TRUE)
```

## Arguments

- delim:

  Single character used to separate fields within a record.

- quote:

  Single character used to quote strings.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- quoted_na:

  **\[deprecated\]** Should missing values inside quotes be treated as
  missing values (the default) or strings. This parameter is only
  supported in certain legacy functions (e.g., the `read_*_chunked()`
  functions) or when requesting the legacy first edition parser with
  [`read_delim()`](https://readr.tidyverse.org/reference/read_delim.md)
  and friends.

- comment:

  A string used to identify comments. Any text after the comment
  characters will be silently ignored.

- trim_ws:

  Should leading and trailing whitespace (ASCII spaces and tabs) be
  trimmed from each field before parsing it?

- escape_double:

  Does the file escape quotes by doubling them? i.e. If this option is
  `TRUE`, the value `""""` represents a single quote, `\"`.

- escape_backslash:

  Does the file use backslashes to escape special characters? This is
  more general than `escape_double` as backslashes can be used to escape
  the delimiter character, the quote character, or to add special
  characters like `\\n`.

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

- begin, end:

  Begin and end offsets for each file. These are C++ offsets so the
  first column is column zero, and the ranges are \[begin, end) (i.e
  inclusive-exclusive).

## Examples

``` r
tokenizer_csv()
#> $delim
#> [1] ","
#> 
#> $quote
#> [1] "\""
#> 
#> $na
#> [1] "NA"
#> 
#> $quoted_na
#> [1] TRUE
#> 
#> $comment
#> [1] ""
#> 
#> $trim_ws
#> [1] TRUE
#> 
#> $escape_double
#> [1] TRUE
#> 
#> $escape_backslash
#> [1] FALSE
#> 
#> $skip_empty_rows
#> [1] TRUE
#> 
#> attr(,"class")
#> [1] "tokenizer_delim"
```

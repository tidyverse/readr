# Introduction to readr

The key problem that readr solves is **parsing** a flat file into a
tibble. Parsing is the process of taking a text file and turning it into
a rectangular tibble where each column is the appropriate part. Parsing
takes place in three basic stages:

1.  The flat file is parsed into a rectangular matrix of strings.

2.  The type of each column is determined.

3.  Each column of strings is parsed into a vector of a more specific
    type.

It’s easiest to learn how this works in the opposite order Below, you’ll
learn how the:

1.  **Vector parsers** turn a character vector in to a more specific
    type.

2.  **Column specification** describes the type of each column and the
    strategy readr uses to guess types so you don’t need to supply them
    all.

3.  **Rectangular parsers** turn a flat file into a matrix of rows and
    columns.

Each `parse_*()` is coupled with a `col_*()` function, which will be
used in the process of parsing a complete tibble.

## Vector parsers

It’s easiest to learn the vector parses using `parse_` functions. These
all take a character vector and some options. They return a new vector
the same length as the old, along with an attribute describing any
problems.

### Atomic vectors

[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
and
[`parse_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
are straightforward parsers that produce the corresponding atomic
vector.

``` r
parse_integer(c("1", "2", "3"))
#> [1] 1 2 3
parse_double(c("1.56", "2.34", "3.56"))
#> [1] 1.56 2.34 3.56
parse_logical(c("true", "false"))
#> [1]  TRUE FALSE
```

By default, readr expects `.` as the decimal mark and `,` as the
grouping mark. You can override this default using
[`locale()`](https://readr.tidyverse.org/dev/reference/locale.md), as
described in
[`vignette("locales")`](https://readr.tidyverse.org/dev/articles/locales.md).

### Flexible numeric parser

[`parse_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
and
[`parse_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
are strict: the input string must be a single number with no leading or
trailing characters.
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
is more flexible: it ignores non-numeric prefixes and suffixes, and
knows how to deal with grouping marks. This makes it suitable for
reading currencies and percentages:

``` r
parse_number(c("0%", "10%", "150%"))
#> [1]   0  10 150
parse_number(c("$1,234.5", "$12.45"))
#> [1] 1234.50   12.45
```

### Date/times

readr supports three types of date/time data:

- dates: number of days since 1970-01-01.
- times: number of seconds since midnight.
- datetimes: number of seconds since midnight 1970-01-01.

``` r
parse_datetime("2010-10-01 21:45")
#> [1] "2010-10-01 21:45:00 UTC"
parse_date("2010-10-01")
#> [1] "2010-10-01"
parse_time("1:00pm")
#> 13:00:00
```

Each function takes a `format` argument which describes the format of
the string. If not specified, it uses a default value:

- [`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  recognises [ISO8601](https://en.wikipedia.org/wiki/ISO_8601)
  datetimes.

- [`parse_date()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  uses the `date_format` specified by the
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md). The
  default value is `%AD` which uses an automatic date parser that
  recognises dates of the format `Y-m-d` or `Y/m/d`.

- [`parse_time()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md)
  uses the `time_format` specified by the
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md). The
  default value is `%At` which uses an automatic time parser that
  recognises times of the form `H:M` optionally followed by seconds and
  am/pm.

In most cases, you will need to supply a `format`, as documented in
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md):

``` r
parse_datetime("1 January, 2010", "%d %B, %Y")
#> [1] "2010-01-01 UTC"
parse_datetime("02/02/15", "%m/%d/%y")
#> [1] "2015-02-02 UTC"
```

### Factors

When reading a column that has a known set of values, you can read
directly into a factor.
[`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md)
will generate a warning if a value is not in the supplied levels.

``` r
parse_factor(c("a", "b", "a"), levels = c("a", "b", "c"))
#> [1] a b a
#> Levels: a b c
parse_factor(c("a", "b", "d"), levels = c("a", "b", "c"))
#> Warning: 1 parsing failure.
#> row col           expected actual
#>   3  -- value in level set      d
#> [1] a    b    <NA>
#> attr(,"problems")
#> # A tibble: 1 × 4
#>     row   col expected           actual
#>   <int> <int> <chr>              <chr> 
#> 1     3    NA value in level set d     
#> Levels: a b c
```

## Column specification

It would be tedious if you had to specify the type of every column when
reading a file. Instead readr, uses some heuristics to guess the type of
each column. You can access these results yourself using
[`guess_parser()`](https://readr.tidyverse.org/dev/reference/parse_guess.md):

``` r
guess_parser(c("a", "b", "c"))
#> [1] "character"
guess_parser(c("1", "2", "3"))
#> [1] "double"
guess_parser(c("1,000", "2,000", "3,000"))
#> [1] "number"
guess_parser(c("2001/10/10"))
#> [1] "date"
```

The guessing policies are described in the documentation for the
individual functions. Guesses are fairly strict. For example, we don’t
guess that currencies are numbers, even though we can parse them:

``` r
guess_parser("$1,234")
#> [1] "character"
parse_number("$1,234")
#> [1] 1234
```

There are two parsers that will never be guessed:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md)
and
[`col_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md).
You will always need to supply these explicitly.

You can see the specification that readr would generate for a column
file by using
[`spec_csv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md),
[`spec_tsv()`](https://readr.tidyverse.org/dev/reference/spec_delim.md)
and so on:

``` r
x <- spec_csv(readr_example("challenge.csv"))
```

For bigger files, you can often make the specification simpler by
changing the default column type using
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md)

``` r
mtcars_spec <- spec_csv(readr_example("mtcars.csv"))
mtcars_spec
#> cols(
#>   mpg = col_double(),
#>   cyl = col_double(),
#>   disp = col_double(),
#>   hp = col_double(),
#>   drat = col_double(),
#>   wt = col_double(),
#>   qsec = col_double(),
#>   vs = col_double(),
#>   am = col_double(),
#>   gear = col_double(),
#>   carb = col_double()
#> )

cols_condense(mtcars_spec)
#> cols(
#>   .default = col_double()
#> )
```

By default readr only looks at the first 1000 rows. This keeps file
parsing speedy, but can generate incorrect guesses. For example, in
`challenge.csv` the column types change in row 1001, so readr guesses
the wrong types. One way to resolve the problem is to increase the
number of rows:

``` r
x <- spec_csv(readr_example("challenge.csv"), guess_max = 1001)
```

Another way is to manually specify the `col_type`, as described below.

## Rectangular parsers

readr comes with five parsers for rectangular file formats:

- [`read_csv()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  and
  [`read_csv2()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  for csv files
- [`read_tsv()`](https://readr.tidyverse.org/dev/reference/read_delim.md)
  for tabs separated files
- [`read_fwf()`](https://readr.tidyverse.org/dev/reference/read_fwf.md)
  for fixed-width files
- [`read_log()`](https://readr.tidyverse.org/dev/reference/read_log.md)
  for web log files

Each of these functions firsts calls `spec_xxx()` (as described above),
and then parses the file according to that column specification:

``` r
df1 <- read_csv(readr_example("challenge.csv"))
#> Rows: 2000 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl  (1): x
#> date (1): y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
```

The rectangular parsing functions almost always succeed; they’ll only
fail if the format is severely messed up. Instead, readr will generate a
data frame of problems. The first few will be printed out, and you can
access them all with
[`problems()`](https://readr.tidyverse.org/dev/reference/problems.md):

``` r
problems(df1)
#> # A tibble: 0 × 5
#> # ℹ 5 variables: row <int>, col <int>, expected <chr>, actual <chr>,
#> #   file <chr>
```

You’ve already seen one way of handling bad guesses: increasing the
number of rows used to guess the type of each column.

``` r
df2 <- read_csv(readr_example("challenge.csv"), guess_max = 1001)
#> Rows: 2000 Columns: 2
#> ── Column specification ───────────────────────────────────────────────
#> Delimiter: ","
#> dbl  (1): x
#> date (1): y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
```

Another approach is to manually supply the column specification.

### Overriding the defaults

In the previous examples, you may have noticed that readr printed the
column specification that it used to parse the file:

``` r
#> Parsed with column specification:
#> cols(
#>   x = col_integer(),
#>   y = col_character()
#> )
```

You can also access it after the fact using
[`spec()`](https://readr.tidyverse.org/dev/reference/spec.md):

``` r
spec(df1)
#> cols(
#>   x = col_double(),
#>   y = col_date(format = "")
#> )
spec(df2)
#> cols(
#>   x = col_double(),
#>   y = col_date(format = "")
#> )
```

(This also allows you to access the full column specification if you’re
reading a very wide file. By default, readr will only print the
specification of the first 20 columns.)

If you want to manually specify the column types, you can start by
copying and pasting this code, and then tweaking it fix the parsing
problems.

``` r
df3 <- read_csv(
  readr_example("challenge.csv"), 
  col_types = list(
    x = col_double(),
    y = col_date(format = "")
  )
)
```

In general, it’s good practice to supply an explicit column
specification. It is more work, but it ensures that you get warnings if
the data changes in unexpected ways. To be really strict, you can use
`stop_for_problems(df3)`. This will throw an error if there are any
parsing problems, forcing you to fix those problems before proceeding
with the analysis.

### Available column specifications

The available specifications are: (with string abbreviations in
brackets)

- [`col_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  \[l\], containing only `T`, `F`, `TRUE` or `FALSE`.
- [`col_integer()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  \[i\], integers.
- [`col_double()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  \[d\], doubles.
- [`col_character()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md)
  \[c\], everything else.
- `col_factor(levels, ordered)` \[f\], a fixed set of values.
- `col_date(format = "")` \[D\]: with the locale’s `date_format`.
- `col_time(format = "")` \[t\]: with the locale’s `time_format`.
- `col_datetime(format = "")` \[T\]: ISO8601 date times
- [`col_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  \[n\], numbers containing the `grouping_mark`
- [`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md)
  \[\_, -\], don’t import this column.
- [`col_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  \[?\], parse using the “best” type based on the input.

Use the `col_types` argument to override the default choices. There are
two ways to use it:

- With a string: `"dc__d"`: read first column as double, second as
  character, skip the next two and read the last column as a double.
  (There’s no way to use this form with types that take additional
  parameters.)

- With a (named) list of col objects:

  ``` r
  read_csv("iris.csv", col_types = list(
    Sepal.Length = col_double(),
    Sepal.Width = col_double(),
    Petal.Length = col_double(),
    Petal.Width = col_double(),
    Species = col_factor(c("setosa", "versicolor", "virginica"))
  ))
  ```

  Or, with their abbreviations:

  ``` r
    read_csv("iris.csv", col_types = list(
    Sepal.Length = "d",
    Sepal.Width = "d",
    Petal.Length = "d",
    Petal.Width = "d",
    Species = col_factor(c("setosa", "versicolor", "virginica"))
  ))
  ```

Any omitted columns will be parsed automatically, so the previous call
will lead to the same result as:

``` r
read_csv("iris.csv", col_types = list(
  Species = col_factor(c("setosa", "versicolor", "virginica")))
)
```

You can also set a default type that will be used instead of relying on
the automatic detection for columns you don’t specify:

``` r
read_csv("iris.csv", col_types = list(
  Species = col_factor(c("setosa", "versicolor", "virginica")),
  .default = col_double())
)
```

If you only want to read specified columns, use
[`cols_only()`](https://readr.tidyverse.org/dev/reference/cols.md):

``` r
read_csv("iris.csv", col_types = cols_only(
  Species = col_factor(c("setosa", "versicolor", "virginica")))
)
```

### Output

The output of all these functions is a tibble. Note that characters are
never automatically converted to factors (i.e. no more
`stringsAsFactors = FALSE`) and column names are left as is, not munged
into valid R identifiers (i.e. there is no `check.names = TRUE`). Row
names are never set.

Attributes store the column specification
([`spec()`](https://readr.tidyverse.org/dev/reference/spec.md)) and any
parsing problems
([`problems()`](https://readr.tidyverse.org/dev/reference/problems.md)).

# Create column specification

`cols()` includes all columns in the input data, guessing the column
types as the default. `cols_only()` includes only the columns you
explicitly specify, skipping the rest. In general you can substitute
[`list()`](https://rdrr.io/r/base/list.html) for `cols()` without
changing the behavior.

## Usage

``` r
cols(..., .default = col_guess())

cols_only(...)
```

## Arguments

- ...:

  Either column objects created by `col_*()`, or their abbreviated
  character names (as described in the `col_types` argument of
  [`read_delim()`](https://readr.tidyverse.org/dev/reference/read_delim.md)).
  If you're only overriding a few columns, it's best to refer to columns
  by name. If not named, the column types must match the column names
  exactly.

- .default:

  Any named columns not explicitly overridden in `...` will be read with
  this column type.

## Details

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

- `col_date(format = "")` \[D\]: with the locale's `date_format`.

- `col_time(format = "")` \[t\]: with the locale's `time_format`.

- `col_datetime(format = "")` \[T\]: ISO8601 date times

- [`col_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md)
  \[n\], numbers containing the `grouping_mark`

- [`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md)
  \[\_, -\], don't import this column.

- [`col_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md)
  \[?\], parse using the "best" type based on the input.

## See also

Other parsers:
[`col_skip()`](https://readr.tidyverse.org/dev/reference/col_skip.md),
[`cols_condense()`](https://readr.tidyverse.org/dev/reference/spec.md),
[`parse_datetime()`](https://readr.tidyverse.org/dev/reference/parse_datetime.md),
[`parse_factor()`](https://readr.tidyverse.org/dev/reference/parse_factor.md),
[`parse_guess()`](https://readr.tidyverse.org/dev/reference/parse_guess.md),
[`parse_logical()`](https://readr.tidyverse.org/dev/reference/parse_atomic.md),
[`parse_number()`](https://readr.tidyverse.org/dev/reference/parse_number.md),
[`parse_vector()`](https://readr.tidyverse.org/dev/reference/parse_vector.md)

## Examples

``` r
cols(a = col_integer())
#> cols(
#>   a = col_integer()
#> )
cols_only(a = col_integer())
#> cols_only(
#>   a = col_integer()
#> )

# You can also use the standard abbreviations
cols(a = "i")
#> cols(
#>   a = col_integer()
#> )
cols(a = "i", b = "d", c = "_")
#> cols(
#>   a = col_integer(),
#>   b = col_double(),
#>   c = col_skip()
#> )

# You can also use multiple sets of column definitions by combining
# them like so:

t1 <- cols(
  column_one = col_integer(),
  column_two = col_number()
)

t2 <- cols(
  column_three = col_character()
)

t3 <- t1
t3$cols <- c(t1$cols, t2$cols)
t3
#> cols(
#>   column_one = col_integer(),
#>   column_two = col_number(),
#>   column_three = col_character()
#> )
```

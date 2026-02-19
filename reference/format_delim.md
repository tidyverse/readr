# Convert a data frame to a delimited string

These functions are equivalent to
[`write_csv()`](https://readr.tidyverse.org/reference/write_delim.md)
etc., but instead of writing to disk, they return a string.

## Usage

``` r
format_delim(
  x,
  delim,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n"
)

format_csv(
  x,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n"
)

format_csv2(
  x,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n"
)

format_tsv(
  x,
  na = "NA",
  append = FALSE,
  col_names = !append,
  quote = c("needed", "all", "none"),
  escape = c("double", "backslash", "none"),
  eol = "\n"
)
```

## Arguments

- x:

  A data frame.

- delim:

  Delimiter used to separate values. Defaults to `" "` for
  [`write_delim()`](https://readr.tidyverse.org/reference/write_delim.md),
  `","` for
  [`write_excel_csv()`](https://readr.tidyverse.org/reference/write_delim.md)
  and `";"` for
  [`write_excel_csv2()`](https://readr.tidyverse.org/reference/write_delim.md).
  Must be a single character.

- na:

  String used for missing values. Defaults to NA. Missing values will
  never be quoted; strings with the same value as `na` will always be
  quoted.

- append:

  If `FALSE`, will overwrite existing file. If `TRUE`, will append to
  existing file. In both cases, if the file does not exist a new file is
  created.

- col_names:

  If `FALSE`, column names will not be included at the top of the file.
  If `TRUE`, column names will be included. If not specified,
  `col_names` will take the opposite value given to `append`.

- quote:

  How to handle fields which contain characters that need to be quoted.

  - `needed` - Values are only quoted if needed: if they contain a
    delimiter, quote, or newline.

  - `all` - Quote all fields.

  - `none` - Never quote fields.

- escape:

  The type of escape to use when quotes are in the data.

  - `double` - quotes are escaped by doubling them.

  - `backslash` - quotes are escaped by a preceding backslash.

  - `none` - quotes are not escaped.

- eol:

  The end of line character to use. Most commonly either `"\n"` for Unix
  style newlines, or `"\r\n"` for Windows style newlines.

## Value

A string.

## Output

Factors are coerced to character. Doubles are formatted to a decimal
string using the grisu3 algorithm. `POSIXct` values are formatted as
ISO8601 with a UTC timezone *Note: `POSIXct` objects in local or non-UTC
timezones will be converted to UTC time before writing.*

All columns are encoded as UTF-8.
[`write_excel_csv()`](https://readr.tidyverse.org/reference/write_delim.md)
and
[`write_excel_csv2()`](https://readr.tidyverse.org/reference/write_delim.md)
also include a [UTF-8 Byte order
mark](https://en.wikipedia.org/wiki/Byte_order_mark) which indicates to
Excel the csv is UTF-8 encoded.

[`write_excel_csv2()`](https://readr.tidyverse.org/reference/write_delim.md)
and `write_csv2` were created to allow users with different locale
settings to save .csv files using their default settings (e.g. `;` as
the column separator and `,` as the decimal separator). This is common
in some European countries.

Values are only quoted if they contain a comma, quote or newline.

The `write_*()` functions will automatically compress outputs if an
appropriate extension is given. Three extensions are currently
supported: `.gz` for gzip compression, `.bz2` for bzip2 compression and
`.xz` for lzma compression. See the examples for more information.

## References

Florian Loitsch, Printing Floating-Point Numbers Quickly and Accurately
with Integers, PLDI '10,
<http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf>

## Examples

``` r
# format_()* functions are useful for testing and reprexes
cat(format_csv(mtcars))
#> mpg,cyl,disp,hp,drat,wt,qsec,vs,am,gear,carb
#> 21,6,160,110,3.9,2.62,16.46,0,1,4,4
#> 21,6,160,110,3.9,2.875,17.02,0,1,4,4
#> 22.8,4,108,93,3.85,2.32,18.61,1,1,4,1
#> 21.4,6,258,110,3.08,3.215,19.44,1,0,3,1
#> 18.7,8,360,175,3.15,3.44,17.02,0,0,3,2
#> 18.1,6,225,105,2.76,3.46,20.22,1,0,3,1
#> 14.3,8,360,245,3.21,3.57,15.84,0,0,3,4
#> 24.4,4,146.7,62,3.69,3.19,20,1,0,4,2
#> 22.8,4,140.8,95,3.92,3.15,22.9,1,0,4,2
#> 19.2,6,167.6,123,3.92,3.44,18.3,1,0,4,4
#> 17.8,6,167.6,123,3.92,3.44,18.9,1,0,4,4
#> 16.4,8,275.8,180,3.07,4.07,17.4,0,0,3,3
#> 17.3,8,275.8,180,3.07,3.73,17.6,0,0,3,3
#> 15.2,8,275.8,180,3.07,3.78,18,0,0,3,3
#> 10.4,8,472,205,2.93,5.25,17.98,0,0,3,4
#> 10.4,8,460,215,3,5.424,17.82,0,0,3,4
#> 14.7,8,440,230,3.23,5.345,17.42,0,0,3,4
#> 32.4,4,78.7,66,4.08,2.2,19.47,1,1,4,1
#> 30.4,4,75.7,52,4.93,1.615,18.52,1,1,4,2
#> 33.9,4,71.1,65,4.22,1.835,19.9,1,1,4,1
#> 21.5,4,120.1,97,3.7,2.465,20.01,1,0,3,1
#> 15.5,8,318,150,2.76,3.52,16.87,0,0,3,2
#> 15.2,8,304,150,3.15,3.435,17.3,0,0,3,2
#> 13.3,8,350,245,3.73,3.84,15.41,0,0,3,4
#> 19.2,8,400,175,3.08,3.845,17.05,0,0,3,2
#> 27.3,4,79,66,4.08,1.935,18.9,1,1,4,1
#> 26,4,120.3,91,4.43,2.14,16.7,0,1,5,2
#> 30.4,4,95.1,113,3.77,1.513,16.9,1,1,5,2
#> 15.8,8,351,264,4.22,3.17,14.5,0,1,5,4
#> 19.7,6,145,175,3.62,2.77,15.5,0,1,5,6
#> 15,8,301,335,3.54,3.57,14.6,0,1,5,8
#> 21.4,4,121,109,4.11,2.78,18.6,1,1,4,2
cat(format_tsv(mtcars))
#> mpg  cyl disp    hp  drat    wt  qsec    vs  am  gear    carb
#> 21   6   160 110 3.9 2.62    16.46   0   1   4   4
#> 21   6   160 110 3.9 2.875   17.02   0   1   4   4
#> 22.8 4   108 93  3.85    2.32    18.61   1   1   4   1
#> 21.4 6   258 110 3.08    3.215   19.44   1   0   3   1
#> 18.7 8   360 175 3.15    3.44    17.02   0   0   3   2
#> 18.1 6   225 105 2.76    3.46    20.22   1   0   3   1
#> 14.3 8   360 245 3.21    3.57    15.84   0   0   3   4
#> 24.4 4   146.7   62  3.69    3.19    20  1   0   4   2
#> 22.8 4   140.8   95  3.92    3.15    22.9    1   0   4   2
#> 19.2 6   167.6   123 3.92    3.44    18.3    1   0   4   4
#> 17.8 6   167.6   123 3.92    3.44    18.9    1   0   4   4
#> 16.4 8   275.8   180 3.07    4.07    17.4    0   0   3   3
#> 17.3 8   275.8   180 3.07    3.73    17.6    0   0   3   3
#> 15.2 8   275.8   180 3.07    3.78    18  0   0   3   3
#> 10.4 8   472 205 2.93    5.25    17.98   0   0   3   4
#> 10.4 8   460 215 3   5.424   17.82   0   0   3   4
#> 14.7 8   440 230 3.23    5.345   17.42   0   0   3   4
#> 32.4 4   78.7    66  4.08    2.2 19.47   1   1   4   1
#> 30.4 4   75.7    52  4.93    1.615   18.52   1   1   4   2
#> 33.9 4   71.1    65  4.22    1.835   19.9    1   1   4   1
#> 21.5 4   120.1   97  3.7 2.465   20.01   1   0   3   1
#> 15.5 8   318 150 2.76    3.52    16.87   0   0   3   2
#> 15.2 8   304 150 3.15    3.435   17.3    0   0   3   2
#> 13.3 8   350 245 3.73    3.84    15.41   0   0   3   4
#> 19.2 8   400 175 3.08    3.845   17.05   0   0   3   2
#> 27.3 4   79  66  4.08    1.935   18.9    1   1   4   1
#> 26   4   120.3   91  4.43    2.14    16.7    0   1   5   2
#> 30.4 4   95.1    113 3.77    1.513   16.9    1   1   5   2
#> 15.8 8   351 264 4.22    3.17    14.5    0   1   5   4
#> 19.7 6   145 175 3.62    2.77    15.5    0   1   5   6
#> 15   8   301 335 3.54    3.57    14.6    0   1   5   8
#> 21.4 4   121 109 4.11    2.78    18.6    1   1   4   2
cat(format_delim(mtcars, ";"))
#> mpg;cyl;disp;hp;drat;wt;qsec;vs;am;gear;carb
#> 21;6;160;110;3.9;2.62;16.46;0;1;4;4
#> 21;6;160;110;3.9;2.875;17.02;0;1;4;4
#> 22.8;4;108;93;3.85;2.32;18.61;1;1;4;1
#> 21.4;6;258;110;3.08;3.215;19.44;1;0;3;1
#> 18.7;8;360;175;3.15;3.44;17.02;0;0;3;2
#> 18.1;6;225;105;2.76;3.46;20.22;1;0;3;1
#> 14.3;8;360;245;3.21;3.57;15.84;0;0;3;4
#> 24.4;4;146.7;62;3.69;3.19;20;1;0;4;2
#> 22.8;4;140.8;95;3.92;3.15;22.9;1;0;4;2
#> 19.2;6;167.6;123;3.92;3.44;18.3;1;0;4;4
#> 17.8;6;167.6;123;3.92;3.44;18.9;1;0;4;4
#> 16.4;8;275.8;180;3.07;4.07;17.4;0;0;3;3
#> 17.3;8;275.8;180;3.07;3.73;17.6;0;0;3;3
#> 15.2;8;275.8;180;3.07;3.78;18;0;0;3;3
#> 10.4;8;472;205;2.93;5.25;17.98;0;0;3;4
#> 10.4;8;460;215;3;5.424;17.82;0;0;3;4
#> 14.7;8;440;230;3.23;5.345;17.42;0;0;3;4
#> 32.4;4;78.7;66;4.08;2.2;19.47;1;1;4;1
#> 30.4;4;75.7;52;4.93;1.615;18.52;1;1;4;2
#> 33.9;4;71.1;65;4.22;1.835;19.9;1;1;4;1
#> 21.5;4;120.1;97;3.7;2.465;20.01;1;0;3;1
#> 15.5;8;318;150;2.76;3.52;16.87;0;0;3;2
#> 15.2;8;304;150;3.15;3.435;17.3;0;0;3;2
#> 13.3;8;350;245;3.73;3.84;15.41;0;0;3;4
#> 19.2;8;400;175;3.08;3.845;17.05;0;0;3;2
#> 27.3;4;79;66;4.08;1.935;18.9;1;1;4;1
#> 26;4;120.3;91;4.43;2.14;16.7;0;1;5;2
#> 30.4;4;95.1;113;3.77;1.513;16.9;1;1;5;2
#> 15.8;8;351;264;4.22;3.17;14.5;0;1;5;4
#> 19.7;6;145;175;3.62;2.77;15.5;0;1;5;6
#> 15;8;301;335;3.54;3.57;14.6;0;1;5;8
#> 21.4;4;121;109;4.11;2.78;18.6;1;1;4;2

# Specifying missing values
df <- data.frame(x = c(1, NA, 3))
format_csv(df, na = "missing")
#> [1] "x\n1\nmissing\n3\n"

# Quotes are automatically added as needed
df <- data.frame(x = c("a ", '"', ",", "\n"))
cat(format_csv(df))
#> x
#> a 
#> """"
#> ","
#> "
#> "
```

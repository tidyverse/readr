# Read lines from a file or string by chunk.

Read lines from a file or string by chunk.

## Usage

``` r
read_lines_chunked(
  file,
  callback,
  chunk_size = 10000,
  skip = 0,
  locale = default_locale(),
  na = character(),
  progress = show_progress()
)

read_lines_raw_chunked(
  file,
  callback,
  chunk_size = 10000,
  skip = 0,
  progress = show_progress()
)
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector).

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  uncompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote `.gz` files can
  also be automatically downloaded and decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, wrap the input with
  [`I()`](https://rdrr.io/r/base/AsIs.html).

  Using a value of
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
  will read from the system clipboard.

- callback:

  A callback function to call on each chunk

- chunk_size:

  The number of rows to include in each chunk

- skip:

  Number of lines to skip before reading data.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The automatic
  progress bar can be disabled by setting option `readr.show_progress`
  to `FALSE`.

## See also

Other chunked:
[`callback`](https://readr.tidyverse.org/reference/callback.md),
[`read_delim_chunked()`](https://readr.tidyverse.org/reference/read_delim_chunked.md)

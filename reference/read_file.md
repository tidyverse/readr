# Read/write a complete file

`read_file()` reads a complete file into a single object: either a
character vector of length one, or a raw vector. `write_file()` takes a
single string, or a raw vector, and writes it exactly as is. Raw vectors
are useful when dealing with binary data, or if you have text data with
unknown encoding.

## Usage

``` r
read_file(file, locale = default_locale())

read_file_raw(file)

write_file(x, file, append = FALSE, path = deprecated())
```

## Arguments

- file:

  Either a path to a file, a connection, or literal data (either a
  single string or a raw vector).

  Files ending in `.gz`, `.bz2`, `.xz`, or `.zip` will be automatically
  uncompressed. Files starting with `http://`, `https://`, `ftp://`, or
  `ftps://` will be automatically downloaded. Remote gz files can also
  be automatically downloaded and decompressed.

  Literal data is most useful for examples and tests. To be recognised
  as literal data, the input must be either wrapped with
  [`I()`](https://rdrr.io/r/base/AsIs.html), be a string containing at
  least one new line, or be a vector containing at least one string with
  a new line.

  Using a value of
  [`clipboard()`](https://readr.tidyverse.org/reference/clipboard.md)
  will read from the system clipboard.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- x:

  A single string, or a raw vector to write to disk.

- append:

  If `FALSE`, will overwrite existing file. If `TRUE`, will append to
  existing file. In both cases, if the file does not exist a new file is
  created.

- path:

  **\[deprecated\]** Use the `file` argument instead.

## Value

`read_file`: A length 1 character vector. `read_lines_raw`: A raw
vector.

## Examples

``` r
read_file(file.path(R.home("doc"), "AUTHORS"))
#> [1] "Authors of R.\n\nR was initially written by Robert Gentleman and Ross Ihaka, also known as \"R & R\"\nof the Statistics Department of the University of Auckland.\n\nSince mid-1997 there has been a core group with write access to the R\nsource, currently consisting of\n\nJohn Chambers\nPeter Dalgaard\nRobert Gentleman\nKurt Hornik\nRoss Ihaka\nTomas Kalibera\nMichael Lawrence\nUwe Ligges\nThomas Lumley\nMartin Maechler\nSebastian Meyer\nPaul Murrell\nMartyn Plummer\nBrian Ripley\nDeepayan Sarkar\nDuncan Temple Lang\nLuke Tierney\nSimon Urbanek\n\nplus Heiner Schwarte up to October 1999, Guido Masarotto up to June 2003,\nStefano Iacus up to July 2014, Seth Falcon up to August 2015, Duncan Murdoch\nup to September 2017, Martin Morgan up to June 2021, Douglas Bates up to March 2024,\nand Friedrich Leisch up to April 2024.\n\n\nCurrent R-core members can be contacted via email to R-project.org\nwith name made up by replacing spaces by dots in the name listed above.\n\n(The authors of code from other projects included in the R distribution\nare listed in the COPYRIGHTS file.)\n"
read_file_raw(file.path(R.home("doc"), "AUTHORS"))
#>    [1] 41 75 74 68 6f 72 73 20 6f 66 20 52 2e 0a 0a 52 20 77 61 73 20
#>   [22] 69 6e 69 74 69 61 6c 6c 79 20 77 72 69 74 74 65 6e 20 62 79 20
#>   [43] 52 6f 62 65 72 74 20 47 65 6e 74 6c 65 6d 61 6e 20 61 6e 64 20
#>   [64] 52 6f 73 73 20 49 68 61 6b 61 2c 20 61 6c 73 6f 20 6b 6e 6f 77
#>   [85] 6e 20 61 73 20 22 52 20 26 20 52 22 0a 6f 66 20 74 68 65 20 53
#>  [106] 74 61 74 69 73 74 69 63 73 20 44 65 70 61 72 74 6d 65 6e 74 20
#>  [127] 6f 66 20 74 68 65 20 55 6e 69 76 65 72 73 69 74 79 20 6f 66 20
#>  [148] 41 75 63 6b 6c 61 6e 64 2e 0a 0a 53 69 6e 63 65 20 6d 69 64 2d
#>  [169] 31 39 39 37 20 74 68 65 72 65 20 68 61 73 20 62 65 65 6e 20 61
#>  [190] 20 63 6f 72 65 20 67 72 6f 75 70 20 77 69 74 68 20 77 72 69 74
#>  [211] 65 20 61 63 63 65 73 73 20 74 6f 20 74 68 65 20 52 0a 73 6f 75
#>  [232] 72 63 65 2c 20 63 75 72 72 65 6e 74 6c 79 20 63 6f 6e 73 69 73
#>  [253] 74 69 6e 67 20 6f 66 0a 0a 4a 6f 68 6e 20 43 68 61 6d 62 65 72
#>  [274] 73 0a 50 65 74 65 72 20 44 61 6c 67 61 61 72 64 0a 52 6f 62 65
#>  [295] 72 74 20 47 65 6e 74 6c 65 6d 61 6e 0a 4b 75 72 74 20 48 6f 72
#>  [316] 6e 69 6b 0a 52 6f 73 73 20 49 68 61 6b 61 0a 54 6f 6d 61 73 20
#>  [337] 4b 61 6c 69 62 65 72 61 0a 4d 69 63 68 61 65 6c 20 4c 61 77 72
#>  [358] 65 6e 63 65 0a 55 77 65 20 4c 69 67 67 65 73 0a 54 68 6f 6d 61
#>  [379] 73 20 4c 75 6d 6c 65 79 0a 4d 61 72 74 69 6e 20 4d 61 65 63 68
#>  [400] 6c 65 72 0a 53 65 62 61 73 74 69 61 6e 20 4d 65 79 65 72 0a 50
#>  [421] 61 75 6c 20 4d 75 72 72 65 6c 6c 0a 4d 61 72 74 79 6e 20 50 6c
#>  [442] 75 6d 6d 65 72 0a 42 72 69 61 6e 20 52 69 70 6c 65 79 0a 44 65
#>  [463] 65 70 61 79 61 6e 20 53 61 72 6b 61 72 0a 44 75 6e 63 61 6e 20
#>  [484] 54 65 6d 70 6c 65 20 4c 61 6e 67 0a 4c 75 6b 65 20 54 69 65 72
#>  [505] 6e 65 79 0a 53 69 6d 6f 6e 20 55 72 62 61 6e 65 6b 0a 0a 70 6c
#>  [526] 75 73 20 48 65 69 6e 65 72 20 53 63 68 77 61 72 74 65 20 75 70
#>  [547] 20 74 6f 20 4f 63 74 6f 62 65 72 20 31 39 39 39 2c 20 47 75 69
#>  [568] 64 6f 20 4d 61 73 61 72 6f 74 74 6f 20 75 70 20 74 6f 20 4a 75
#>  [589] 6e 65 20 32 30 30 33 2c 0a 53 74 65 66 61 6e 6f 20 49 61 63 75
#>  [610] 73 20 75 70 20 74 6f 20 4a 75 6c 79 20 32 30 31 34 2c 20 53 65
#>  [631] 74 68 20 46 61 6c 63 6f 6e 20 75 70 20 74 6f 20 41 75 67 75 73
#>  [652] 74 20 32 30 31 35 2c 20 44 75 6e 63 61 6e 20 4d 75 72 64 6f 63
#>  [673] 68 0a 75 70 20 74 6f 20 53 65 70 74 65 6d 62 65 72 20 32 30 31
#>  [694] 37 2c 20 4d 61 72 74 69 6e 20 4d 6f 72 67 61 6e 20 75 70 20 74
#>  [715] 6f 20 4a 75 6e 65 20 32 30 32 31 2c 20 44 6f 75 67 6c 61 73 20
#>  [736] 42 61 74 65 73 20 75 70 20 74 6f 20 4d 61 72 63 68 20 32 30 32
#>  [757] 34 2c 0a 61 6e 64 20 46 72 69 65 64 72 69 63 68 20 4c 65 69 73
#>  [778] 63 68 20 75 70 20 74 6f 20 41 70 72 69 6c 20 32 30 32 34 2e 0a
#>  [799] 0a 0a 43 75 72 72 65 6e 74 20 52 2d 63 6f 72 65 20 6d 65 6d 62
#>  [820] 65 72 73 20 63 61 6e 20 62 65 20 63 6f 6e 74 61 63 74 65 64 20
#>  [841] 76 69 61 20 65 6d 61 69 6c 20 74 6f 20 52 2d 70 72 6f 6a 65 63
#>  [862] 74 2e 6f 72 67 0a 77 69 74 68 20 6e 61 6d 65 20 6d 61 64 65 20
#>  [883] 75 70 20 62 79 20 72 65 70 6c 61 63 69 6e 67 20 73 70 61 63 65
#>  [904] 73 20 62 79 20 64 6f 74 73 20 69 6e 20 74 68 65 20 6e 61 6d 65
#>  [925] 20 6c 69 73 74 65 64 20 61 62 6f 76 65 2e 0a 0a 28 54 68 65 20
#>  [946] 61 75 74 68 6f 72 73 20 6f 66 20 63 6f 64 65 20 66 72 6f 6d 20
#>  [967] 6f 74 68 65 72 20 70 72 6f 6a 65 63 74 73 20 69 6e 63 6c 75 64
#>  [988] 65 64 20 69 6e 20 74 68 65 20 52 20 64 69 73 74 72 69 62 75 74
#> [1009] 69 6f 6e 0a 61 72 65 20 6c 69 73 74 65 64 20 69 6e 20 74 68 65
#> [1030] 20 43 4f 50 59 52 49 47 48 54 53 20 66 69 6c 65 2e 29 0a

tmp <- tempfile()

x <- format_csv(mtcars[1:6, ])
write_file(x, tmp)
identical(x, read_file(tmp))
#> [1] TRUE

read_lines(I(x))
#> [1] "mpg,cyl,disp,hp,drat,wt,qsec,vs,am,gear,carb"
#> [2] "21,6,160,110,3.9,2.62,16.46,0,1,4,4"         
#> [3] "21,6,160,110,3.9,2.875,17.02,0,1,4,4"        
#> [4] "22.8,4,108,93,3.85,2.32,18.61,1,1,4,1"       
#> [5] "21.4,6,258,110,3.08,3.215,19.44,1,0,3,1"     
#> [6] "18.7,8,360,175,3.15,3.44,17.02,0,0,3,2"      
#> [7] "18.1,6,225,105,2.76,3.46,20.22,1,0,3,1"      
```

# Read/write lines to/from a file

`read_lines()` reads up to `n_max` lines from a file. New lines are not
included in the output. `read_lines_raw()` produces a list of raw
vectors, and is useful for handling data with unknown encoding.
`write_lines()` takes a character vector or list of raw vectors,
appending a new line after each entry.

## Usage

``` r
read_lines(
  file,
  skip = 0,
  skip_empty_rows = FALSE,
  n_max = Inf,
  locale = default_locale(),
  na = character(),
  lazy = should_read_lazy(),
  num_threads = readr_threads(),
  progress = show_progress()
)

read_lines_raw(
  file,
  skip = 0,
  n_max = -1L,
  num_threads = readr_threads(),
  progress = show_progress()
)

write_lines(
  x,
  file,
  sep = "\n",
  na = "NA",
  append = FALSE,
  num_threads = readr_threads()
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
  [`clipboard()`](https://readr.tidyverse.org/dev/reference/clipboard.md)
  will read from the system clipboard.

- skip:

  Number of lines to skip before reading data.

- skip_empty_rows:

  Should blank rows be ignored altogether? i.e. If this option is `TRUE`
  then blank rows will not be represented at all. If it is `FALSE` then
  they will be represented by `NA` values in all the columns.

- n_max:

  Number of lines to read. If `n_max` is -1, all lines in file will be
  read.

- locale:

  The locale controls defaults that vary from place to place. The
  default locale is US-centric (like R), but you can use
  [`locale()`](https://readr.tidyverse.org/dev/reference/locale.md) to
  create your own locale that controls things like the default time
  zone, encoding, decimal mark, big mark, and day/month names.

- na:

  Character vector of strings to interpret as missing values. Set this
  option to [`character()`](https://rdrr.io/r/base/character.html) to
  indicate no missing values.

- lazy:

  Read values lazily? By default, this is `FALSE`, because there are
  special considerations when reading a file lazily that have tripped up
  some users. Specifically, things get tricky when reading and then
  writing back into the same file. But, in general, lazy reading
  (`lazy = TRUE`) has many benefits, especially for interactive use and
  when your downstream work only involves a subset of the rows or
  columns.

  Learn more in
  [`should_read_lazy()`](https://readr.tidyverse.org/dev/reference/should_read_lazy.md)
  and in the documentation for the `altrep` argument of
  [`vroom::vroom()`](https://vroom.tidyverse.org/reference/vroom.html).

- num_threads:

  The number of processing threads to use for initial parsing and lazy
  reading of data. If your data contains newlines within fields the
  parser should automatically detect this and fall back to using one
  thread only. However if you know your file has newlines within quoted
  fields it is safest to set `num_threads = 1` explicitly.

- progress:

  Display a progress bar? By default it will only display in an
  interactive session and not while knitting a document. The automatic
  progress bar can be disabled by setting option `readr.show_progress`
  to `FALSE`.

- x:

  A character vector or list of raw vectors to write to disk.

- sep:

  The line separator. Defaults to `\\n`, commonly used on POSIX systems
  like macOS and linux. For native windows (CRLF) separators use
  `\\r\\n`.

- append:

  If `FALSE`, will overwrite existing file. If `TRUE`, will append to
  existing file. In both cases, if the file does not exist a new file is
  created.

## Value

`read_lines()`: A character vector with one element for each line.
`read_lines_raw()`: A list containing a raw vector for each line.

`write_lines()` returns `x`, invisibly.

## Examples

``` r
read_lines(file.path(R.home("doc"), "AUTHORS"), n_max = 10)
#>  [1] "Authors of R."                                                                      
#>  [2] ""                                                                                   
#>  [3] "R was initially written by Robert Gentleman and Ross Ihaka, also known as \"R & R\""
#>  [4] "of the Statistics Department of the University of Auckland."                        
#>  [5] ""                                                                                   
#>  [6] "Since mid-1997 there has been a core group with write access to the R"              
#>  [7] "source, currently consisting of"                                                    
#>  [8] ""                                                                                   
#>  [9] "John Chambers"                                                                      
#> [10] "Peter Dalgaard"                                                                     
read_lines_raw(file.path(R.home("doc"), "AUTHORS"), n_max = 10)
#> [[1]]
#>  [1] 41 75 74 68 6f 72 73 20 6f 66 20 52 2e
#> 
#> [[2]]
#> raw(0)
#> 
#> [[3]]
#>  [1] 52 20 77 61 73 20 69 6e 69 74 69 61 6c 6c 79 20 77 72 69 74 74 65
#> [23] 6e 20 62 79 20 52 6f 62 65 72 74 20 47 65 6e 74 6c 65 6d 61 6e 20
#> [45] 61 6e 64 20 52 6f 73 73 20 49 68 61 6b 61 2c 20 61 6c 73 6f 20 6b
#> [67] 6e 6f 77 6e 20 61 73 20 22 52 20 26 20 52 22
#> 
#> [[4]]
#>  [1] 6f 66 20 74 68 65 20 53 74 61 74 69 73 74 69 63 73 20 44 65 70 61
#> [23] 72 74 6d 65 6e 74 20 6f 66 20 74 68 65 20 55 6e 69 76 65 72 73 69
#> [45] 74 79 20 6f 66 20 41 75 63 6b 6c 61 6e 64 2e
#> 
#> [[5]]
#> raw(0)
#> 
#> [[6]]
#>  [1] 53 69 6e 63 65 20 6d 69 64 2d 31 39 39 37 20 74 68 65 72 65 20 68
#> [23] 61 73 20 62 65 65 6e 20 61 20 63 6f 72 65 20 67 72 6f 75 70 20 77
#> [45] 69 74 68 20 77 72 69 74 65 20 61 63 63 65 73 73 20 74 6f 20 74 68
#> [67] 65 20 52
#> 
#> [[7]]
#>  [1] 73 6f 75 72 63 65 2c 20 63 75 72 72 65 6e 74 6c 79 20 63 6f 6e 73
#> [23] 69 73 74 69 6e 67 20 6f 66
#> 
#> [[8]]
#> raw(0)
#> 
#> [[9]]
#>  [1] 4a 6f 68 6e 20 43 68 61 6d 62 65 72 73
#> 
#> [[10]]
#>  [1] 50 65 74 65 72 20 44 61 6c 67 61 61 72 64
#> 

tmp <- tempfile()

write_lines(rownames(mtcars), tmp)
read_lines(tmp, lazy = FALSE)
#>  [1] "Mazda RX4"           "Mazda RX4 Wag"       "Datsun 710"         
#>  [4] "Hornet 4 Drive"      "Hornet Sportabout"   "Valiant"            
#>  [7] "Duster 360"          "Merc 240D"           "Merc 230"           
#> [10] "Merc 280"            "Merc 280C"           "Merc 450SE"         
#> [13] "Merc 450SL"          "Merc 450SLC"         "Cadillac Fleetwood" 
#> [16] "Lincoln Continental" "Chrysler Imperial"   "Fiat 128"           
#> [19] "Honda Civic"         "Toyota Corolla"      "Toyota Corona"      
#> [22] "Dodge Challenger"    "AMC Javelin"         "Camaro Z28"         
#> [25] "Pontiac Firebird"    "Fiat X1-9"           "Porsche 914-2"      
#> [28] "Lotus Europa"        "Ford Pantera L"      "Ferrari Dino"       
#> [31] "Maserati Bora"       "Volvo 142E"         
read_file(tmp) # note trailing \n
#> [1] "Mazda RX4\nMazda RX4 Wag\nDatsun 710\nHornet 4 Drive\nHornet Sportabout\nValiant\nDuster 360\nMerc 240D\nMerc 230\nMerc 280\nMerc 280C\nMerc 450SE\nMerc 450SL\nMerc 450SLC\nCadillac Fleetwood\nLincoln Continental\nChrysler Imperial\nFiat 128\nHonda Civic\nToyota Corolla\nToyota Corona\nDodge Challenger\nAMC Javelin\nCamaro Z28\nPontiac Firebird\nFiat X1-9\nPorsche 914-2\nLotus Europa\nFord Pantera L\nFerrari Dino\nMaserati Bora\nVolvo 142E\n"

write_lines(airquality$Ozone, tmp, na = "-1")
read_lines(tmp)
#>   [1] "41"  "36"  "12"  "18"  "-1"  "28"  "23"  "19"  "8"   "-1"  "7"  
#>  [12] "16"  "11"  "14"  "18"  "14"  "34"  "6"   "30"  "11"  "1"   "11" 
#>  [23] "4"   "32"  "-1"  "-1"  "-1"  "23"  "45"  "115" "37"  "-1"  "-1" 
#>  [34] "-1"  "-1"  "-1"  "-1"  "29"  "-1"  "71"  "39"  "-1"  "-1"  "23" 
#>  [45] "-1"  "-1"  "21"  "37"  "20"  "12"  "13"  "-1"  "-1"  "-1"  "-1" 
#>  [56] "-1"  "-1"  "-1"  "-1"  "-1"  "-1"  "135" "49"  "32"  "-1"  "64" 
#>  [67] "40"  "77"  "97"  "97"  "85"  "-1"  "10"  "27"  "-1"  "7"   "48" 
#>  [78] "35"  "61"  "79"  "63"  "16"  "-1"  "-1"  "80"  "108" "20"  "52" 
#>  [89] "82"  "50"  "64"  "59"  "39"  "9"   "16"  "78"  "35"  "66"  "122"
#> [100] "89"  "110" "-1"  "-1"  "44"  "28"  "65"  "-1"  "22"  "59"  "23" 
#> [111] "31"  "44"  "21"  "9"   "-1"  "45"  "168" "73"  "-1"  "76"  "118"
#> [122] "84"  "85"  "96"  "78"  "73"  "91"  "47"  "32"  "20"  "23"  "21" 
#> [133] "24"  "44"  "21"  "28"  "9"   "13"  "46"  "18"  "13"  "24"  "16" 
#> [144] "13"  "23"  "36"  "7"   "14"  "30"  "-1"  "14"  "18"  "20" 
```

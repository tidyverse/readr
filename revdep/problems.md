# Setup

## Platform

|setting  |value                        |
|:--------|:----------------------------|
|version  |R version 3.3.0 (2016-05-03) |
|system   |x86_64, darwin13.4.0         |
|ui       |RStudio (0.99.1271)          |
|language |(EN)                         |
|collate  |en_US.UTF-8                  |
|tz       |America/Chicago              |
|date     |2016-07-29                   |

## Packages

|package   |*  |version    |date       |source                           |
|:---------|:--|:----------|:----------|:--------------------------------|
|BH        |   |1.60.0-2   |2016-05-07 |CRAN (R 3.3.0)                   |
|covr      |   |2.1.0      |2016-06-21 |cran (@2.1.0)                    |
|curl      |   |1.1        |2016-07-26 |cran (@1.1)                      |
|hms       |   |0.2-1      |2016-07-19 |Github (rstats-db/hms@98d14cf)   |
|knitr     |   |1.13       |2016-05-09 |CRAN (R 3.3.0)                   |
|R6        |   |2.1.2      |2016-01-26 |CRAN (R 3.3.0)                   |
|Rcpp      |   |0.12.6     |2016-07-19 |cran (@0.12.6)                   |
|readr     |   |0.2.2.9000 |2016-07-29 |local (hadley/readr@9d09872)     |
|rmarkdown |   |1.0        |2016-07-08 |cran (@1.0)                      |
|stringi   |   |1.1.1      |2016-05-27 |cran (@1.1.1)                    |
|testthat  |*  |1.0.2.9000 |2016-07-19 |Github (hadley/testthat@46d15da) |
|tibble    |   |1.1-2      |2016-07-29 |Github (hadley/tibble@8c12ace)   |

# Check results
11 packages with problems

## biomartr (0.0.3)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/biomartr/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Packages required but not available: ‘biomaRt’ ‘Biostrings’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## ddpcr (1.4)
Maintainer: Dean Attali <daattali@gmail.com>  
Bug reports: https://github.com/daattali/ddpcr/issues

1 error  | 1 warning  | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  testthat results ================================================================
  OK: 220 SKIPPED: 0 FAILED: 8
  1. Error: classify works (@test-custom_thresholds.R#38) 
  2. Error: get_empty_cutoff works (@test-empty.R#6) 
  3. Error: get_empty_cutoff for pnpp works (@test-empty.R#20) 
  4. Error: is_well_success works (@test-failures.R#6) 
  5. Error: test basic plate attribute getters/setters (@test-plate-attribs.R#30) 
  6. Error: reset works (@test-plate.R#12) 
  7. Error: next_step and analyze work (@test-plate.R#46) 
  8. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) 
  
  Error: testthat unit tests failed
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Quitting from lines 205-213 (extend.Rmd) 
Error: processing vignette 'extend.Rmd' failed with diagnostics:
NA/NaN/Inf in foreign function call (arg 1)
Execution halted

```

## eemR (0.1.3)
Maintainer: Philippe Massicotte <pm@bios.au.dk>  
Bug reports: https://github.com/PMassicotte/eemR/issues

2 errors | 1 warning  | 0 notes

```
checking examples ... ERROR
Running examples in ‘eemR-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: eem_bind
> ### Title: Bind eem or eemlist
> ### Aliases: eem_bind
> 
> ### ** Examples
> 
> file <- system.file("extdata/cary/scans_day_1/", "sample1.csv", package = "eemR")
> eem <- eem_read(file)
Error in read_lines_(ds, locale_ = locale, na = na, n_max = n_max, progress = progress) : 
  attempt to set index 1000/1000 in SET_STRING_ELT
Calls: eem_read ... lapply -> FUN -> read_lines -> read_lines_ -> .Call
Execution halted

checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  4: read_lines(file)
  5: read_lines_(ds, locale_ = locale, na = na, n_max = n_max, progress = progress) at /Users/hadley/Documents/ingest/readr/R/read_lines.R:24
  
  Error in read_lines_(ds, locale_ = locale, na = na, n_max = n_max, progress = progress) : 
    attempt to set index 1000/1000 in SET_STRING_ELT
  Calls: test_check ... lapply -> FUN -> read_lines -> read_lines_ -> .Call
  testthat results ================================================================
  OK: 0 SKIPPED: 0 FAILED: 2
  1. Error: grouped blank correction works (@test-blank-correction.R#6) 
  2. Error: single blank correction works (@test-blank-correction.R#20) 
  
  Error: testthat unit tests failed
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...

Attaching package: 'dplyr'

The following objects are masked from 'package:stats':

    filter, lag

The following objects are masked from 'package:base':

    intersect, setdiff, setequal, union

Quitting from lines 32-48 (introduction.Rmd) 
Error: processing vignette 'introduction.Rmd' failed with diagnostics:
attempt to set index 1000/1000 in SET_STRING_ELT
Execution halted

```

## fuzzyjoin (0.1.1)
Maintainer: David Robinson <drobinson@stackoverflow.com>

1 error  | 0 warnings | 0 notes

```
checking examples ... ERROR
Running examples in ‘fuzzyjoin-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: misspellings
> ### Title: A corpus of common misspellings, for examples and practice
> ### Aliases: misspellings
> ### Keywords: datasets
> 
... 33 lines ...
+   html_nodes("pre") %>%
+   html_text() %>%
+   readr::read_delim(col_names = c("misspelling", "correct"), delim = ">",
+                     skip = 1) %>%
+   mutate(misspelling = str_sub(misspelling, 1, -2)) %>%
+   unnest(correct = str_split(correct, ", ")) %>%
+   filter(Encoding(correct) != "UTF-8")
Error in read_tokens_(data, tokenizer, col_specs, col_names, locale_,  : 
  attempt to set index 1000/1000 in SET_STRING_ELT
Calls: %>% ... read_delimited -> read_tokens -> read_tokens_ -> .Call
Execution halted
```

## gutenbergr (0.1.2)
Maintainer: David Robinson <admiral.david@gmail.com>  
Bug reports: http://github.com/ropenscilabs/gutenbergr/issues

1 error  | 1 warning  | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  sum(str_detect(d$text, "Aristotle")) is not strictly more than 50. Difference: -50
  
  
  testthat results ================================================================
  OK: 49 SKIPPED: 0 FAILED: 5
  1. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#22) 
  2. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#23) 
  3. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#31) 
  4. Failure: Can download Charles Dickens' Christmas Carol and Jane Austen's Persuasion (@test-download.R#32) 
  5. Failure: We can download a file that only has a -8 version (@test-download.R#50) 
  
  Error: testthat unit tests failed
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...

    filter, lag

The following objects are masked from 'package:base':

    intersect, setdiff, setequal, union

... 8 lines ...
Warning in .f(.x[[i]], ...) :
  Could not download a book at http://www.gutenberg.lib.md.us/7/6/768/768.zip
Warning in .f(.x[[i]], ...) :
  Could not download a book at http://www.gutenberg.lib.md.us/1/2/6/1260/1260.zip
Warning: Unknown column 'text'
Warning in is.na(text) :
  is.na() applied to non-(list or vector) of type 'NULL'
Quitting from lines 119-131 (intro.Rmd) 
Error: processing vignette 'intro.Rmd' failed with diagnostics:
invalid 'times' argument
Execution halted
```

## myTAI (0.4.0)
Maintainer: Hajk-Georg Drost <hgd23@cam.ac.uk>  
Bug reports: https://github.com/HajkD/myTAI/issues

1 error  | 0 warnings | 0 notes

```
checking package dependencies ... ERROR
Package required but not available: ‘edgeR’

See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
manual.
```

## photobiologyInOut (0.4.6)
Maintainer: Pedro J. Aphalo <pedro.aphalo@helsinki.fi>  
Bug reports: https://bitbucket.org/aphalo/photobiologyinout/

1 error  | 1 warning  | 0 notes

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
  Read 18 items
  Read 3 items
  Read 16 items
  Read 3 items
  Read 16 items
  Read 4 items
  testthat results ================================================================
  OK: 202 SKIPPED: 0 FAILED: 2
  1. Failure: single spectrum (quantum) (@test-avantes.R#16) 
  2. Failure: single spectrum (quantum) (@test-avantes.R#17) 
  
  Error: testthat unit tests failed
  Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Read 3 items
Read 16 items
Read 4 items
Read 18 items
Read 4 items
Read 18 items
Read 4 items
Read 18 items
Read 4 items
Read 18 items
Read 3 items
Read 16 items
Read 12 items
Quitting from lines 334-336 (user-guide.Rnw) 
Error: processing vignette 'user-guide.Rnw' failed with diagnostics:
'vec' must be sorted non-decreasingly and not contain NAs
Execution halted

```

## rgho (0.1.0)
Maintainer: Antoine Filipovic-Pierucci <pierucci@gmail.com>  
Bug reports: https://github.com/pierucci/rgho/issues

1 error  | 1 warning  | 0 notes

```
checking examples ... ERROR
Running examples in ‘rgho-Ex.R’ failed
The error most likely occurred in:

> base::assign(".ptime", proc.time(), pos = "CheckExEnv")
> ### Name: get_gho_data_
> ### Title: Returns GHO Data
> ### Aliases: get_gho_data get_gho_data_
> 
> ### ** Examples
> 
> 
> result <- get_gho_data(
+   dimension = "GHO",
+   code = "MDG_0000000001"
+ )
Error in `_f`(url = url, debug = debug, max_try = max_try) : 
  Server error: (500) Internal Server Error
Calls: get_gho_data ... %>% -> eval -> eval -> get_gho -> withVisible -> _f
Execution halted

checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...
Quitting from lines 74-80 (intro.Rmd) 
Error: processing vignette 'intro.Rmd' failed with diagnostics:
Server error: (500) Internal Server Error
Execution halted

```

## riem (0.1.0)
Maintainer: Maëlle Salmon <maelle.salmon@yahoo.se>  
Bug reports: http://github.com/ropenscilabs/riem/issues

0 errors | 1 warning  | 1 note 

```
checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...

Attaching package: 'dplyr'

The following objects are masked from 'package:stats':

    filter, lag

The following objects are masked from 'package:base':

    intersect, setdiff, setequal, union

Quitting from lines 96-97 (riem_package.Rmd) 
Error: processing vignette 'riem_package.Rmd' failed with diagnostics:
attempt to set index 1000/1000 in SET_STRING_ELT
Execution halted


checking DESCRIPTION meta-information ... NOTE
Authors@R field gives persons with no valid roles:
  Brooke Anderson [rev] (Brooke Anderson reviewed the package for rOpenSci, see https://github.com/ropensci/onboarding/issues/39.)
```

## stationaRy (0.4.1)
Maintainer: Richard Iannone <riannone@me.com>  
Bug reports: https://github.com/rich-iannone/stationaRy/issues

1 error  | 0 warnings | 1 note 

```
checking tests ... ERROR
Running the tests in ‘tests/testthat.R’ failed.
Last 13 lines of output:
     <dbl> <dbl>                  <chr>   <chr> <chr>  <dbl>  <dbl> <dbl> <dbl>
  1 710040 99999 CYPRESS BOWL FREESTYLE      CA       49.400 -123.2   969  2007
  2 715620 99999 CYPRESS BOWL SNOWBOARD      CA       49.383 -123.2  1180  2010
  3 716930 99999     CYPRESS BOWL SOUTH      CA       49.383 -123.2   886  2007
  # ... with 7 more variables: end <dbl>, gmt_offset <dbl>, time_zone_id <chr>,
  #   country_name <chr>, country_code <chr>, iso3166_2_subd <chr>,
  #   fips10_4_subd <chr>
  testthat results ================================================================
  OK: 41 SKIPPED: 0 FAILED: 1
  1. Error: get_isd_station_data returns correct number of columns (@test-get_isd_station_data.R#6) 
  
  Error: testthat unit tests failed
  Execution halted

checking installed package size ... NOTE
  installed size is  8.1Mb
```

## tidytext (0.1.1)
Maintainer: Julia Silge <julia.silge@gmail.com>  
Bug reports: http://github.com/juliasilge/tidytext/issues

0 errors | 1 warning  | 0 notes

```
checking re-building of vignette outputs ... WARNING
Error in re-building vignettes:
  ...

The following object is masked from 'package:tidyr':

    smiths

Joining, by = "word"
Joining, by = "word"
... 8 lines ...
Warning in .f(.x[[i]], ...) :
  Could not download a book at http://www.gutenberg.lib.md.us/1/3/4/1342/1342.zip
Warning in .f(.x[[i]], ...) :
  Could not download a book at http://www.gutenberg.lib.md.us/1/4/0/1400/1400.zip
Warning: Unknown column 'text'
Warning in is.na(text) :
  is.na() applied to non-(list or vector) of type 'NULL'
Quitting from lines 51-71 (topic_modeling.Rmd) 
Error: processing vignette 'topic_modeling.Rmd' failed with diagnostics:
invalid 'times' argument
Execution halted
```


# auk

<details>

* Version: 0.4.3
* Source code: https://github.com/cran/auk
* URL: https://github.com/CornellLabofOrnithology/auk, https://cornelllabofornithology.github.io/auk/
* BugReports: https://github.com/CornellLabofOrnithology/auk/issues
* Date/Publication: 2020-11-23 06:40:02 UTC
* Number of recursive dependencies: 90

Run `cloud_details(, "auk")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      auk 0.4.2 is designed for EBD files downloaded after 2019-08-15. 
      No EBD data directory set, see ?auk_set_ebd_path to set EBD_PATH 
      eBird taxonomy version:  2019
      > 
      > test_check("auk")
      ══ Skipped tests ═══════════════════════════════════════════════════════════════
      • On CRAN (21)
      
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test_filters.r:43:5): auk_species ──────────────────────────────────
      `auk_species(ebd, "Canada Jay", taxonomy_version = 2016)` produced messages.
      
      [ FAIL 1 | WARN 0 | SKIP 21 | PASS 409 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 552 marked UTF-8 strings
    ```

# blaise

<details>

* Version: 1.3.7
* Source code: https://github.com/cran/blaise
* Date/Publication: 2021-06-04 16:40:02 UTC
* Number of recursive dependencies: 54

Run `cloud_details(, "blaise")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Complete output:
      > library(testthat)
      > library(blaise)
      > 
      > test_check("blaise")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test_types.R:164:3): empty STRING ──────────────────────────────────
      rep(NA_character_, 10) not equal to dfnew[["A"]].
      Lengths differ: 10 is not 1
      
      [ FAIL 1 | WARN 0 | SKIP 0 | PASS 419 ]
      Error: Test failures
      Execution halted
    ```

# breathtestcore

<details>

* Version: 0.8.1
* Source code: https://github.com/cran/breathtestcore
* URL: https://github.com/dmenne/breathtestcore
* BugReports: https://github.com/dmenne/breathtestcore/issues
* Date/Publication: 2021-04-22 09:50:02 UTC
* Number of recursive dependencies: 109

Run `cloud_details(, "breathtestcore")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘test-all.R’
    Running the tests in ‘tests/test-all.R’ failed.
    Last 13 lines of output:
        2. │ └─testthat:::quasi_capture(...)
        3. │   ├─testthat:::.capture(...)
        4. │   │ └─base::withCallingHandlers(...)
        5. │   └─rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
        6. ├─breathtestcore::read_iris_csv(filename)
        7. │ ├─base::suppressWarnings(...)
        8. │ │ └─base::withCallingHandlers(...)
        9. │ └─readr::read_csv(to_read, col_types = "cccciddddddcc", locale = readr::locale(encoding = "ISO-8859-2"))
       10. │   └─vroom::vroom(...)
       11. │     └─vroom:::vroom_(...)
       12. └─(function (spec, col_names, col_select, name_repair) ...
      
      [ FAIL 2 | WARN 2 | SKIP 4 | PASS 359 ]
      Error: Test failures
      Execution halted
    ```

# dataRetrieval

<details>

* Version: 2.7.7
* Source code: https://github.com/cran/dataRetrieval
* URL: https://pubs.usgs.gov/tm/04/a10/
* BugReports: https://github.com/USGS/dataRetrieval/issues
* Date/Publication: 2021-03-06 19:10:02 UTC
* Number of recursive dependencies: 94

Run `cloud_details(, "dataRetrieval")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    ...
    > 
    > obs_url <- constructNWISURL(site_id,property,
    +          startDate,endDate,"dv",format="tsv")
    > # User file:
    > filePath <- system.file("extdata", package="dataRetrieval")
    > fileName <- "RDB1Example.txt"
    > fullPath <- file.path(filePath, fileName)
    > importUserRDB <- importRDB1(fullPath)
    Rows: 31 Columns: 5
    ── Column specification ────────────────────────────────────────────────────────
    Delimiter: "\t"
    chr  (3): X1, X2, X5
    dbl  (1): X4
    date (1): X3
    
    ℹ Use `spec()` to retrieve the full column specification for this data.
    ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
    Error in attr(readr.data, "problems")[["col"]] : 
      object of type 'externalptr' is not subsettable
    Calls: importRDB1
    Execution halted
    ```

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      ── Error (tests_general.R:114:3): whatNWISdata ─────────────────────────────────
      Error: object of type 'externalptr' is not subsettable
      Backtrace:
          █
       1. └─dataRetrieval::whatNWISdata(siteNumber = "05114000") tests_general.R:114:2
       2.   └─dataRetrieval::importRDB1(urlSitefile, asDateTime = FALSE)
      ── Error (tests_imports.R:54:3): CRAN-friendly importRDB test ──────────────────
      Error: object of type 'externalptr' is not subsettable
      Backtrace:
          █
       1. └─dataRetrieval::importRDB1(fullPath) tests_imports.R:54:2
      
      [ FAIL 2 | WARN 0 | SKIP 42 | PASS 20 ]
      Error: Test failures
      Execution halted
    ```

# DSSAT

<details>

* Version: 0.0.2
* Source code: https://github.com/cran/DSSAT
* BugReports: https://github.com/palderman/DSSAT/issues
* Date/Publication: 2020-05-18 14:50:06 UTC
* Number of recursive dependencies: 41

Run `cloud_details(, "DSSAT")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    Running examples in ‘DSSAT-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: add_v_fmt
    > ### Title: Adds variable format information to a tibble
    > ### Aliases: add_v_fmt
    > 
    > ### ** Examples
    > 
    > 
    > # Extract file path for sample ecotype file
    > sample_eco_file <- system.file('extdata','SAMPLE.ECO',package='DSSAT')
    > 
    > # Read sample ecotype file
    > eco <- read_eco(sample_eco_file)
    Error: '@ECO#  ECONAME.........  TBASE  TOPT ROPT   P20  DJTI  GDDE  DSGFT  RUE   KCAN  TSEN  CDAY' does not exist in current working directory ('/tmp/workdir/DSSAT/new/DSSAT.Rcheck').
    Execution halted
    ```

# esmisc

<details>

* Version: 0.0.3
* Source code: https://github.com/cran/esmisc
* URL: https://github.com/EDiLD/esmisc
* BugReports: https://github.com/EDiLD/esmisc/issues
* Date/Publication: 2017-01-11 10:34:49
* Number of recursive dependencies: 54

Run `cloud_details(, "esmisc")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Complete output:
      > library('testthat')
      > library('esmisc')
      > test_check("esmisc")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test-read_regnie.R:7:3): read_regnie works ─────────────────────────
      nrow(r) not equal to 971.
      1/1 mismatches
      [1] 972 - 971 == 1
      
      [ FAIL 1 | WARN 1 | SKIP 0 | PASS 7 ]
      Error: Test failures
      Execution halted
    ```

# genius

<details>

* Version: 2.2.2
* Source code: https://github.com/cran/genius
* URL: https://github.com/josiahparry/genius
* BugReports: https://github.com/josiahparry/genius/issues
* Date/Publication: 2020-05-28 16:10:02 UTC
* Number of recursive dependencies: 71

Run `cloud_details(, "genius")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    Running examples in ‘genius-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: genius_lyrics
    > ### Title: Retrieve song lyrics from Genius.com
    > ### Aliases: genius_lyrics
    > 
    > ### ** Examples
    > 
    > genius_lyrics(artist = "Kendrick Lamar", song = "Money Trees")
    Warning: `html_session()` was deprecated in rvest 1.0.0.
    Please use `session()` instead.
    This warning is displayed once every 8 hours.
    Call `lifecycle::last_warnings()` to see where this warning was generated.
    Error: 'NA' does not exist in current working directory ('/tmp/workdir/genius/new/genius.Rcheck').
    Execution halted
    ```

# PL94171

<details>

* Version: 0.2.0
* Source code: https://github.com/cran/PL94171
* URL: https://corymccartan.github.io/PL94171/, https://github.com/CoryMcCartan/PL94171/
* BugReports: https://github.com/CoryMcCartan/PL94171/issues
* Date/Publication: 2021-06-15 15:00:02 UTC
* Number of recursive dependencies: 90

Run `cloud_details(, "PL94171")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    Running examples in ‘PL94171-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: pl_crosswalk
    > ### Title: Download Block Crosswalk Files
    > ### Aliases: pl_crosswalk
    > 
    > ### ** Examples
    > 
    > pl_crosswalk("RI", 2010, 2020)
    Error in vroom_(file, delim = delim %||% col_types$delim, col_names = col_names,  : 
      embedded nul in string: 'PK\003\004\024\0\0\0\b\0\x8f'
    Calls: pl_crosswalk -> <Anonymous> -> <Anonymous> -> vroom_
    Execution halted
    ```

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      • On CRAN (2)
      
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Error (test-crosswalk.R:2:5): crosswalks are formatted correctly ────────────
      Error: embedded nul in string: 'PK\003\004\024\0\0\0\b\0\x8f'
      Backtrace:
          █
       1. └─PL94171::pl_crosswalk("RI", 2010, 2020) test-crosswalk.R:2:4
       2.   └─readr::read_delim(...)
       3.     └─vroom::vroom(...)
       4.       └─vroom:::vroom_(...)
      
      [ FAIL 1 | WARN 0 | SKIP 2 | PASS 18 ]
      Error: Test failures
      Execution halted
    ```

# rhmmer

<details>

* Version: 0.1.0
* Source code: https://github.com/cran/rhmmer
* URL: https://github.com/arendsee/rhmmer
* BugReports: https://github.com/arendsee/rhmmer/issues
* Date/Publication: 2017-12-19 19:14:30 UTC
* Number of recursive dependencies: 51

Run `cloud_details(, "rhmmer")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > 
      > test_check("rhmmer")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test-parse.R:11:3): read_tblout works ──────────────────────────────
      `read_tblout(tblout_file)` produced messages.
      ── Failure (test-parse.R:17:3): read_domtblout works ───────────────────────────
      `read_domtblout(domtblout_file)` produced messages.
      ── Failure (test-parse.R:27:3): files with no data do not fail ─────────────────
      `read_domtblout(empty_tblout_file)` produced messages.
      ── Failure (test-parse.R:28:3): files with no data do not fail ─────────────────
      `read_tblout(empty_domtblout_file)` produced messages.
      
      [ FAIL 4 | WARN 0 | SKIP 0 | PASS 6 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```


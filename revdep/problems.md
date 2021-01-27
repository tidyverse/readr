# aire.zmvm

<details>

* Version: 0.8.2
* Source code: https://github.com/cran/aire.zmvm
* URL: https://hoyodesmog.diegovalle.net/aire.zmvm/, https://github.com/diegovalle/aire.zmvm
* BugReports: https://github.com/diegovalle/aire.zmvm/issues
* Date/Publication: 2019-03-30 18:00:03 UTC
* Number of recursive dependencies: 102

Run `cloud_details(, "aire.zmvm")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
        1. └─testthat::expect_true(is.integer2(1986)) test_utils.R:19:2
        2.   └─testthat:::expect_waldo_constant(act, TRUE, info = info)
        3.     └─testthat:::waldo_compare(...)
        4.       └─waldo::compare
        5.         └─base::getExportedValue(pkg, name)
        6.           └─base::asNamespace(ns)
        7.             └─base::getNamespace(ns)
        8.               └─base::loadNamespace(name)
        9.                 └─base::withRestarts(stop(cond), retry_loadNamespace = function() NULL)
       10.                   └─base:::withOneRestart(expr, restarts[[1L]])
       11.                     └─base:::doWithOneRestart(return(expr), restart)
      
      [ FAIL 3 | WARN 0 | SKIP 13 | PASS 162 ]
      Error: Test failures
      Execution halted
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 53 marked UTF-8 strings
    ```

## Newly fixed

*   checking whether package ‘aire.zmvm’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/tmp/workdir/aire.zmvm/old/aire.zmvm.Rcheck/00install.out’ for details.
    ```

# arealDB

<details>

* Version: 0.3.4
* Source code: https://github.com/cran/arealDB
* URL: https://gitlab.com/luckinet/software/arealDB
* BugReports: https://gitlab.com/luckinet/software/arealDB/issues
* Date/Publication: 2020-07-01 09:10:06 UTC
* Number of recursive dependencies: 76

Run `cloud_details(, "arealDB")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
      
      
      
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test_04_regDataseries.R:24:3): a dataseries inventory entry can be produced ──
      output[-7] not equal to db[-7].
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component 2: Modes: numeric, externalptr >
      Attributes: < Component 2: target is numeric, current is externalptr >
      
      [ FAIL 1 | WARN 3 | SKIP 0 | PASS 102 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 8 marked UTF-8 strings
    ```

# dataverse

<details>

* Version: 0.3.0
* Source code: https://github.com/cran/dataverse
* URL: https://github.com/iqss/dataverse-client-r
* BugReports: https://github.com/iqss/dataverse-client-r/issues
* Date/Publication: 2021-01-19 06:40:14 UTC
* Number of recursive dependencies: 69

Run `cloud_details(, "dataverse")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component "class": Lengths (3, 4) differ (string compare on first 3) >
      Attributes: < Component "class": 3 string mismatches >
      Attributes: < Component 2: target is externalptr, current is numeric >
      ── Failure (tests-get_dataframe-dataframe-basketball.R:38:3): roster-by-id ─────
      `actual` not equal to `expected_file`.
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component "class": Lengths (3, 4) differ (string compare on first 3) >
      Attributes: < Component "class": 3 string mismatches >
      Attributes: < Component 2: target is externalptr, current is numeric >
      
      [ FAIL 3 | WARN 0 | SKIP 0 | PASS 96 ]
      Error: Test failures
      Execution halted
    ```

# ddpcr

<details>

* Version: 1.15
* Source code: https://github.com/cran/ddpcr
* URL: https://github.com/daattali/ddpcr
* BugReports: https://github.com/daattali/ddpcr/issues
* Date/Publication: 2020-06-02 07:10:07 UTC
* Number of recursive dependencies: 99

Run `cloud_details(, "ddpcr")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      plate_data(plate) not equal to `expected_data`.
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component 2: Modes: numeric, externalptr >
      Attributes: < Component 2: Lengths: 11, 1 >
      Attributes: < Component 2: target is numeric, current is externalptr >
      ── Failure (test-v174.R:7:3): reading v174 works ───────────────────────────────
      `expected_data` not equal to plate_data(plate).
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component 2: target is externalptr, current is numeric >
      
      [ FAIL 7 | WARN 7 | SKIP 0 | PASS 262 ]
      Error: Test failures
      Execution halted
    ```

# echor

<details>

* Version: 0.1.5
* Source code: https://github.com/cran/echor
* BugReports: https://github.com/mps9506/echor/issues
* Date/Publication: 2020-08-05 15:30:03 UTC
* Number of recursive dependencies: 108

Run `cloud_details(, "echor")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Backtrace:
          █
       1. ├─testthat::expect_is(...) test-expected_objects.R:20:4
       2. │ └─testthat::quasi_label(enquo(object), label, arg = "object")
       3. │   └─rlang::eval_bare(expr, quo_get_env(quo))
       4. ├─echor::echoAirGetFacilityInfo(...)
       5. │ └─echor:::getDownload("caa", qid, qcolumns, col_types = colTypes)
       6. │   └─readr::read_csv(...)
       7. │     └─vroom::vroom(...)
       8. │       └─vroom:::vroom_(...)
       9. └─(function (spec, col_names, col_select, name_repair) ...
      
      [ FAIL 1 | WARN 0 | SKIP 0 | PASS 10 ]
      Error: Test failures
      Execution halted
    ```

# eyelinker

<details>

* Version: 0.2.0
* Source code: https://github.com/cran/eyelinker
* URL: https://github.com/a-hurst/eyelinker
* BugReports: https://github.com/a-hurst/eyelinker/issues
* Date/Publication: 2019-09-22 22:00:03 UTC
* Number of recursive dependencies: 80

Run `cloud_details(, "eyelinker")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    Running examples in ‘eyelinker-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: read.asc
    > ### Title: Read EyeLink ASC Files
    > ### Aliases: read.asc
    > 
    > ### ** Examples
    > 
    > # Example file from SR research that ships with the package
    > fpath <- system.file("extdata/mono500.asc.gz", package = "eyelinker")
    > dat <- read.asc(fpath)
    Error: '7196720	  512.8	  394.5	 1063.0	...' does not exist in current working directory ('/tmp/workdir/eyelinker/new/eyelinker.Rcheck').
    Execution halted
    ```

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
       6.   └─vroom:::check_path(path)
      ── Error (test_eyelink_parser.R:232:5): test_block_parsing ─────────────────────
      Error: '** VERSION: EYELINK II 1' does not exist in current working directory ('/tmp/workdir/eyelinker/new/eyelinker.Rcheck/tests/testthat').
      Backtrace:
          █
       1. ├─eyelinker::read.asc(testfile) test_eyelink_parser.R:232:4
       2. │ └─readr::read_lines(fname, progress = FALSE)
       3. │   └─vroom::vroom_lines(...)
       4. │     └─vroom:::vroom_(...)
       5. └─(function (path, write = FALSE) ...
       6.   └─vroom:::check_path(path)
      
      [ FAIL 3 | WARN 0 | SKIP 0 | PASS 28 ]
      Error: Test failures
      Execution halted
    ```

# iNZightTools

<details>

* Version: 1.10
* Source code: https://github.com/cran/iNZightTools
* URL: http://inzight.nz
* BugReports: https://github.com/iNZightVIT/iNZightTools/issues
* Date/Publication: 2020-12-14 06:00:09 UTC
* Number of recursive dependencies: 79

Run `cloud_details(, "iNZightTools")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test-read_text.R:11:5): Tab-delim text reads ───────────────────────
      read_text(text) not equal to readr::read_tsv(text) %>% dplyr::mutate(y = as.factor(y)).
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component "class": Lengths (4, 3) differ (string compare on first 3) >
      Attributes: < Component "class": 3 string mismatches >
      Attributes: < Component 2: Modes: numeric, externalptr >
      Attributes: < Component 2: Lengths: 4, 1 >
      Attributes: < Component 2: target is numeric, current is externalptr >
      
      [ FAIL 1 | WARN 0 | SKIP 4 | PASS 238 ]
      Error: Test failures
      Execution halted
    ```

# lazytrade

<details>

* Version: 0.4.4
* Source code: https://github.com/cran/lazytrade
* URL: https://vladdsm.github.io/myblog_attempt/topics/lazy%20trading/, https://github.com/vzhomeexperiments/lazytrade
* BugReports: https://github.com/vzhomeexperiments/lazytrade/issues
* Date/Publication: 2021-01-19 22:30:02 UTC
* Number of recursive dependencies: 81

Run `cloud_details(, "lazytrade")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    ...
    Rows: 39
    Columns: 3
    Delimiter: ","
    chr [2]: Pair, Period
    dbl [1]: Magic
    
    Use `spec()` to retrieve the guessed column specification
    Pass a specification to the `col_types` argument to quiet this message
    > 
    > data(profit_factorDF)
    > 
    > 
    > # without writing to the file
    > check_if_optimize(x = profit_factorDF,
    +                   system_list = system_list,
    +                   path_data,
    +                   num_trades_to_consider = 3,
    +                   profit_factor_limit = 0.8,
    +                   write_mode = TRUE)
    Error: Trading system list must be as spec_tbl_df
    Execution halted
    ```

# MIMSunit

<details>

* Version: 0.9.2
* Source code: https://github.com/cran/MIMSunit
* URL: https://mhealthgroup.github.io/MIMSunit/, https://github.com/mhealthgroup/MIMSunit/tree/master
* BugReports: https://github.com/mhealthgroup/MIMSunit/issues/
* Date/Publication: 2020-08-01 00:20:10 UTC
* Number of recursive dependencies: 113

Run `cloud_details(, "MIMSunit")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    ...
    >   # Check more
    >   summary(df)
     HEADER_TIME_STAMP                      X                  Y            
     Min.   :2018-06-14 11:21:00.00   Min.   :-0.44400   Min.   :-0.366000  
     1st Qu.:2018-06-14 12:20:11.75   1st Qu.:-0.08000   1st Qu.: 0.000000  
     Median :2018-06-14 13:19:23.50   Median :-0.08000   Median : 0.004000  
     Mean   :2018-06-14 13:19:23.50   Mean   :-0.07808   Mean   : 0.002706  
     3rd Qu.:2018-06-14 14:18:35.25   3rd Qu.:-0.07500   3rd Qu.: 0.004000  
     Max.   :2018-06-14 15:17:47.00   Max.   : 0.28500   Max.   : 0.382000  
           Z         
     Min.   :-1.491  
     1st Qu.:-1.056  
     Median :-1.052  
     Mean   :-1.052  
     3rd Qu.:-1.052  
     Max.   :-0.785  
    > 
    >   # If set has_ts wrong, you should see a warning
    >   df = import_actigraph_csv(filepath, has_ts=TRUE)
    Error: Unnamed `col_types` must have the same length as `col_names`.
    Execution halted
    ```

# qualtRics

<details>

* Version: 3.1.4
* Source code: https://github.com/cran/qualtRics
* URL: https://docs.ropensci.org/qualtRics/, https://github.com/ropensci/qualtRics
* BugReports: https://github.com/ropensci/qualtRics/issues
* Date/Publication: 2021-01-14 20:40:02 UTC
* Number of recursive dependencies: 73

Run `cloud_details(, "qualtRics")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
       10. ├─purrr::map_dfr(JSON, jsonlite::fromJSON)
       11. │ └─purrr::map(.x, .f, ...)
       12. │   └─jsonlite:::.f(.x[[i]], ...)
       13. │     └─jsonlite:::parse_and_simplify(...)
       14. │       └─jsonlite:::parseJSON(txt, bigint_as_char)
       15. │         └─jsonlite:::parse_string(txt, bigint_as_char)
       16. └─base::.handleSimpleError(...)
       17.   └─dplyr:::h(simpleError(msg, call))
      
      [ FAIL 1 | WARN 1 | SKIP 3 | PASS 138 ]
      Error: Test failures
      In addition: Warning message:
      In readRenviron("~/.Renviron") :
        file '/root/.Renviron' cannot be opened for reading
      Execution halted
    ```

# radous

<details>

* Version: 0.1.2
* Source code: https://github.com/cran/radous
* URL: https://github.com/feddelegrand7/radous
* BugReports: https://github.com/feddelegrand7/radous/issues
* Date/Publication: 2021-01-18 21:20:06 UTC
* Number of recursive dependencies: 51

Run `cloud_details(, "radous")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Complete output:
      > library(testthat)
      > library(radous)
      > 
      > test_check("radous")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test-test_get_data.R:20:3): testing identical results ──────────────
      `final` not identical to get_data(n = 10, seed = "123").
      Objects equal but not identical
      
      [ FAIL 1 | WARN 0 | SKIP 0 | PASS 2 ]
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
* Number of recursive dependencies: 54

Run `cloud_details(, "rhmmer")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
       14. │ └─base::is.data.frame(df)
       15. ├─tidyr::separate(...)
       16. ├─tidyr:::separate.data.frame(...)
       17. │ └─tidyselect::vars_pull(names(data), !!enquo(col))
       18. │   ├─tidyselect:::instrument_base_errors(...)
       19. │   │ └─base::withCallingHandlers(...)
       20. │   └─rlang::eval_tidy(enquo(var), set_names(seq_along(vars), vars))
       21. ├─X
       22. ├─rlang:::`$.rlang_data_pronoun`(.data, X)
       23. │ └─rlang:::data_pronoun_get(x, nm)
       24. └─rlang:::abort_data_pronoun(x)
      
      [ FAIL 5 | WARN 32 | SKIP 0 | PASS 2 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```

# rPraat

<details>

* Version: 1.3.1
* Source code: https://github.com/cran/rPraat
* URL: https://github.com/bbTomas/rPraat/
* BugReports: https://github.com/bbTomas/rPraat/issues
* Date/Publication: 2020-04-04 17:10:02 UTC
* Number of recursive dependencies: 56

Run `cloud_details(, "rPraat")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
       6.   └─rPraat:::tg.read_lines(flines, find)
      ── Failure (test_rpraat.R:1696:5): col.write ───────────────────────────────────
      {
          ...
      } not equal to `col2`.
      Component 2: Component 3: Component 4: 1 string mismatch
      ── Failure (test_rpraat.R:1705:5): col.write ───────────────────────────────────
      {
          ...
      } not equal to `col2`.
      Component 2: Component 3: Component 4: 1 string mismatch
      
      [ FAIL 4 | WARN 3 | SKIP 0 | PASS 476 ]
      Error: Test failures
      Execution halted
    ```

# swirlify

<details>

* Version: 0.5.3
* Source code: https://github.com/cran/swirlify
* URL: http://swirlstats.com
* Date/Publication: 2019-05-28 07:40:03 UTC
* Number of recursive dependencies: 76

Run `cloud_details(, "swirlify")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > 
      > test_check("swirlify")
      ══ Skipped tests ═══════════════════════════════════════════════════════════════
      ● Locale is not en_US.UTF-8 (1)
      
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test_google_form_decode.R:37:3): Google Forms can be Properly Decoded. ──
      `cr` not equal to rbind(correct_responses, correct_responses, correct_responses).
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component 2: target is externalptr, current is numeric >
      
      [ FAIL 1 | WARN 0 | SKIP 1 | PASS 6 ]
      Error: Test failures
      Execution halted
    ```

# tidystats

<details>

* Version: 0.5
* Source code: https://github.com/cran/tidystats
* URL: https://willemsleegers.github.io/tidystats/
* BugReports: https://github.com/WillemSleegers/tidystats/issues
* Date/Publication: 2020-09-21 16:50:02 UTC
* Number of recursive dependencies: 90

Run `cloud_details(, "tidystats")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Please note that this update (again) breaks much of the code from previous versions; so please check your old code carefully.
      > 
      > test_check("tidystats")
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure (test_tidy_stats_to_data_frame.R:45:3): tidy stats to data frame works ──
      `results_df` not equal to `test_results`.
      Attributes: < Names: 1 string mismatch >
      Attributes: < Length mismatch: comparison on first 2 components >
      Attributes: < Component 2: Modes: numeric, externalptr >
      Attributes: < Component 2: Lengths: 69, 1 >
      Attributes: < Component 2: target is numeric, current is externalptr >
      
      [ FAIL 1 | WARN 0 | SKIP 0 | PASS 70 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 113 marked UTF-8 strings
    ```

# weathercan

<details>

* Version: 0.5.0
* Source code: https://github.com/cran/weathercan
* URL: https://docs.ropensci.org/weathercan/, https://github.com/ropensci/weathercan/
* BugReports: https://github.com/ropensci/weathercan/issues/
* Date/Publication: 2021-01-15 06:00:03 UTC
* Number of recursive dependencies: 138

Run `cloud_details(, "weathercan")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      `{ ... }` produced warnings.
      ── Failure (test_06_weather_dl_1_hour.R:175:3): weather (hour) verbose and quiet ──
      `weather_dl(...)` produced warnings.
      ── Failure (test_06_weather_dl_1_hour.R:186:3): weather (hour) handles data with different numbers of columns ──
      `... <- NULL` produced warnings, messages.
      ── Failure (test_06_weather_dl_1_hour.R:210:3): weather (hour) crosses the year line ──
      `... <- NULL` produced warnings.
      ── Failure (test_06_weather_dl_3_month.R:60:3): weather (month) no data fails nicely ──
      `expect_message(...)` produced warnings.
      ── Failure (test_06_weather_dl_3_month.R:69:3): weather (month) no data fails nicely ──
      `expect_message(...)` produced warnings.
      
      [ FAIL 9 | WARN 32 | SKIP 13 | PASS 537 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘memoise’
      All declared Imports should be used.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 3 marked UTF-8 strings
    ```


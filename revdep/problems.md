# admixr (0.9.1)

* GitHub: <https://github.com/bodkan/admixr>
* Email: <mailto:contact@bodkan.net>
* GitHub mirror: <https://github.com/cran/admixr>

Run `revdepcheck::cloud_details(, "admixr")` for more info

## Newly broken

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```

# arkdb (0.0.18)

* GitHub: <https://github.com/ropensci/arkdb>
* Email: <mailto:cboettig@gmail.com>
* GitHub mirror: <https://github.com/cran/arkdb>

Run `revdepcheck::cloud_details(, "arkdb")` for more info

## Newly broken

*   checking re-building of vignette outputs ... ERROR
     ```
     ...
     --- re-building ‘arkdb.Rmd’ using rmarkdown
     
     Quitting from arkdb.Rmd:163-166 [unnamed-chunk-11]
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     <error/rlang_error>
     Error in `readr::write_tsv()`:
     ! unused argument (path = path)
     ---
     Backtrace:
         ▆
      1. └─arkdb::ark(db, dir, streamable_table = stream)
      2.   └─arkdb:::ark_file(...)
      3.     └─arkdb:::keep_open(...)
      4.       └─streamable_table$write(header, con, omit_header = FALSE)
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     
     Error: processing vignette 'arkdb.Rmd' failed with diagnostics:
     unused argument (path = path)
     --- failed re-building ‘arkdb.Rmd’
     
     SUMMARY: processing the following file failed:
       ‘arkdb.Rmd’
     
     Error: Vignette re-building failed.
     Execution halted
     ```

# chronochrt (0.1.3)

* Email: <mailto:thomas.rose@daad-alumni.de>
* GitHub mirror: <https://github.com/cran/chronochrt>

Run `revdepcheck::cloud_details(, "chronochrt")` for more info

## Newly broken

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```

# eyelinker (0.2.1)

* GitHub: <https://github.com/a-hurst/eyelinker>
* Email: <mailto:ajhurst@uwaterloo.ca>
* GitHub mirror: <https://github.com/cran/eyelinker>

Run `revdepcheck::cloud_details(, "eyelinker")` for more info

## Newly broken

*   checking whether package ‘eyelinker’ can be installed ... ERROR
     ```
     Installation failed.
     See ‘/tmp/workdir/eyelinker/new/eyelinker.Rcheck/00install.out’ for details.
     ```

## Installation

### Devel

```
* installing *source* package ‘eyelinker’ ...
** this is package ‘eyelinker’ version ‘0.2.1’
** package ‘eyelinker’ successfully unpacked and MD5 sums checked
** using staged installation
** R
** inst
** byte-compile and prepare package for lazy loading
Error: object ‘read_table2’ is not exported by 'namespace:readr'
Execution halted
ERROR: lazy loading failed for package ‘eyelinker’
* removing ‘/tmp/workdir/eyelinker/new/eyelinker.Rcheck/eyelinker’


```
### CRAN

```
* installing *source* package ‘eyelinker’ ...
** this is package ‘eyelinker’ version ‘0.2.1’
** package ‘eyelinker’ successfully unpacked and MD5 sums checked
** using staged installation
** R
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
*** copying figures
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
** testing if installed package can be loaded from final location
** testing if installed package keeps a record of temporary installation path
* DONE (eyelinker)


```
# genogeographer (0.1.19)

* Email: <mailto:tvede@math.aau.dk>
* GitHub mirror: <https://github.com/cran/genogeographer>

Run `revdepcheck::cloud_details(, "genogeographer")` for more info

## Newly broken

*   checking whether package ‘genogeographer’ can be installed ... WARNING
     ```
     Found the following significant warnings:
       Note: possible error in 'write_csv(aims_example, ': unused argument (path = file) 
     See ‘/tmp/workdir/genogeographer/new/genogeographer.Rcheck/00install.out’ for details.
     Information on the location(s) of code generating the ‘Note’s can be
     obtained by re-running with environment variable R_KEEP_PKG_SOURCE set
     to ‘yes’.
     ```

*   checking R code for possible problems ... NOTE
     ```
     server_fct : <anonymous>: possible error in write_csv(aims_example,
       path = file): unused argument (path = file)
     ```

# MIMSunit (0.11.2)

* GitHub: <https://github.com/mhealthgroup/MIMSunit>
* Email: <mailto:tang.q@northeastern.edu>
* GitHub mirror: <https://github.com/cran/MIMSunit>

Run `revdepcheck::cloud_details(, "MIMSunit")` for more info

## Newly broken

*   checking examples ... ERROR
     ```
     ...
     > 
     > ### ** Examples
     > 
     >   default_ops = options()
     >   options(digits.secs=3)
     >   # Use the sample mhealth csv file provided by the package
     >   filepath = system.file('extdata', 'mhealth.csv', package='MIMSunit')
     >   filepath
     [1] "/tmp/workdir/MIMSunit/new/MIMSunit.Rcheck/MIMSunit/extdata/mhealth.csv"
     > 
     >   # Load the file
     >   df = import_mhealth_csv(filepath)
     Error:
     ! The `quoted_na` argument of `read_csv()` was deprecated in readr 2.0.0
       and is now defunct.
     ℹ This argument is not supported in readr edition 2.
     ℹ Use `with_edition(1, ...)` or `local_edition(1)` to use the legacy edition 1.
     Backtrace:
         ▆
      1. └─MIMSunit::import_mhealth_csv(filepath)
      2.   └─readr::read_csv(file = filepath, quoted_na = TRUE, col_types = coltypes)
      3.     └─lifecycle::deprecate_stop(...)
      4.       └─lifecycle:::deprecate_stop0(msg)
      5.         └─rlang::cnd_signal(...)
     Execution halted
     ```

# nlrx (0.4.5)

* GitHub: <https://github.com/ropensci/nlrx>
* Email: <mailto:nlrx@mailbox.org>
* GitHub mirror: <https://github.com/cran/nlrx>

Run `revdepcheck::cloud_details(, "nlrx")` for more info

## Newly broken

*   checking examples ... ERROR
     ```
     Running examples in ‘nlrx-Ex.R’ failed
     The error most likely occurred in:
     
     > ### Name: write_simoutput
     > ### Title: Write attached NetLogo simulation output to file
     > ### Aliases: write_simoutput
     > 
     > ### ** Examples
     > 
     > 
     > # Load nl object including output data from testdata
     > nl <- nl_lhs
     > 
     > # Write output to outpath directory
     > write_simoutput(nl, outpath=tempdir())
     Error in readr::write_csv(x = getsim(nl, "simoutput"), path = outfilename) : 
       unused argument (path = outfilename)
     Calls: write_simoutput
     Execution halted
     ```

# params (0.7.7)

* GitHub: <https://github.com/sahilseth/params>
* Email: <mailto:me@sahilseth.com>
* GitHub mirror: <https://github.com/cran/params>

Run `revdepcheck::cloud_details(, "params")` for more info

## Newly broken

*   checking R code for possible problems ... NOTE
     ```
     write_sheet: possible error in write_delim(x = x, file = file, delim =
       "\t", quote_escape = "double", ...): unused argument (quote_escape =
       "double")
     write_sheet: possible error in write_delim(x = x, file = file, delim =
       ",", quote_escape = "double", ...): unused argument (quote_escape =
       "double")
     ```

# readit (1.0.0)

* GitHub: <https://github.com/ryapric/readit>
* Email: <mailto:ryapric@gmail.com>
* GitHub mirror: <https://github.com/cran/readit>

Run `revdepcheck::cloud_details(, "readit")` for more info

## Newly broken

*   checking examples ... ERROR
     ```
     ...
     > 
     > ### ** Examples
     > 
     > readit(system.file("examples", "csv.csv", package = "readit"))
     File guessed to be CSV (system.file("examples", "csv.csv", package = "readit"))
     Rows: 5 Columns: 5
     ── Column specification ────────────────────────────────────────────────────────
     Delimiter: ","
     chr (5): testheader1, testheader2, testheader3, testheader4, testheader5
     
     ℹ Use `spec()` to retrieve the full column specification for this data.
     ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
     # A tibble: 5 × 5
       testheader1 testheader2 testheader3 testheader4 testheader5
       <chr>       <chr>       <chr>       <chr>       <chr>      
     1 testdata11  testdata12  testdata13  testdata14  testdata15 
     2 testdata21  testdata22  testdata23  testdata24  testdata25 
     3 testdata31  testdata32  testdata33  testdata34  testdata35 
     4 testdata41  testdata42  testdata43  testdata44  testdata45 
     5 testdata51  testdata52  testdata53  testdata54  testdata55 
     > readit(system.file("examples", "tab_sep.txt", package = "readit"))
     Error in read_table2(x, n_max = n_max) : 
       could not find function "read_table2"
     Calls: readit ... is.data.frame -> suppressMessages -> withCallingHandlers
     Execution halted
     ```

*   checking tests ... ERROR
     ```
     ...
         7.         ├─base::suppressMessages(suppressWarnings(y(.data)))
         8.         │ └─base::withCallingHandlers(...)
         9.         ├─base::suppressWarnings(y(.data))
        10.         │ └─base::withCallingHandlers(...)
        11.         └─readit (local) y(.data)
       ── Error ('test_readit.R:68:3'): Additional arguments are picked up by readit ──
       Error in `read_table2(x, n_max = n_max)`: could not find function "read_table2"
       Backtrace:
            ▆
         1. └─readit::readit(...) at test_readit.R:68:3
         2.   └─readit:::guess_txt(.data)
         3.     └─base::lapply(delims_test, function(y) length(colnames(suppressMessages(suppressWarnings(y(.data))))))
         4.       └─readit (local) FUN(X[[i]], ...)
         5.         ├─base::colnames(suppressMessages(suppressWarnings(y(.data))))
         6.         │ └─base::is.data.frame(x)
         7.         ├─base::suppressMessages(suppressWarnings(y(.data)))
         8.         │ └─base::withCallingHandlers(...)
         9.         ├─base::suppressWarnings(y(.data))
        10.         │ └─base::withCallingHandlers(...)
        11.         └─readit (local) y(.data)
       
       [ FAIL 3 | WARN 0 | SKIP 0 | PASS 12 ]
       Error:
       ! Test failures.
       Execution halted
     ```

*   checking R code for possible problems ... NOTE
     ```
     guess_txt : <anonymous>: no visible global function definition for
       ‘read_table2’
     Undefined global functions or variables:
       read_table2
     ```

# rubias (0.3.4)

* Email: <mailto:eric.anderson@noaa.gov>
* GitHub mirror: <https://github.com/cran/rubias>

Run `revdepcheck::cloud_details(, "rubias")` for more info

## Newly broken

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```

# skater (0.1.2)

* GitHub: <https://github.com/signaturescience/skater>
* Email: <mailto:vustephen@gmail.com>
* GitHub mirror: <https://github.com/cran/skater>

Run `revdepcheck::cloud_details(, "skater")` for more info

## Newly broken

*   checking examples ... ERROR
     ```
     Running examples in ‘skater-Ex.R’ failed
     The error most likely occurred in:
     
     > ### Name: read_akt
     > ### Title: Read AKT kin output file
     > ### Aliases: read_akt
     > 
     > ### ** Examples
     > 
     > aktFile <- system.file("extdata", "3gens.akt", package="skater", mustWork=TRUE)
     > akt <- read_akt(aktFile)
     Error: 'read_table2' is not an exported object from 'namespace:readr'
     Execution halted
     ```

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```

# suddengains (0.7.2)

* GitHub: <https://github.com/milanwiedemann/suddengains>
* Email: <mailto:milan.wiedemann@gmail.com>
* GitHub mirror: <https://github.com/cran/suddengains>

Run `revdepcheck::cloud_details(, "suddengains")` for more info

## Newly broken

*   checking examples ... ERROR
     ```
     ...
     > temp <- tempfile(pattern = "byperson", fileext = ".csv")
     > 
     > # Write byperson dataset (CSV file)
     > # To write a different format change the 'format' argument ...
     > # ... as well as the file extension in the 'path' argument
     > write_byperson(data = sgdata,
     +                sg_crit1_cutoff = 7,
     +                id_var_name = "id",
     +                tx_start_var_name = "bdi_s1",
     +                tx_end_var_name = "bdi_s12",
     +                sg_var_list = c("bdi_s1", "bdi_s2", "bdi_s3", "bdi_s4",
     +                                "bdi_s5", "bdi_s6", "bdi_s7", "bdi_s8",
     +                                "bdi_s9", "bdi_s10", "bdi_s11", "bdi_s12"),
     +                sg_measure_name = "bdi",
     +                identify_sg_1to2 = FALSE,
     +                multiple_sg_select = "largest",
     +                format = "CSV",
     +                path = temp)
     First, second, and third sudden gains criteria were applied.
     The critical value for the third criterion was adjusted for missingness.
     The first gain/loss was selected in case of multiple gains/losses.
     Error in readr::write_csv(x = byperson_data, path = path, ...) : 
       unused argument (path = path)
     Calls: write_byperson
     Execution halted
     ```

## In both

*   checking dependencies in R code ... NOTE
     ```
     Namespace in Imports field not imported from: ‘cli’
       All declared Imports should be used.
     ```

*   checking Rd files ... NOTE
     ```
     ...
     checkRd: (-1) sgdata_bad.Rd:16: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:17: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:18: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:19: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:20: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:21: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:22: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:23: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:24: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:25: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:26: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:27: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:28: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:29: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:30: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:31: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:32: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:33: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:34: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:35: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:36: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:37: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:38: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:39: Lost braces in \itemize; meant \describe ?
     checkRd: (-1) sgdata_bad.Rd:40: Lost braces in \itemize; meant \describe ?
     ```

# tidypopgen (0.4.0)

* GitHub: <https://github.com/EvolEcolGroup/tidypopgen>
* Email: <mailto:am315@cam.ac.uk>
* GitHub mirror: <https://github.com/cran/tidypopgen>

Run `revdepcheck::cloud_details(, "tidypopgen")` for more info

## Newly broken

*   checking tests ... ERROR
     ```
     ...
       Loading required package: tibble
       > 
       > test_check("tidypopgen")
       Adding missing grouping variables: `population`
       Saving _problems/test_gt_extract_f2-45.R
       [ FAIL 1 | WARN 3 | SKIP 3 | PASS 1017 ]
       
       ══ Skipped tests (3) ═══════════════════════════════════════════════════════════
       • (system2("which", args = "admixture", stdout = NULL) != 0) &&
         !requireNamespace("tidygenclust", quietly = TRUE) is TRUE (2):
         'test_gt_admix_methods.R:2:1', 'test_gt_admixture.R:2:1'
       • On CRAN (1): 'test_gt_pca.R:348:1'
       
       ══ Failed tests ════════════════════════════════════════════════════════════════
       ── Error ('test_gt_extract_f2.R:41:3'): extract f2 correctly ───────────────────
       Error in `read_table2(bimfile, col_names = nam, progress = FALSE, col_types = "ccddcc")`: could not find function "read_table2"
       Backtrace:
           ▆
        1. └─admixtools:::anygeno_to_aftable(...) at test_gt_extract_f2.R:41:3
        2.   └─admixtools (local) geno_to_aftable(...)
       
       [ FAIL 1 | WARN 3 | SKIP 3 | PASS 1017 ]
       Error:
       ! Test failures.
       Execution halted
     ```

# tidytreatment (0.3.1)

* GitHub: <https://github.com/bonStats/tidytreatment>
* Email: <mailto:joshuajbon@gmail.com>
* GitHub mirror: <https://github.com/cran/tidytreatment>

Run `revdepcheck::cloud_details(, "tidytreatment")` for more info

## Newly broken

*   checking re-building of vignette outputs ... ERROR
     ```
     Error(s) in re-building vignettes:
     --- re-building ‘use-tidytreatment-BART.Rmd’ using rmarkdown
     ```

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```

# xpose (0.4.21)

* GitHub: <https://github.com/UUPharmacometrics/xpose>
* Email: <mailto:guiastrennec@gmail.com>
* GitHub mirror: <https://github.com/cran/xpose>

Run `revdepcheck::cloud_details(, "xpose")` for more info

## Newly broken

*   checking dependencies in R code ... WARNING
     ```
     Missing or unexported object: ‘readr::read_table2’
     ```


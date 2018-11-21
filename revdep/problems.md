# ActisoftR

Version: 0.0.2

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# aire.zmvm

Version: 0.8.0

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 52 marked UTF-8 strings
    ```

# alphavantager

Version: 0.1.0

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# annotatr

Version: 1.8.0

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘annotatr-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: build_annotations
    > ### Title: A function to build annotations from TxDb.* and AnnotationHub
    > ###   resources
    > ### Aliases: build_annotations
    > 
    > ### ** Examples
    > 
    > # Example with hg19 gene promoters
    > annots = c('hg19_genes_promoters')
    > annots_gr = build_annotations(genome = 'hg19', annotations = annots)
    Error in get(txdb_name) : 
      object 'TxDb.Hsapiens.UCSC.hg19.knownGene' not found
    Calls: build_annotations
    Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    snapshotDate(): 2018-04-30
    Building annotation Gm12878 from AnnotationHub resource AH23256 ...
    downloading 0 resources
    loading from cache 
        '/Users/jhester//.AnnotationHub/28684'
    require("rtracklayer")
    Quitting from lines 154-171 (annotatr-vignette.Rmd) 
    Error: processing vignette 'annotatr-vignette.Rmd' failed with diagnostics:
    object 'TxDb.Hsapiens.UCSC.hg19.knownGene' not found
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Packages suggested but not available for checking:
      ‘devtools’ ‘org.Dm.eg.db’ ‘org.Gg.eg.db’ ‘org.Hs.eg.db’
      ‘org.Mm.eg.db’ ‘org.Rn.eg.db’ ‘TxDb.Dmelanogaster.UCSC.dm3.ensGene’
      ‘TxDb.Dmelanogaster.UCSC.dm6.ensGene’
      ‘TxDb.Ggallus.UCSC.galGal5.refGene’
      ‘TxDb.Hsapiens.UCSC.hg19.knownGene’
      ‘TxDb.Hsapiens.UCSC.hg38.knownGene’
      ‘TxDb.Mmusculus.UCSC.mm9.knownGene’
      ‘TxDb.Mmusculus.UCSC.mm10.knownGene’
      ‘TxDb.Rnorvegicus.UCSC.rn4.ensGene’
      ‘TxDb.Rnorvegicus.UCSC.rn5.refGene’
      ‘TxDb.Rnorvegicus.UCSC.rn6.refGene’
    ```

*   checking R code for possible problems ... NOTE
    ```
    plot_coannotations: no visible binding for global variable ‘.’
      (.../revdep/checks.noindex/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:176-178)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks.noindex/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:463-480)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks.noindex/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:466-471)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks.noindex/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:473-478)
    Undefined global functions or variables:
      .
    ```

# anyflights

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘tibble’
      All declared Imports should be used.
    ```

# ArchaeoPhases

Version: 1.3

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘DT’
      All declared Imports should be used.
    ```

# auk

Version: 0.3.0

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 552 marked UTF-8 strings
    ```

# BALCONY

Version: 0.2.8

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘base’
      All declared Imports should be used.
    ```

# BaMORC

Version: 1.0

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# BANEScarparkinglite

Version: 0.1.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘zoo’
      All declared Imports should be used.
    ```

# banR

Version: 0.2.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘stringr’
      All declared Imports should be used.
    ```

# BiocPkgTools

Version: 1.0.1

## In both

*   checking R code for possible problems ... NOTE
    ```
    ...
    process_data: no visible binding for global variable ‘biocViews’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:47-66)
    process_data: no visible binding for global variable ‘Description’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:47-66)
    process_data: no visible binding for global variable ‘downloads_month’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:47-66)
    process_data: no visible binding for global variable ‘downloads_total’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:47-66)
    summarise_dl_stats: no visible binding for global variable ‘Package’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:75-80)
    summarise_dl_stats: no visible binding for global variable
      ‘Nb_of_downloads’
      (.../revdep/checks.noindex/BiocPkgTools/new/BiocPkgTools.Rcheck/00_pkg_src/BiocPkgTools/R/getData.R:75-80)
    Undefined global functions or variables:
      Author Description License Nb_of_downloads Package V<- any_alnums
      any_alphas any_blanks any_non_alnums any_of anything biocViews blank
      capture digit downloads_month downloads_total except_any_of maybe
      start tags
    Consider adding
      importFrom("stats", "start")
    to your NAMESPACE file.
    ```

# biomartr

Version: 0.8.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# blorr

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘descriptr’
      All declared Imports should be used.
    ```

# breathtestcore

Version: 0.4.5

## In both

*   checking Rd cross-references ... NOTE
    ```
    Package unavailable to check Rd xrefs: ‘breathteststan’
    ```

# cdcfluview

Version: 0.7.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘units’
      All declared Imports should be used.
    ```

# CDECRetrieve

Version: 0.1.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘lazyeval’ ‘purrr’ ‘roxygen2’
      All declared Imports should be used.
    ```

# celaref

Version: 1.0.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    Calculating likelihood ratio tests
    Refitting on reduced model...
    Calculating likelihood ratio tests
    Refitting on reduced model...
    
    Done!
    
    Done!
    Loading required package: AnnotationHub
    
    Attaching package: 'AnnotationHub'
    
    The following object is masked from 'package:Biobase':
    
        cache
    
    snapshotDate(): 2018-04-27
    Quitting from lines 909-921 (celaref_doco.Rmd) 
    Error: processing vignette 'celaref_doco.Rmd' failed with diagnostics:
    'celarefData' resources were not found in ExperimentHub
    Execution halted
    ```

*   checking for hidden files and directories ... NOTE
    ```
    Found the following hidden files and directories:
      .github
    These were most likely included in error. See section ‘Package
    structure’ in the ‘Writing R Extensions’ manual.
    ```

# chipenrich.data

Version: 2.6.0

## In both

*   checking package dependencies ... NOTE
    ```
    Packages suggested but not available for checking:
      ‘devtools’ ‘GO.db’ ‘org.Dm.eg.db’ ‘org.Dr.eg.db’ ‘org.Hs.eg.db’
      ‘org.Mm.eg.db’ ‘org.Rn.eg.db’ ‘TxDb.Dmelanogaster.UCSC.dm3.ensGene’
      ‘TxDb.Dmelanogaster.UCSC.dm6.ensGene’
      ‘TxDb.Drerio.UCSC.danRer10.refGene’
      ‘TxDb.Hsapiens.UCSC.hg19.knownGene’
      ‘TxDb.Hsapiens.UCSC.hg38.knownGene’
      ‘TxDb.Mmusculus.UCSC.mm9.knownGene’
      ‘TxDb.Mmusculus.UCSC.mm10.knownGene’
      ‘TxDb.Rnorvegicus.UCSC.rn4.ensGene’
      ‘TxDb.Rnorvegicus.UCSC.rn5.refGene’
      ‘TxDb.Rnorvegicus.UCSC.rn6.refGene’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 162.0Mb
      sub-directories of 1Mb or more:
        data  160.7Mb
    ```

# chromVAR

Version: 1.4.0

## In both

*   checking whether package ‘chromVAR’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘.../revdep/checks.noindex/chromVAR/new/chromVAR.Rcheck/00install.out’ for details.
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘BSgenome.Hsapiens.UCSC.hg19’
    ```

## Installation

### Devel

```
* installing *source* package ‘chromVAR’ ...
** libs
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/new/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c RcppExports.cpp -o RcppExports.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/new/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c pwm_similarity.cpp -o pwm_similarity.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/new/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c utils.cpp -o utils.o
clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/lib -o chromVAR.so RcppExports.o pwm_similarity.o utils.o -L/Library/Frameworks/R.framework/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Resources/lib -lRblas -L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin15/6.1.0 -L/usr/local/gfortran/lib -lgfortran -lquadmath -lm -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin15/6.1.0'
ld: warning: directory not found for option '-L/usr/local/gfortran/lib'
installing to .../revdep/checks.noindex/chromVAR/new/chromVAR.Rcheck/chromVAR/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
Error in loadNamespace(j <- i[[1L]], c(lib.loc, .libPaths()), versionCheck = vI[[j]]) : 
  there is no package called ‘GO.db’
ERROR: lazy loading failed for package ‘chromVAR’
* removing ‘.../revdep/checks.noindex/chromVAR/new/chromVAR.Rcheck/chromVAR’

```
### CRAN

```
* installing *source* package ‘chromVAR’ ...
** libs
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/old/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c RcppExports.cpp -o RcppExports.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/old/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c pwm_similarity.cpp -o pwm_similarity.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/old/Rcpp/include" -I".../revdep/library.noindex/chromVAR/RcppArmadillo/include" -I/usr/local/include   -fPIC  -Wall -g -O2 -c utils.cpp -o utils.o
clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/lib -o chromVAR.so RcppExports.o pwm_similarity.o utils.o -L/Library/Frameworks/R.framework/Resources/lib -lRlapack -L/Library/Frameworks/R.framework/Resources/lib -lRblas -L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin15/6.1.0 -L/usr/local/gfortran/lib -lgfortran -lquadmath -lm -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: directory not found for option '-L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin15/6.1.0'
ld: warning: directory not found for option '-L/usr/local/gfortran/lib'
installing to .../revdep/checks.noindex/chromVAR/old/chromVAR.Rcheck/chromVAR/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
Error in loadNamespace(j <- i[[1L]], c(lib.loc, .libPaths()), versionCheck = vI[[j]]) : 
  there is no package called ‘GO.db’
ERROR: lazy loading failed for package ‘chromVAR’
* removing ‘.../revdep/checks.noindex/chromVAR/old/chromVAR.Rcheck/chromVAR’

```
# CNEr

Version: 1.18.1

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘GO.db’
    
    Packages suggested but not available for checking:
      ‘BSgenome.Drerio.UCSC.danRer10’ ‘BSgenome.Hsapiens.UCSC.hg38’
      ‘TxDb.Drerio.UCSC.danRer10.refGene’ ‘BSgenome.Hsapiens.UCSC.hg19’
      ‘BSgenome.Ggallus.UCSC.galGal3’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# CNVScope

Version: 1.9.7

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘BSgenome.Hsapiens.UCSC.hg19’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# codemetar

Version: 0.1.6

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# codified

Version: 0.2.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘methods’ ‘readr’
      All declared Imports should be used.
    ```

# crosswalkr

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```

# crsra

Version: 0.2.3

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 500 marked UTF-8 strings
    ```

# curatedMetagenomicData

Version: 1.12.3

## In both

*   checking examples ... ERROR
    ```
    ...
    > ### Title: Data from the AsnicarF_2017 study
    > ### Aliases: AsnicarF_2017 AsnicarF_2017.genefamilies_relab.milk
    > ###   AsnicarF_2017.genefamilies_relab.stool
    > ###   AsnicarF_2017.marker_abundance.milk
    > ###   AsnicarF_2017.marker_abundance.stool
    > ###   AsnicarF_2017.marker_presence.milk
    > ###   AsnicarF_2017.marker_presence.stool
    > ###   AsnicarF_2017.metaphlan_bugs_list.milk
    > ###   AsnicarF_2017.metaphlan_bugs_list.stool
    > ###   AsnicarF_2017.pathabundance_relab.milk
    > ###   AsnicarF_2017.pathabundance_relab.stool
    > ###   AsnicarF_2017.pathcoverage.milk AsnicarF_2017.pathcoverage.stool
    > 
    > ### ** Examples
    > 
    > AsnicarF_2017.metaphlan_bugs_list.milk()
    snapshotDate(): 2018-04-27
    Error in AsnicarF_2017.metaphlan_bugs_list.milk() : 
      resource AsnicarF_2017.metaphlan_bugs_list.milk not found in ExperimentHub
    Try a different cmdversion, see cmdValidVersions() for possible values
    Execution halted
    ```

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
         })()
      6: stop(paste0("resource ", xx, " not found in ExperimentHub\n", "Try a different cmdversion, see", 
             " cmdValidVersions() for possible values")) at .../revdep/checks.noindex/curatedMetagenomicData/new/curatedMetagenomicData.Rcheck/00_pkg_src/curatedMetagenomicData/R/zzz.R:52
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 23 SKIPPED: 0 FAILED: 6
      1. Error: ExpressionSet2MRexperiment works (@test-ExpressionSet2MRexperiment.R#5) 
      2. Error: ExpressionSet2phyloseq returns phyloseq class object (@test-ExpressionSet2phyloseq.R#5) 
      3. Error: ExpressionSet2phyloseq works with phylogenetictree = TRUE (@test-ExpressionSet2phyloseq.R#14) 
      4. Error: ExpressionSet2phyloseq returns the same numerical data with simplify=TRUE/FALSE (@test-ExpressionSet2phyloseq.R#24) 
      5. Error: BritoIL_2016 and Castro-NallarE (@test-curatedMetagenomicData.R#58) 
      6. Error: countries and studies align. (@test-mergeData.R#27) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    snapshotDate(): 2018-04-27
    Quitting from lines 109-111 (curatedMetagenomicData.Rmd) 
    Error: processing vignette 'curatedMetagenomicData.Rmd' failed with diagnostics:
    resource LomanNJ_2013.metaphlan_bugs_list.stool not found in ExperimentHub
    Try a different cmdversion, see cmdValidVersions() for possible values
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  6.1Mb
      sub-directories of 1Mb or more:
        doc    1.5Mb
        help   2.7Mb
    ```

# datasus

Version: 0.4.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘RCurl’
      All declared Imports should be used.
    ```

# ddpcr

Version: 1.9

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Incompatible type for column `FAM`: x integer, y numeric
      
      ── 2. Failure: reading v174 works (@test-v174.R#7)  ────────────────────────────
      `expected_data` not equal to plate_data(plate).
      Incompatible type for column `HEX`: x numeric, y integer
      Incompatible type for column `FAM`: x numeric, y integer
      Incompatible type for column `cluster`: x numeric, y integer
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 267 SKIPPED: 0 FAILED: 2
      1. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) 
      2. Failure: reading v174 works (@test-v174.R#7) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.2Mb
      sub-directories of 1Mb or more:
        sample_data   3.0Mb
    ```

# DEP

Version: 1.4.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.0Mb
      sub-directories of 1Mb or more:
        R      1.2Mb
        data   1.4Mb
        doc    3.1Mb
    ```

# DESeq2

Version: 1.22.1

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
          aperm, apply
      
      > test_check("DESeq2")
      ── 1. Error: tximeta works (@test_txi.R#37)  ───────────────────────────────────
      there is no package called 'tximeta'
      1: library(tximeta) at testthat/test_txi.R:37
      2: stop(txt, domain = NA)
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 240 SKIPPED: 0 FAILED: 1
      1. Error: tximeta works (@test_txi.R#37) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.5Mb
      sub-directories of 1Mb or more:
        R     2.0Mb
        doc   2.4Mb
    ```

# DiagrammeR

Version: 1.0.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.9Mb
      sub-directories of 1Mb or more:
        R             3.0Mb
        htmlwidgets   3.0Mb
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 1 marked UTF-8 string
    ```

# diffloop

Version: 1.10.0

## In both

*   checking for hidden files and directories ... NOTE
    ```
    Found the following hidden files and directories:
      .travis.yml
    These were most likely included in error. See section ‘Package
    structure’ in the ‘Writing R Extensions’ manual.
    ```

# duawranglr

Version: 0.6.3

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘digest’ ‘dplyr’
      All declared Imports should be used.
    ```

# dwapi

Version: 0.1.3.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘xml2’
      All declared Imports should be used.
    ```

# dynutils

Version: 1.0.0

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# edgeR

Version: 3.24.0

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘edgeR-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: nearestTSS
    > ### Title: Find Nearest Transcriptional Start Site
    > ### Aliases: nearestTSS
    > 
    > ### ** Examples
    > 
    > nearestTSS(chr = c("1","1"), locus = c(1000000,2000000))
    Error in nearestTSS(chr = c("1", "1"), locus = c(1e+06, 2e+06)) : 
      org.Hs.eg.db package required but not not installed (or can't be loaded)
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘org.Hs.eg.db’
    ```

*   checking sizes of PDF files under ‘inst/doc’ ... NOTE
    ```
      ‘qpdf’ made some significant size reductions:
         compacted ‘edgeRUsersGuide.pdf’ from 1.4Mb to 1.3Mb
      consider running tools::compactPDF() on these files
    ```

# EdSurvey

Version: 2.2.2

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.8Mb
      sub-directories of 1Mb or more:
        R   4.1Mb
    ```

# eechidna

Version: 1.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.6Mb
      sub-directories of 1Mb or more:
        data   5.1Mb
        doc    1.2Mb
    ```

# ELMER

Version: 2.6.0

## In both

*   R CMD check timed out
    

*   checking dependencies in R code ... WARNING
    ```
    '::' or ':::' import not declared from: 'progress'
    Unexported objects imported by ':::' calls:
      'TCGAbiolinks:::colDataPrepare' 'TCGAbiolinks:::get.GRCh.bioMart'
      See the note in ?`:::` about the use of this operator.
    ```

*   checking for code/documentation mismatches ... WARNING
    ```
    Codoc mismatches from documentation object 'get.enriched.motif':
    get.enriched.motif
      Code: function(data, probes.motif, probes, min.motif.quality = "DS",
                     background.probes, pvalue = 0.05, lower.OR = 1.1,
                     min.incidence = 10, dir.out = "./", label = NULL, save
                     = TRUE, plot.title = "")
      Docs: function(data, probes.motif, probes, min.motif.quality = "DS",
                     background.probes, pvalue = 0.05, lower.OR = 1.1,
                     min.incidence = 10, dir.out = "./", label = NULL, save
                     = TRUE, plot.title = NULL)
      Mismatches in argument default values:
        Name: 'plot.title' Code: "" Docs: NULL
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 44.7Mb
      sub-directories of 1Mb or more:
        doc  43.6Mb
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/motif.TF.Plots.R:123-135)
    motif.enrichment.plot: no visible binding for global variable 'upperOR'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/motif.TF.Plots.R:147)
    motif.enrichment.plot: no visible binding for global variable 'lowerOR'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/motif.TF.Plots.R:147)
    motif.enrichment.plot: no visible binding for global variable 'motif'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/motif.TF.Plots.R:148-157)
    motif.enrichment.plot: no visible binding for global variable 'OR'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/motif.TF.Plots.R:148-157)
    scatter: no visible binding for global variable 'value'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/Scatter.plot.R:236-250)
    scatter: no visible binding for global variable 'mae'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/Scatter.plot.R:272-289)
    scatter.plot: no visible binding for global variable 'ID'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/Scatter.plot.R:135)
    scatter.plot: no visible binding for global variable 'GeneID'
      (.../revdep/checks.noindex/ELMER/new/ELMER.Rcheck/00_pkg_src/ELMER/R/Scatter.plot.R:135)
    Undefined global functions or variables:
      DistanceTSS Gene GeneID Hugo_Symbol ID OR Probe Side Sides TF
      ensembl_gene_id label lowerOR mae motif pvalue subsetByOverlaps
      upperOR value x y z
    ```

# emuR

Version: 1.1.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  7.1Mb
      sub-directories of 1Mb or more:
        R         3.1Mb
        doc       1.2Mb
        extdata   1.5Mb
    ```

# epicontacts

Version: 1.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘colorspace’
      All declared Imports should be used.
    ```

# epitable

Version: 0.1.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘magrittr’ ‘readr’
      All declared Imports should be used.
    ```

# esc

Version: 0.4.1

## In both

*   checking Rd cross-references ... NOTE
    ```
    Package unavailable to check Rd xrefs: ‘metafor’
    ```

# etl

Version: 0.3.7

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# eurostat

Version: 3.2.9

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
        filter, lag
    
    The following objects are masked from 'package:base':
    
        intersect, setdiff, setequal, union
    
    trying URL 'https://ec.europa.eu/eurostat/estat-navtree-portlet-prod/BulkDownloadListing?sort=1&file=data%2Ften00081.tsv.gz'
    Content type 'application/octet-stream;charset=UTF-8' length 13630 bytes (13 KB)
    ==================================================
    downloaded 13 KB
    
    Table ten00081 cached at /var/folders/dt/r5s12t392tb5sk181j3gs4zw0000gn/T//RtmpWqdzl5/eurostat/ten00081_date_code_TF.rds
    trying URL 'https://ec.europa.eu/eurostat/estat-navtree-portlet-prod/BulkDownloadListing?sort=1&file=data%2Ftgs00026.tsv.gz'
    Content type 'application/octet-stream;charset=UTF-8' length 5998 bytes
    ==================================================
    downloaded 5998 bytes
    
    Quitting from lines 291-308 (eurostat_tutorial.Rmd) 
    Error: processing vignette 'eurostat_tutorial.Rmd' failed with diagnostics:
    Open failed.
    Execution halted
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 596 marked UTF-8 strings
    ```

# EventStudy

Version: 0.34

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.9Mb
      sub-directories of 1Mb or more:
        doc   5.8Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘curl’ ‘openxlsx’ ‘stringr’
      All declared Imports should be used.
    ```

# fastqcr

Version: 0.1.0

## Newly broken

*   checking examples ... ERROR
    ```
    ...
    > 
    > ### ** Examples
    > 
    > # Demo QC dir
    > qc.dir <- system.file("fastqc_results", package = "fastqcr")
    > qc.dir
    [1] ".../revdep/checks.noindex/fastqcr/new/fastqcr.Rcheck/fastqcr/fastqc_results"
    > 
    > # List of files in the directory
    > list.files(qc.dir)
    [1] "S1_fastqc.zip" "S2_fastqc.zip" "S3_fastqc.zip" "S4_fastqc.zip"
    [5] "S5_fastqc.zip"
    > 
    > # Aggregate the report
    > qc <- qc_aggregate(qc.dir, progressbar = FALSE)
    Warning in function_list[[i]](value) : NAs introduced by coercion
    Warning in function_list[[i]](value) : NAs introduced by coercion
    Error in match.names(clabs, names(xi)) : 
      names do not match previous names
    Calls: qc_aggregate -> rbind -> rbind -> match.names
    Execution halted
    ```

# fastR2

Version: 1.2.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.0Mb
      sub-directories of 1Mb or more:
        snippet   3.7Mb
    ```

# febr

Version: 1.0.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘knitr’
      All declared Imports should be used.
    ```

# FedData

Version: 2.5.5

## In both

*   checking package dependencies ... ERROR
    ```
    Packages required but not available: ‘devtools’ ‘soilDB’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# fingertipsR

Version: 0.2.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘purrr’
      All declared Imports should be used.
    ```

# genomation

Version: 1.14.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  7.4Mb
      sub-directories of 1Mb or more:
        R         2.0Mb
        doc       3.5Mb
        extdata   1.2Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘RUnit’
      All declared Imports should be used.
    Unexported object imported by a ':::' call: ‘BiocGenerics:::testPackage’
      See the note in ?`:::` about the use of this operator.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ScoreMatrixBin,RleList-GRangesList: no visible binding for global
      variable ‘id’
      (.../revdep/checks.noindex/genomation/new/genomation.Rcheck/00_pkg_src/genomation/R/scoreMatrixBin.R:336)
    ScoreMatrixBin,RleList-GRangesList: no visible global function
      definition for ‘:=’
      (.../revdep/checks.noindex/genomation/new/genomation.Rcheck/00_pkg_src/genomation/R/scoreMatrixBin.R:343)
    ScoreMatrixBin,RleList-GRangesList: no visible binding for global
      variable ‘id’
      (.../revdep/checks.noindex/genomation/new/genomation.Rcheck/00_pkg_src/genomation/R/scoreMatrixBin.R:343)
    ScoreMatrixBin,RleList-GRangesList: no visible binding for global
      variable ‘id’
      (.../revdep/checks.noindex/genomation/new/genomation.Rcheck/00_pkg_src/genomation/R/scoreMatrixBin.R:347)
    Undefined global functions or variables:
      := id
    ```

*   checking files in ‘vignettes’ ... NOTE
    ```
    The following directory looks like a leftover from 'knitr':
      ‘cache’
    Please remove from your package.
    ```

# genomes

Version: 3.12.0

## In both

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Malformed Description field: should contain one or more complete sentences.
    ```

# GenomicDataCommons

Version: 1.6.0

## In both

*   checking Rd \usage sections ... WARNING
    ```
    Undocumented arguments in documentation object '.htseq_importer'
      ‘fnames’
    
    Functions with \usage entries need to have the appropriate \alias
    entries, and all their arguments documented.
    The \usage entries must correspond to syntactically valid R code.
    See chapter ‘Writing R documentation files’ in the ‘Writing R
    Extensions’ manual.
    ```

*   checking R code for possible problems ... NOTE
    ```
    default_fields.character: no visible binding for global variable
      ‘defaults’
      (.../revdep/checks.noindex/GenomicDataCommons/new/GenomicDataCommons.Rcheck/00_pkg_src/GenomicDataCommons/R/fields.R:51)
    gdc_rnaseq: no visible binding for global variable ‘case_id’
      (.../revdep/checks.noindex/GenomicDataCommons/new/GenomicDataCommons.Rcheck/00_pkg_src/GenomicDataCommons/R/gdc_rnaseq.R:106-107)
    gdc_rnaseq: no visible binding for global variable ‘file_id’
      (.../revdep/checks.noindex/GenomicDataCommons/new/GenomicDataCommons.Rcheck/00_pkg_src/GenomicDataCommons/R/gdc_rnaseq.R:106-107)
    Undefined global functions or variables:
      case_id defaults file_id
    ```

# geojsonio

Version: 0.6.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.4Mb
      sub-directories of 1Mb or more:
        doc        1.4Mb
        examples   1.6Mb
        vign       1.0Mb
    ```

# GEOquery

Version: 2.50.0

## Newly broken

*   checking examples ... ERROR
    ```
    ...
    
    > ### Name: getGSEDataTables
    > ### Title: Get GSE data tables from GEO into R data structures.
    > ### Aliases: getGSEDataTables
    > ### Keywords: IO
    > 
    > ### ** Examples
    > 
    > 
    > dfl = getGSEDataTables("GSE3494")
    Called from: FUN(X[[i]], ...)
    Browse[1]> lapply(dfl,head)
    Error in lapply(dfl, head) : object 'dfl' not found
    Calls: getGSEDataTables -> sapply -> lapply -> FUN -> lapply
    Browse[1]> 
    debug at .../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/getGSEDataTables.R#37: dTable = suppressWarnings(read_tsv(dTableText, col_names = FALSE))
    Browse[2]> 
    Error in read_tokens_(data, tokenizer, col_specs, col_names, locale_,  : 
      attempt to set index 1000/7 in SET_STRING_ELT
    Calls: getGSEDataTables -> sapply -> lapply -> FUN
    Execution halted
    ```

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      trying URL 'https://ftp.ncbi.nlm.nih.gov/geo/samples/GSM15nnn/GSM15789/suppl//GSM15789.cel.gz?tool=geoquery'
      Content type 'application/x-gzip' length 3507725 bytes (3.3 MB)
      ==================================================
      downloaded 3.3 MB
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 183 SKIPPED: 0 FAILED: 5
      1. Error: empty GSE is handled correctly (@test_GSE.R#6) 
      2. Failure: case-mismatched IDs in GSEs handled correctly (@test_GSE.R#17) 
      3. Failure: short GSE handled correctly (@test_GSE.R#30) 
      4. Failure: GSE with more than one value per characteristic handled (@test_GSE.R#49) 
      5. Failure: GSE without GPL works (@test_fetch_GPL_false.R#9) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

## In both

*   checking installed package size ... NOTE
    ```
      installed size is 13.9Mb
      sub-directories of 1Mb or more:
        extdata  12.8Mb
    ```

*   checking whether the namespace can be loaded with stated dependencies ... NOTE
    ```
    Warning: no function found corresponding to methods exports from ‘GEOquery’ for: ‘show’
    
    A namespace must be able to be loaded with just the base namespace
    loaded: otherwise if the namespace gets loaded by a saved object, the
    session will be unable to start.
    
    Probably some imports need to be declared in the NAMESPACE file.
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘httr’
      All declared Imports should be used.
    Package in Depends field not imported from: ‘methods’
      These packages need to be imported from (in the NAMESPACE file)
      for when this namespace is loaded but not attached.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:531-539)
    parseGSEMatrix: no visible binding for global variable ‘accession’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:531-539)
    parseGSEMatrix: no visible binding for global variable ‘accession’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:541-542)
    parseGSEMatrix: no visible global function definition for ‘new’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:568)
    parseGSEMatrix: no visible global function definition for ‘new’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:590)
    parseGSEMatrix: no visible global function definition for ‘new’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:606-610)
    parseGSEMatrix: no visible global function definition for ‘as’
      (.../revdep/checks.noindex/GEOquery/new/GEOquery.Rcheck/00_pkg_src/GEOquery/R/parseGEO.R:606-610)
    Undefined global functions or variables:
      . MA accession as characteristics k kvpair new read.delim read.table
      v
    Consider adding
      importFrom("methods", "as", "new")
      importFrom("utils", "read.delim", "read.table")
    to your NAMESPACE file (and ensure that your DESCRIPTION Imports field
    contains 'methods').
    ```

# GetITRData

Version: 0.7

## Newly broken

*   R CMD check timed out
    

# ggCompNet

Version: 0.1.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    
    Attaching package: 'dplyr'
    
    The following objects are masked from 'package:stats':
    
        filter, lag
    
    The following objects are masked from 'package:base':
    
        intersect, setdiff, setequal, union
    
    Warning: Removed 8 rows containing missing values (geom_segment).
    Quitting from lines 610-612 (examples-from-paper.Rmd) 
    Error: processing vignette 'examples-from-paper.Rmd' failed with diagnostics:
    cannot open URL 'http://maps.googleapis.com/maps/api/staticmap?center=39.09984,-77.16764&zoom=13&size=640x640&scale=2&maptype=terrain&language=en-EN&sensor=false'
    Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  6.4Mb
      sub-directories of 1Mb or more:
        doc   6.1Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘dplyr’ ‘ggmap’ ‘gridExtra’ ‘scales’ ‘tnet’
      All declared Imports should be used.
    ```

# ggguitar

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘gridExtra’ ‘lazyeval’ ‘readr’
      All declared Imports should be used.
    ```

# ggstatsplot

Version: 0.0.6

## In both

*   R CMD check timed out
    

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.5Mb
      sub-directories of 1Mb or more:
        doc    2.6Mb
        help   2.3Mb
    ```

# glmSparseNet

Version: 1.0.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    
    Attaching package: 'dplyr'
    
    The following objects are masked from 'package:stats':
    
        filter, lag
    
    The following objects are masked from 'package:base':
    
        intersect, setdiff, setequal, union
    
    Quitting from lines 28-43 (example_brca_logistic.Rmd) 
    Error: processing vignette 'example_brca_logistic.Rmd' failed with diagnostics:
    there is no package called 'curatedTCGAData'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘curatedTCGAData’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  6.0Mb
      sub-directories of 1Mb or more:
        doc   5.2Mb
    ```

# googlesheets

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘tibble’
      All declared Imports should be used.
    ```

# gutenbergr

Version: 0.1.4

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 13617 marked UTF-8 strings
    ```

# haven

Version: 1.1.2

## In both

*   checking for GNU extensions in Makefiles ... NOTE
    ```
    GNU make is a SystemRequirements.
    ```

# HMP16SData

Version: 1.2.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    Attaching package: 'dendextend'
    
    The following object is masked from 'package:stats':
    
        cutree
    
    ========================================
    circlize version 0.4.4
    CRAN page: https://cran.r-project.org/package=circlize
    Github page: https://github.com/jokergoo/circlize
    Documentation: http://jokergoo.github.io/circlize_book/book/
    
    If you use it in published research, please cite:
    Gu, Z. circlize implements and enhances circular visualization 
      in R. Bioinformatics 2014.
    ========================================
    
    Quitting from lines 58-71 (HMP16SData.Rmd) 
    Error: processing vignette 'HMP16SData.Rmd' failed with diagnostics:
    there is no package called 'curatedMetagenomicData'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Packages suggested but not available for checking:
      ‘curatedMetagenomicData’ ‘devtools’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 19.1Mb
      sub-directories of 1Mb or more:
        doc       1.5Mb
        extdata  17.4Mb
    ```

# HPAanalyze

Version: 1.0.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      ‘quantity’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/xml.R:225-227)
    hpaXmlTissueExpr : <anonymous>: no visible binding for global variable
      ‘imageUrl’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/xml.R:225-227)
    hpaXmlTissueExprSum: no visible binding for global variable ‘tissue’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/xml.R:124-131)
    hpaXmlTissueExprSum: no visible binding for global variable ‘imageUrl’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/xml.R:124-131)
    named_vector_list_to_tibble: no visible binding for global variable
      ‘index’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/utils.R:17-23)
    named_vector_list_to_tibble: no visible binding for global variable
      ‘value’
      (.../revdep/checks.noindex/HPAanalyze/new/HPAanalyze.Rcheck/00_pkg_src/HPAanalyze/R/utils.R:17-23)
    Undefined global functions or variables:
      Count.patients Level Total.patients age cancer cell_line cell_type
      gene go_id high hpaCancer hpaNormalTissue hpaSubcellularLoc imageUrl
      index intensity level low medium not_detected patientId patient_count
      quantity rnaGeneCellLine rnaGeneTissue sex staining sub_location
      tissue tissue_cell value
    ```

# HURDAT

Version: 0.2.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# hydroscoper

Version: 1.1.1

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 3031 marked UTF-8 strings
    ```

# IalsaSynthesis

Version: 0.1.6

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# ipumsr

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘R6’
      All declared Imports should be used.
    ```

# IsoformSwitchAnalyzeR

Version: 1.4.0

## In both

*   checking examples ... ERROR
    ```
    ...
    > ### Prepare for orf analysis
    > # Load example data and prefilter
    > data("exampleSwitchList")
    > exampleSwitchList <- preFilter(exampleSwitchList)
    The fitering removed 52 ( 20.08% of ) transcripts. There is now 207 isoforms left
    > 
    > # Perfom test
    > exampleSwitchListAnalyzed <- isoformSwitchTestDEXSeq(exampleSwitchList, dIFcutoff = 0.3) # high dIF cutoff for fast runtime
    Step 1 of 3: Calculating isoform abundances (from counts)...
    Step 2 of 3: Calculating Isoform Fraction matrix...
    Step 3 of 3: Testing each pariwise comparisons with DEXSeq (this might be a bit slow)...
        Estimated time (for dataset with ~30.000 isoforms): 2 min
    Step 4 of 3: Integrating result into switchAnalyzeRlist...
        Isoform switch analysis was performed for 62 gene comparisons (100%).
    Done
    > 
    > ### analyzeORF
    > library(BSgenome.Hsapiens.UCSC.hg19)
    Error in library(BSgenome.Hsapiens.UCSC.hg19) : 
      there is no package called ‘BSgenome.Hsapiens.UCSC.hg19’
    Execution halted
    ```

*   checking whether package ‘IsoformSwitchAnalyzeR’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: replacing previous import ‘DEXSeq::plotMA’ by ‘limma::plotMA’ when loading ‘IsoformSwitchAnalyzeR’
    See ‘.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00install.out’ for details.
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    Loading required package: DESeq2
    Loading required package: AnnotationDbi
    Loading required package: RColorBrewer
    Loading required package: ggplot2
    Warning: replacing previous import 'DEXSeq::plotMA' by 'limma::plotMA' when loading 'IsoformSwitchAnalyzeR'
    Step 1 of 6: Checking data...
    Step 2 of 6: Obtaining annotation...
        importing GTF (this may take a while)
    Warning in importRdata(isoformCountMatrix = salmonQuant$counts, isoformRepExpression = salmonQuant$abundance,  :
         No CDS annotation was found in the GTF files meaning ORFs could not be annotated.
         (But ORFs can still be predicted with the analyzeORF() function)
    Step 3 of 6: Calculating gene expression and isoform fraction...
         111 ( 9.23%) isoforms were removed since they were not expressed in any samples.
    Step 4 of 6: Merging gene and isoform expression...
    Step 5 of 6: Making comparisons...
    Step 6 of 6: Making switchAnalyzeRlist object...
    Done
    Quitting from lines 399-416 (IsoformSwitchAnalyzeR.Rmd) 
    Error: processing vignette 'IsoformSwitchAnalyzeR.Rmd' failed with diagnostics:
    there is no package called 'BSgenome.Hsapiens.UCSC.hg19'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘BSgenome.Hsapiens.UCSC.hg19’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  7.9Mb
      sub-directories of 1Mb or more:
        R     3.0Mb
        doc   3.5Mb
    ```

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Package listed in more than one of Depends, Imports, Suggests, Enhances:
      ‘limma’
    A package should be listed in only one of these fields.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1058-1068)
    switchPlotTranscript: no visible binding for global variable ‘x’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1058-1068)
    switchPlotTranscript: no visible binding for global variable ‘ymin’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1071-1087)
    switchPlotTranscript: no visible binding for global variable ‘xmin’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1071-1087)
    switchPlotTranscript: no visible binding for global variable ‘ymax’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1071-1087)
    switchPlotTranscript: no visible binding for global variable ‘xmax’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1071-1087)
    switchPlotTranscript: no visible binding for global variable ‘Domain’
      (.../revdep/checks.noindex/IsoformSwitchAnalyzeR/new/IsoformSwitchAnalyzeR.Rcheck/00_pkg_src/IsoformSwitchAnalyzeR/R/isoform_plots.R:1071-1087)
    Undefined global functions or variables:
      AStype CI_down CI_hi CI_low CI_up Comparison Condition Domain IF
      Significant feature2 geneFraction gene_expression gene_id idNr
      isoFraction isoform_feature isoform_id nrGenesWithConsequences
      nrIsoWithConsequences propCiHi propCiLo propOfRelevantEvents propUp
      propUpCiHi propUpCiLo queryHits sigEval sigLevel sigLevelPos
      significance splicingResult switchConsequence value variable x xmax
      xmin y yend ymax ymin
    ```

*   checking for unstated dependencies in vignettes ... NOTE
    ```
    'library' or 'require' call not declared from: ‘pheatmap’
    ```

# isomiRs

Version: 1.10.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘org.Mm.eg.db’
    ```

*   checking for hidden files and directories ... NOTE
    ```
    Found the following hidden files and directories:
      .travis.yml
    These were most likely included in error. See section ‘Package
    structure’ in the ‘Writing R Extensions’ manual.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:535)
    mirna2targetscan: no visible binding for global variable
      ‘targetscan.Hs.egTARGETSFULL’
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:536)
    mirna2targetscan: no visible binding for global variable
      ‘targetscan.Mm.egMIRNA’
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:538)
    mirna2targetscan: no visible binding for global variable
      ‘targetscan.Mm.egMIRBASE2FAMILY’
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:539)
    mirna2targetscan: no visible binding for global variable
      ‘targetscan.Mm.egTARGETS’
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:540)
    mirna2targetscan: no visible binding for global variable
      ‘targetscan.Mm.egTARGETSFULL’
      (.../revdep/checks.noindex/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/targets.R:541)
    Undefined global functions or variables:
      iso_sample targetscan.Hs.egMIRBASE2FAMILY targetscan.Hs.egMIRNA
      targetscan.Hs.egTARGETS targetscan.Hs.egTARGETSFULL
      targetscan.Mm.egMIRBASE2FAMILY targetscan.Mm.egMIRNA
      targetscan.Mm.egTARGETS targetscan.Mm.egTARGETSFULL
    ```

# jstor

Version: 0.3.4

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > library(testthat)
      > library(jstor)
      > 
      > test_check("jstor")
      ── 1. Failure: writing error messages to file works (@test-writing-to-file.R#77)
      `res` not identical to `correct_res`.
      Incompatible type for column `id`: x numeric, y integer
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 249 SKIPPED: 4 FAILED: 1
      1. Failure: writing error messages to file works (@test-writing-to-file.R#77) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# kokudosuuchi

Version: 0.4.2

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 52458 marked UTF-8 strings
    ```

# MetaIntegrator

Version: 2.0.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.4Mb
      sub-directories of 1Mb or more:
        R      1.0Mb
        data   1.9Mb
        doc    2.2Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘DT’ ‘GEOmetadb’ ‘RMySQL’ ‘RSQLite’ ‘gplots’ ‘pheatmap’ ‘readr’
      All declared Imports should be used.
    ```

# microsamplingDesign

Version: 1.0.5

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# mosaic

Version: 1.4.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package which this enhances but not available for checking: ‘manipulate’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  6.6Mb
      sub-directories of 1Mb or more:
        R     4.3Mb
        doc   1.9Mb
    ```

*   checking Rd cross-references ... NOTE
    ```
    Package unavailable to check Rd xrefs: ‘cubature’
    ```

# mudata2

Version: 1.0.3

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/test-all.R’ failed.
    Last 13 lines of output:
      
      OGR: Unsupported geometry type
      OGR: Unsupported geometry type
      OGR: Unsupported geometry type
      OGR: Unsupported geometry type
      OGR: Unsupported geometry type
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 805 SKIPPED: 0 FAILED: 4
      1. Error: read/write JSON functions work (@test_mudata.io.R#180) 
      2. Error: mudata_prepare_column and mudata_parse_column are opposites (@test_mudata.io.R#267) 
      3. Error: mudata_prepare_tbl and mudata_parse_tbl are opposites (@test_mudata.io.R#344) 
      4. Error: read/write mudatas containing datetime objects works (@test_mudata.io.R#431) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# myTAI

Version: 0.8.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.6Mb
      sub-directories of 1Mb or more:
        data   2.0Mb
        doc    2.4Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘biomartr’
      All declared Imports should be used.
    ```

# ncappc

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘bookdown’
      All declared Imports should be used.
    ```

# oec

Version: 2.7.8

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘readr’
      All declared Imports should be used.
    ```

# opensensmapr

Version: 0.5.0

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
             test_error <<- e
         }, "object 'boxes' not found", quote(eval(code, test_env))) at testthat/test_phenomena.R:30
      2: eval(code, test_env)
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 10 SKIPPED: 35 FAILED: 6
      1. Error: osem_box_to_archive_name works for one box (@test_archive.R#23) 
      2. Error: osem_box_to_archive_name works for multiple boxes (@test_archive.R#29) 
      3. Error: osem_measurements_archive works for one box (@test_archive.R#41) 
      4. Error: osem_measurements_archive fails for multiple boxes (@test_archive.R#47) 
      5. Error: summary.sensebox outputs all metrics for a single box (@test_box.R#42) 
      6. Error: phenomena from a not sensebox data.frame returns error (@test_phenomena.R#30) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    
        intersect, setdiff, setequal, union
    
    
    Attaching package: 'lubridate'
    
    The following object is masked from 'package:base':
    
        date
    
    
    Attaching package: 'zoo'
    
    The following objects are masked from 'package:base':
    
        as.Date, as.Date.numeric
    
    Quitting from lines 44-47 (osem-history.Rmd) 
    Error: processing vignette 'osem-history.Rmd' failed with diagnostics:
    $ operator is invalid for atomic vectors
    Execution halted
    ```

# openwindfarm

Version: 0.1.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Quitting from lines 34-37 (openwindfarm-vignette.Rmd) 
    Error: processing vignette 'openwindfarm-vignette.Rmd' failed with diagnostics:
    task 1 failed - "Not Found (HTTP 404)."
    Execution halted
    ```

# paxtoolsr

Version: 1.16.0

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘paxtoolsr-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: convertIds
    > ### Title: Covert IDs Using org.Hs.eg.db
    > ### Aliases: convertIds
    > 
    > ### ** Examples
    > 
    > convertIds("TP53", "SYMBOL", "ENTREZID")
    Loading required package: org.Hs.eg.db
    Warning in library(package, lib.loc = lib.loc, character.only = TRUE, logical.return = TRUE,  :
      there is no package called ‘org.Hs.eg.db’
    Error in convertIds("TP53", "SYMBOL", "ENTREZID") : 
      This function requires org.Hs.eg.db.
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘org.Hs.eg.db’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 33.7Mb
      sub-directories of 1Mb or more:
        doc       1.8Mb
        extdata   6.8Mb
        java     24.5Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    'library' or 'require' call to ‘org.Hs.eg.db’ in package code.
      Please use :: or requireNamespace() instead.
      See section 'Suggested packages' in the 'Writing R Extensions' manual.
    ```

*   checking R code for possible problems ... NOTE
    ```
    convertIds: no visible global function definition for ‘select’
      (.../revdep/checks.noindex/paxtoolsr/new/paxtoolsr.Rcheck/00_pkg_src/paxtoolsr/R/convertIds.R:19)
    convertIds: no visible binding for global variable ‘org.Hs.eg.db’
      (.../revdep/checks.noindex/paxtoolsr/new/paxtoolsr.Rcheck/00_pkg_src/paxtoolsr/R/convertIds.R:19)
    splitSifnxByPathway: no visible global function definition for
      ‘%dopar%’
      (.../revdep/checks.noindex/paxtoolsr/new/paxtoolsr.Rcheck/00_pkg_src/paxtoolsr/R/splitSifnxByPathway.R:34-40)
    Undefined global functions or variables:
      %dopar% org.Hs.eg.db select
    ```

# pcr

Version: 1.1.2

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# photobiologyInOut

Version: 0.4.17-1

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
      Read 5 items
      Read 8 items
      Read 8 items
      Read 5 items
      Read 8 items
      Read 8 items
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 433 SKIPPED: 4 FAILED: 3
      1. Failure: read Quick TUV (@test-tuv.R#18) 
      2. Failure: read Quick TUV (@test-tuv.R#20) 
      3. Failure: read Quick TUV (@test-tuv.R#21) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# PkgsFromFiles

Version: 0.5

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘PkgsFromFiles-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: pff_check_install_pkgs
    > ### Title: Checks and installs a single package
    > ### Aliases: pff_check_install_pkgs
    > 
    > ### ** Examples
    > 
    > pff_check_install_pkgs('dplyr')
    
    Installing dplyrError in pkg.in %in% my.available.packages : 
      argument "my.available.packages" is missing, with no default
    Calls: pff_check_install_pkgs -> %in%
    Execution halted
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘XML’ ‘curl’ ‘readr’ ‘stringdist’
      All declared Imports should be used.
    ```

# PKPDmisc

Version: 2.1.1

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘purrr’
      All declared Imports should be used.
    ```

# plotGrouper

Version: 1.0.0

## In both

*   checking R code for possible problems ... NOTE
    ```
    gplot: no visible binding for global variable ‘max_value’
      (.../revdep/checks.noindex/plotGrouper/new/plotGrouper.Rcheck/00_pkg_src/plotGrouper/R/gplot.R:360-395)
    gplot: no visible binding for global variable ‘max_error’
      (.../revdep/checks.noindex/plotGrouper/new/plotGrouper.Rcheck/00_pkg_src/plotGrouper/R/gplot.R:360-395)
    Undefined global functions or variables:
      max_error max_value
    ```

# postal

Version: 0.1.0

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Complete output:
      > library(testthat)
      > library(postal)
      > 
      > test_check("postal")
      ── 1. Failure: Extract date works (@test_utils.R#244)  ─────────────────────────
      extract_dates(future_date) %>% as.numeric() is not strictly more than lubridate::today() %>% as.numeric(). Difference: 0
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 109 SKIPPED: 0 FAILED: 1
      1. Failure: Extract date works (@test_utils.R#244) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# prozor

Version: 0.2.11

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.7Mb
      sub-directories of 1Mb or more:
        data      1.7Mb
        extdata   2.3Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘dplyr’ ‘readr’
      All declared Imports should be used.
    ```

# radiant.data

Version: 0.9.7

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘shinyFiles’
      All declared Imports should be used.
    ```

# ratematrix

Version: 1.1

## In both

*   checking whether package ‘ratematrix’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘.../revdep/checks.noindex/ratematrix/new/ratematrix.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘ratematrix’ ...
** package ‘ratematrix’ successfully unpacked and MD5 sums checked
** libs
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/new/Rcpp/include" -I".../revdep/library.noindex/ratematrix/RcppArmadillo/include" -I/usr/local/include  -fopenmp  -fPIC  -Wall -g -O2 -c MultRegimeMCMC.cpp -o MultRegimeMCMC.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/new/Rcpp/include" -I".../revdep/library.noindex/ratematrix/RcppArmadillo/include" -I/usr/local/include  -fopenmp  -fPIC  -Wall -g -O2 -c RcppExports.cpp -o RcppExports.o
clang: error: unsupported option '-fopenmp'
make: *** [RcppExports.o] Error 1
make: *** Waiting for unfinished jobs....
clang: error: unsupported option '-fopenmp'
make: *** [MultRegimeMCMC.o] Error 1
ERROR: compilation failed for package ‘ratematrix’
* removing ‘.../revdep/checks.noindex/ratematrix/new/ratematrix.Rcheck/ratematrix’

```
### CRAN

```
* installing *source* package ‘ratematrix’ ...
** package ‘ratematrix’ successfully unpacked and MD5 sums checked
** libs
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/old/Rcpp/include" -I".../revdep/library.noindex/ratematrix/RcppArmadillo/include" -I/usr/local/include  -fopenmp  -fPIC  -Wall -g -O2 -c MultRegimeMCMC.cpp -o MultRegimeMCMC.o
clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG  -I".../revdep/library.noindex/readr/old/Rcpp/include" -I".../revdep/library.noindex/ratematrix/RcppArmadillo/include" -I/usr/local/include  -fopenmp  -fPIC  -Wall -g -O2 -c RcppExports.cpp -o RcppExports.o
clang: error: unsupported option '-fopenmp'
clang: error: unsupported option '-fopenmp'
make: *** [MultRegimeMCMC.o] Error 1
make: *** Waiting for unfinished jobs....
make: *** [RcppExports.o] Error 1
ERROR: compilation failed for package ‘ratematrix’
* removing ‘.../revdep/checks.noindex/ratematrix/old/ratematrix.Rcheck/ratematrix’

```
# rclimateca

Version: 1.0.2

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 24 marked UTF-8 strings
    ```

# RcppEigenAD

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘RcppEigen’
      All declared Imports should be used.
    ```

# rcv

Version: 0.2.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.2Mb
      sub-directories of 1Mb or more:
        data   5.0Mb
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 6543 marked UTF-8 strings
    ```

# rdflib

Version: 0.2.0

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > 
      > test_check("rdflib")
      ── 1. Failure: SPARQL handles data types (@test-rdf_query.R#74)  ───────────────
      match$o[[1]] inherits from `numeric` not `integer`.
      
      ── 2. Failure: SPARQL handles data types (@test-rdf_query.R#75)  ───────────────
      match$o[[1]] has type `double`, not `integer`.
      
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 53 SKIPPED: 6 FAILED: 2
      1. Failure: SPARQL handles data types (@test-rdf_query.R#74) 
      2. Failure: SPARQL handles data types (@test-rdf_query.R#75) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# readabs

Version: 0.2.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘sjmisc’ ‘stringr’
      All declared Imports should be used.
    ```

# readit

Version: 1.0.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# readODS

Version: 1.6.4

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      x[1]: "numeric"
      y[1]: "integer"
      
        adding: META-INF/ (stored 0%)
        adding: META-INF/manifest.xml (deflated 61%)
        adding: content.xml (deflated 96%)
        adding: meta.xml (deflated 51%)
        adding: mimetype (deflated 4%)
        adding: styles.xml (deflated 70%)
      ══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 20 SKIPPED: 0 FAILED: 1
      1. Failure: col_types ODS (@test_col_types.R#5) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# redcapAPI

Version: 2.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘DBI’ ‘readr’
      All declared Imports should be used.
    ```

# REDCapR

Version: 0.9.8

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# rfbCNPJ

Version: 0.1.1

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 27 marked UTF-8 strings
    ```

# rfishbase

Version: 3.0.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 44 marked UTF-8 strings
    ```

# rhmmer

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```

# Ricetl

Version: 0.2.5

## In both

*   checking package dependencies ... ERROR
    ```
    Packages required but not available: ‘devtools’ ‘gWidgetsRGtk2’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# Rilostat

Version: 0.2.1

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# rmsfuns

Version: 0.0.0.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Missing or unexported object: ‘base::shell.exec’
    ```

# rrr

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘Rcpp’
      All declared Imports should be used.
    ```

# rsoi

Version: 0.3.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘utils’
      All declared Imports should be used.
    ```

# RTCGAToolbox

Version: 2.12.1

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘RTCGAToolbox-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: getReport
    > ### Title: Draws a circle plot into working directory
    > ### Aliases: getReport
    > 
    > ### ** Examples
    > 
    > data(RTCGASample)
    > require("Homo.sapiens")
    Loading required package: Homo.sapiens
    Warning in library(package, lib.loc = lib.loc, character.only = TRUE, logical.return = TRUE,  :
      there is no package called ‘Homo.sapiens’
    > locations <- genes(Homo.sapiens,columns="SYMBOL")
    Error in genes(Homo.sapiens, columns = "SYMBOL") : 
      could not find function "genes"
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘Homo.sapiens’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.2Mb
      sub-directories of 1Mb or more:
        doc   3.8Mb
    ```

*   checking R code for possible problems ... NOTE
    ```
    .getGISTIC: no visible global function definition for ‘mcols<-’
      (.../revdep/checks.noindex/RTCGAToolbox/new/RTCGAToolbox.Rcheck/00_pkg_src/RTCGAToolbox/R/utils.R:47)
    Undefined global functions or variables:
      mcols<-
    ```

# rtimicropem

Version: 1.3

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘R6’
      All declared Imports should be used.
    ```

# rtweet

Version: 0.6.8

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 113868 marked UTF-8 strings
    ```

# rubias

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘ggplot2’
      All declared Imports should be used.
    ```

# SanFranBeachWater

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘tibble’
      All declared Imports should be used.
    ```

# SanzCircos

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘purrr’ ‘tidyr’
      All declared Imports should be used.
    ```

# sasMap

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘stringi’
      All declared Imports should be used.
    ```

# sevenbridges

Version: 1.12.3

## In both

*   checking installed package size ... NOTE
    ```
      installed size is 14.3Mb
      sub-directories of 1Mb or more:
        R     4.1Mb
        doc   9.5Mb
    ```

# sevenC

Version: 1.2.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Unexported object imported by a ':::' call: ‘GenomicRanges:::get_out_of_bound_index’
      See the note in ?`:::` about the use of this operator.
    ```

# spant

Version: 0.12.0

## In both

*   checking whether package ‘spant’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: loading Rplot failed
    See ‘.../revdep/checks.noindex/spant/new/spant.Rcheck/00install.out’ for details.
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘neurobase’
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘foreach’
      All declared Imports should be used.
    ```

# staRdom

Version: 1.0.8

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘readr’ ‘tools’
      All declared Imports should be used.
    ```

# starmie

Version: 0.1.2

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  7.2Mb
      sub-directories of 1Mb or more:
        doc       1.1Mb
        extdata   4.9Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘MCMCpack’
      All declared Imports should be used.
    ```

# stationaRy

Version: 0.4.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  8.4Mb
    ```

# statsDK

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘dplyr’ ‘ggplot2’ ‘stringr’
      All declared Imports should be used.
    ```

# stminsights

Version: 0.2.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘huge’ ‘readr’ ‘scales’ ‘shinyjs’
      All declared Imports should be used.
    ```

# sugrrants

Version: 0.2.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘gtable’
      All declared Imports should be used.
    ```

# SummarizedBenchmark

Version: 2.0.0

## In both

*   checking package dependencies ... NOTE
    ```
    Depends: includes the non-default packages:
      ‘tidyr’ ‘SummarizedExperiment’ ‘S4Vectors’ ‘BiocGenerics’ ‘UpSetR’
      ‘rlang’ ‘stringr’ ‘BiocParallel’ ‘ggplot2’ ‘mclust’ ‘dplyr’ ‘digest’
      ‘sessioninfo’ ‘crayon’ ‘tibble’
    Adding so many packages to the search path is excessive and importing
    selectively is preferable.
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 15.8Mb
      sub-directories of 1Mb or more:
        R      1.0Mb
        data  11.1Mb
        doc    3.5Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Package in Depends field not imported from: ‘BiocGenerics’
      These packages need to be imported from (in the NAMESPACE file)
      for when this namespace is loaded but not attached.
    Unexported object imported by a ':::' call: ‘BiocGenerics:::replaceSlots’
      See the note in ?`:::` about the use of this operator.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BDData-show.R:11)
    show,BDMethodList: no visible global function definition for ‘head’
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BDMethodList-show.R:8)
    show,BDMethodList: no visible global function definition for ‘head’
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BDMethodList-show.R:10)
    show,BenchDesign: no visible global function definition for ‘head’
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BenchDesign-show.R:19)
    show,BenchDesign: no visible global function definition for ‘head’
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BenchDesign-show.R:21)
    show,BenchDesign: no visible global function definition for ‘head’
      (.../revdep/checks.noindex/SummarizedBenchmark/new/SummarizedBenchmark.Rcheck/00_pkg_src/SummarizedBenchmark/R/BenchDesign-show.R:23-28)
    Undefined global functions or variables:
      . .id .method .val .valueClassTest FDR TPR colid comparison cor f
      head label meta metadata method overlap params post rerun sd slot
      value
    Consider adding
      importFrom("methods", ".valueClassTest", "slot")
      importFrom("stats", "cor", "sd")
      importFrom("utils", "head")
    to your NAMESPACE file (and ensure that your DESCRIPTION Imports field
    contains 'methods').
    ```

# survivALL

Version: 0.9.3

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘cowplot’
      All declared Imports should be used.
    ```

# sweep

Version: 0.2.1.1

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# SympluR

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘readr’
      All declared Imports should be used.
    ```

# synapter

Version: 2.6.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Quitting from lines 30-34 (fragmentmatching.Rmd) 
    Error: processing vignette 'fragmentmatching.Rmd' failed with diagnostics:
    there is no package called 'synapterdata'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘synapterdata’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  9.3Mb
      sub-directories of 1Mb or more:
        R     2.0Mb
        doc   5.9Mb
    ```

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Authors@R field gives more than one person with maintainer role:
      Laurent Gatto <lg390@cam.ac.uk> [aut, cre]
      Sebastian Gibb <mail@sebastiangibb.de> [aut, cre]
    ```

*   checking dependencies in R code ... NOTE
    ```
    Unexported objects imported by ':::' calls:
      ‘MSnbase:::.plotSingleSpectrum’ ‘MSnbase:::Spectrum2_mz_sorted’
      ‘MSnbase:::commonPeaks’ ‘MSnbase:::numberOfCommonPeaks’
      ‘MSnbase:::relaxedMatch’ ‘MSnbase:::utils.list2ssv’
      ‘MSnbase:::utils.ssv2list’ ‘MSnbase:::utils.ssv2vec’
      ‘MSnbase:::utils.vec2ssv’
      See the note in ?`:::` about the use of this operator.
    ```

# TCGAbiolinks

Version: 2.10.0

## In both

*   R CMD check timed out
    

*   checking dependencies in R code ... WARNING
    ```
    '::' or ':::' import not declared from: ‘tidyr’
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 75.5Mb
      sub-directories of 1Mb or more:
        R      4.1Mb
        data   4.1Mb
        doc   67.1Mb
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:156-157)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘dNetPipeline’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:161-162)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘dCommSignif’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:174)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘visNet’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:184-189)
    TCGAvisualize_oncoprint: no visible binding for global variable ‘value’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:936)
    readExonQuantification: no visible binding for global variable ‘exon’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/prepare.R:234-235)
    readExonQuantification: no visible binding for global variable
      ‘coordinates’
      (.../revdep/checks.noindex/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/prepare.R:234-235)
    Undefined global functions or variables:
      Tumor.purity barcode c3net clinical coordinates dCommSignif
      dNetInduce dNetPipeline exon knnmi.cross limmacontrasts.fit
      limmamakeContrasts minet portions rse_gene value visNet
    ```

# TCGAbiolinksGUI

Version: 1.8.0

## In both

*   checking package dependencies ... ERROR
    ```
    Packages required but not available:
      ‘IlluminaHumanMethylation450kanno.ilmn12.hg19’
      ‘IlluminaHumanMethylation450kmanifest’
      ‘IlluminaHumanMethylation27kmanifest’
      ‘IlluminaHumanMethylation27kanno.ilmn12.hg19’
      ‘IlluminaHumanMethylationEPICanno.ilm10b2.hg19’
      ‘IlluminaHumanMethylationEPICmanifest’
    
    Package suggested but not available for checking: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# TCGAbiolinksGUI.data

Version: 1.2.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is 19.7Mb
      sub-directories of 1Mb or more:
        data  18.6Mb
        doc    1.0Mb
    ```

# TCGAutils

Version: 1.2.1

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘TCGAutils-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: imputeAssay
    > ### Title: This function imputes assays values inside a
    > ###   'MultiAssayExperiment'
    > ### Aliases: imputeAssay
    > 
    > ### ** Examples
    > 
    > library(curatedTCGAData)
    Error in library(curatedTCGAData) : 
      there is no package called ‘curatedTCGAData’
    Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Quitting from lines 16-22 (TCGAutils.Rmd) 
    Error: processing vignette 'TCGAutils.Rmd' failed with diagnostics:
    there is no package called 'curatedTCGAData'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Packages suggested but not available for checking:
      ‘curatedTCGAData’ ‘devtools’ ‘org.Hs.eg.db’
      ‘TxDb.Hsapiens.UCSC.hg19.knownGene’
    ```

*   checking dependencies in R code ... NOTE
    ```
    Unexported objects imported by ':::' calls:
      ‘BiocGenerics:::replaceSlots’ ‘GenomicRanges:::.normarg_field’
      See the note in ?`:::` about the use of this operator.
    ```

# TeXCheckR

Version: 0.6.0

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# tidyLPA

Version: 0.2.3

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# tidytransit

Version: 0.3.5

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.3Mb
      sub-directories of 1Mb or more:
        extdata   4.4Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘here’ ‘htmltools’ ‘scales’ ‘stringr’
      All declared Imports should be used.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 41 marked UTF-8 strings
    ```

# tidyverse

Version: 1.2.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘dbplyr’ ‘reprex’ ‘rlang’
      All declared Imports should be used.
    ```

# timetk

Version: 0.1.1.1

## In both

*   checking package dependencies ... ERROR
    ```
    Package required but not available: ‘devtools’
    
    See section ‘The DESCRIPTION file’ in the ‘Writing R Extensions’
    manual.
    ```

# trread

Version: 0.2.5

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘here’ ‘htmltools’ ‘magrittr’ ‘scales’ ‘stringr’
      All declared Imports should be used.
    ```

# tximport

Version: 1.10.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Quitting from lines 100-104 (tximport.Rmd) 
    Error: processing vignette 'tximport.Rmd' failed with diagnostics:
    there is no package called 'TxDb.Hsapiens.UCSC.hg19.knownGene'
    Execution halted
    ```

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘TxDb.Hsapiens.UCSC.hg19.knownGene’
    ```

# ukbtools

Version: 0.11.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘plyr’
      All declared Imports should be used.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 5 marked UTF-8 strings
    ```

# valr

Version: 0.4.2

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# variancePartition

Version: 1.12.0

## In both

*   R CMD check timed out
    

# visdat

Version: 0.5.1

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      ── 6. Failure: vis_guess creates the right plot (@test-vis-guess.R#13)  ────────
      Figures don't match: vis-guess-default.svg
      
      
      nrows =  1000 ncols =  1000══ testthat results  ═══════════════════════════════════════════════════════════
      OK: 28 SKIPPED: 6 FAILED: 6
      1. Failure: guess_element correctly identifies individual elements (@test-guess-type.R#9) 
      2. Failure: guess_element correctly identifies individual elements (@test-guess-type.R#10) 
      3. Failure: vis_guess creates the right plot (@test-vis-guess.R#10) 
      4. Failure: vis_guess creates the right plot (@test-vis-guess.R#11) 
      5. Failure: vis_guess creates the right plot (@test-vis-guess.R#12) 
      6. Failure: vis_guess creates the right plot (@test-vis-guess.R#13) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘plotly’ ‘rlang’
      All declared Imports should be used.
    ```

# webTRISr

Version: 0.1.1

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘devtools’
    ```

# xpose4

Version: 4.6.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.1Mb
      sub-directories of 1Mb or more:
        R   4.0Mb
    ```

# xtractomatic

Version: 3.4.2

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    date	lon	lat	lowLon	higLon	lowLat	higLat
    4/23/2003	203.899	19.664	203.899	203.899	19.664	19.664
    4/24/2003	204.151	19.821	203.912597	204.389403	18.78051934	20.86148066
    4/30/2003	203.919	20.351	203.6793669	204.1586331	18.79728188	21.90471812
    5/1/2003	204.229	20.305	203.9943343	204.4636657	18.90440013	21.70559987
    Quitting from lines 818-843 (Usingxtractomatic.Rmd) 
    Error: processing vignette 'Usingxtractomatic.Rmd' failed with diagnostics:
    (converted from warning) Removed 4070 rows containing missing values (geom_raster).
    Execution halted
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```


# aire.zmvm

Version: 0.5.0

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 38 marked UTF-8 strings
    ```

# alphavantager

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘devtools’
      All declared Imports should be used.
    ```

# annotatr

Version: 1.2.1

## In both

*   R CMD check timed out
    

*   checking R code for possible problems ... NOTE
    ```
    plot_coannotations: no visible binding for global variable ‘.’
      (.../revdep/checks/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:176-178)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:412-429)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:415-420)
    plot_numerical_coannotations: no visible binding for global variable
      ‘.’
      (.../revdep/checks/annotatr/new/annotatr.Rcheck/00_pkg_src/annotatr/R/visualize.R:422-427)
    Undefined global functions or variables:
      .
    ```

# ArchaeoPhases

Version: 1.3

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘DT’
      All declared Imports should be used.
    ```

# asciiSetupReader

Version: 1.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘stringi’
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

# biomartr

Version: 0.5.2

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      trying URL 'ftp://ftp.ncbi.nlm.nih.gov/genomes/refseq/viral/assembly_summary.txt'
      Content type 'unknown' length 2242561 bytes (2.1 MB)
      ==================================================
      trying URL 'ftp://ftp.ncbi.nlm.nih.gov/genomes/GENOME_REPORTS/overview.txt'
      Content type 'unknown' length 3016122 bytes (2.9 MB)
      ==================================================
      trying URL 'ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/metagenomes/assembly_summary.txt'
      Content type 'unknown' length 366154 bytes (357 KB)
      ==================================================
      testthat results ================================================================
      OK: 5 SKIPPED: 48 FAILED: 1
      1. Error: The biomart() interface works properly.. (@test-biomart.R#14) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Quitting from lines 97-112 (Functional_Annotation.Rmd) 
    Error: processing vignette 'Functional_Annotation.Rmd' failed with diagnostics:
    The query to the BioMart webservice returned an invalid result: the number of columns in the result table does not equal the number of attributes in the query. Please report this to the mailing list.
    Execution halted
    ```

# breathtestcore

Version: 0.4.0

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

# chimeraviz

Version: 1.0.4

## In both

*   R CMD check timed out
    

*   checking package dependencies ... NOTE
    ```
    Depends: includes the non-default packages:
      ‘Biostrings’ ‘GenomicRanges’ ‘IRanges’ ‘Gviz’ ‘S4Vectors’ ‘ensembldb’
      ‘AnnotationFilter’
    Adding so many packages to the search path is excessive and importing
    selectively is preferable.
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.5Mb
      sub-directories of 1Mb or more:
        doc       2.7Mb
        extdata   2.0Mb
    ```

# chipenrich.data

Version: 2.0.0

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Error: processing vignette 'chipenrich.data-vignette.Rmd' failed with diagnostics:
    path for html_dependency not found: 
    Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 147.8Mb
      sub-directories of 1Mb or more:
        data  147.0Mb
    ```

# crosswalkr

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘dplyr’
      All declared Imports should be used.
    ```

# curatedMetagenomicData

Version: 1.2.2

## In both

*   R CMD check timed out
    

*   checking package dependencies ... NOTE
    ```
    Depends: includes the non-default packages:
      ‘dplyr’ ‘phyloseq’ ‘Biobase’ ‘ExperimentHub’ ‘AnnotationHub’
      ‘magrittr’
    Adding so many packages to the search path is excessive and importing
    selectively is preferable.
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  8.6Mb
      sub-directories of 1Mb or more:
        help   7.9Mb
    ```

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Package listed in more than one of Depends, Imports, Suggests, Enhances:
      ‘BiocInstaller’
    A package should be listed in only one of these fields.
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘BiocInstaller’
      All declared Imports should be used.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ExpressionSet2MRexperiment: no visible global function definition for
      ‘AnnotatedDataFrame’
      (.../revdep/checks/curatedMetagenomicData/new/curatedMetagenomicData.Rcheck/00_pkg_src/curatedMetagenomicData/R/ExpressionSet2MRexperiment.R:45)
    ExpressionSet2MRexperiment: no visible global function definition for
      ‘phenoData’
      (.../revdep/checks/curatedMetagenomicData/new/curatedMetagenomicData.Rcheck/00_pkg_src/curatedMetagenomicData/R/ExpressionSet2MRexperiment.R:46-47)
    curatedMetagenomicData : <anonymous>: no visible global function
      definition for ‘exprs<-’
      (.../revdep/checks/curatedMetagenomicData/new/curatedMetagenomicData.Rcheck/00_pkg_src/curatedMetagenomicData/R/curatedMetagenomicData.R:57-58)
    Undefined global functions or variables:
      AnnotatedDataFrame exprs<- phenoData
    ```

*   checking Rd files ... NOTE
    ```
    prepare_Rd: HMP_2012.Rd:540-542: Dropping empty section \seealso
    prepare_Rd: KarlssonFH_2013.Rd:90-92: Dropping empty section \seealso
    prepare_Rd: LeChatelierE_2013.Rd:86-88: Dropping empty section \seealso
    prepare_Rd: LomanNJ_2013_Hi.Rd:82-84: Dropping empty section \seealso
    prepare_Rd: LomanNJ_2013_Mi.Rd:82-84: Dropping empty section \seealso
    prepare_Rd: NielsenHB_2014.Rd:94-96: Dropping empty section \seealso
    prepare_Rd: Obregon_TitoAJ_2015.Rd:94-96: Dropping empty section \seealso
    prepare_Rd: OhJ_2014.Rd:86-88: Dropping empty section \seealso
    prepare_Rd: QinJ_2012.Rd:106-108: Dropping empty section \seealso
    prepare_Rd: QinN_2014.Rd:94-96: Dropping empty section \seealso
    prepare_Rd: RampelliS_2015.Rd:90-92: Dropping empty section \seealso
    prepare_Rd: TettAJ_2016.Rd:184-186: Dropping empty section \seealso
    prepare_Rd: ZellerG_2014.Rd:94-96: Dropping empty section \seealso
    ```

# dataonderivatives

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘stats’
      All declared Imports should be used.
    ```

# datasus

Version: 0.4.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘RCurl’
      All declared Imports should be used.
    ```

# ddpcr

Version: 1.8

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
      2. Failure: reading v174 works (@test-v174.R#7) --------------------------------
      `expected_data` not equal to plate_data(plate).
      Incompatible type for column `HEX`: x numeric, y integer
      Incompatible type for column `FAM`: x numeric, y integer
      Incompatible type for column `cluster`: x numeric, y integer
      
      
      testthat results ================================================================
      OK: 267 SKIPPED: 0 FAILED: 2
      1. Failure: get_filled_drops works (@test-pnpp_experiment-filled.R#22) 
      2. Failure: reading v174 works (@test-v174.R#7) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.1Mb
      sub-directories of 1Mb or more:
        sample_data   3.0Mb
    ```

# DESeq2

Version: 1.16.1

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      > test_check("DESeq2")
      1. Error: tximport works (@test_tximport.R#12) ---------------------------------
      importing inferential replicates for Salmon or Sailfish requires package `rjson`.
        to skip this step, set dropInfReps=TRUE
      1: tximport(files, type = "salmon", tx2gene = tx2gene) at testthat/test_tximport.R:12
      2: infRepImporter(dirname(files[i]))
      3: readInfRepFish(x, type)
      4: stop("importing inferential replicates for Salmon or Sailfish requires package `rjson`.\n  to skip this step, set dropInfReps=TRUE")
      
      testthat results ================================================================
      OK: 203 SKIPPED: 0 FAILED: 1
      1. Error: tximport works (@test_tximport.R#12) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    reading in files with read_tsv
    1 Quitting from lines 256-257 (DESeq2.Rmd) 
    Error: processing vignette 'DESeq2.Rmd' failed with diagnostics:
    importing inferential replicates for Salmon or Sailfish requires package `rjson`.
      to skip this step, set dropInfReps=TRUE
    Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  5.2Mb
      sub-directories of 1Mb or more:
        doc    2.4Mb
        libs   1.0Mb
    ```

# DiagrammeR

Version: 0.9.2

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.4Mb
      sub-directories of 1Mb or more:
        R             1.9Mb
        htmlwidgets   3.0Mb
    ```

# diffloop

Version: 1.4.0

## In both

*   checking for hidden files and directories ... NOTE
    ```
    Found the following hidden files and directories:
      .travis.yml
    These were most likely included in error. See section ‘Package
    structure’ in the ‘Writing R Extensions’ manual.
    ```

# dwapi

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘xml2’
      All declared Imports should be used.
    ```

# eechidna

Version: 1.1

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.4Mb
      sub-directories of 1Mb or more:
        data   4.9Mb
        doc    1.2Mb
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

Version: 0.4.0

## In both

*   checking Rd cross-references ... NOTE
    ```
    Package unavailable to check Rd xrefs: ‘metafor’
    ```

# EventStudy

Version: 0.34

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.6Mb
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
    [1] ".../revdep/checks/fastqcr/new/fastqcr.Rcheck/fastqcr/fastqc_results"
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

Version: 0.2.0

## In both

*   checking whether package ‘fastR2’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘mosaic’ was built under R version 3.4.3
    See ‘.../revdep/checks/fastR2/new/fastR2.Rcheck/00install.out’ for details.
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘magrittr’
      All declared Imports should be used.
    ```

# genomation

Version: 1.8.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.1Mb
      sub-directories of 1Mb or more:
        doc       3.6Mb
        extdata   1.2Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘RUnit’
      All declared Imports should be used.
    Unexported object imported by a ':::' call: ‘BiocGenerics:::testPackage’
      See the note in ?`:::` about the use of this operator.
    ```

*   checking files in ‘vignettes’ ... NOTE
    ```
    The following directory looks like a leftover from 'knitr':
      ‘cache’
    Please remove from your package.
    ```

# genomes

Version: 3.6.0

## In both

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Malformed Description field: should contain one or more complete sentences.
    ```

# GenomicDataCommons

Version: 1.0.5

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    Error in re-building vignettes:
      ...
    Loading required package: magrittr
    
    Attaching package: 'GenomicDataCommons'
    
    The following object is masked from 'package:stats':
    
        filter
    
    sh: gdc-client: command not found
    Error: processing vignette 'overview.Rmd' failed with diagnostics:
    path for html_dependency not found: 
    Execution halted
    ```

*   checking R code for possible problems ... NOTE
    ```
    default_fields.character: no visible binding for global variable
      ‘defaults’
      (.../revdep/checks/GenomicDataCommons/new/GenomicDataCommons.Rcheck/00_pkg_src/GenomicDataCommons/R/fields.R:51)
    Undefined global functions or variables:
      defaults
    ```

*   checking Rd \usage sections ... NOTE
    ```
    S3 methods shown with full name in documentation object 'as.data.frame.GDCResults':
      ‘as.data.frame.GDCResults’
    
    The \usage entries for S3 methods should use the \method markup and not
    their full name.
    See chapter ‘Writing R documentation files’ in the ‘Writing R
    Extensions’ manual.
    ```

# geojsonio

Version: 0.5.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.2Mb
      sub-directories of 1Mb or more:
        doc        1.4Mb
        examples   1.6Mb
        vign       1.0Mb
    ```

# ggCompNet

Version: 0.1.0

## In both

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

# gutenbergr

Version: 0.1.3

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 13617 marked UTF-8 strings
    ```

# haven

Version: 1.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘hms’
      All declared Imports should be used.
    ```

*   checking for GNU extensions in Makefiles ... NOTE
    ```
    GNU make is a SystemRequirements.
    ```

# isomiRs

Version: 1.4.0

## In both

*   checking R code for possible problems ... NOTE
    ```
    ...
      variable ‘add’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:97-99)
    isoSelect,IsomirDataSeq : <anonymous>: no visible binding for global
      variable ‘t5’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:97-99)
    isoSelect,IsomirDataSeq : <anonymous>: no visible binding for global
      variable ‘t3’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:97-99)
    isoSelect,IsomirDataSeq : <anonymous>: no visible binding for global
      variable ‘id’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:97-99)
    isoSelect,IsomirDataSeq : <anonymous>: no visible binding for global
      variable ‘freq’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:97-99)
    isoSelect,IsomirDataSeq: no visible binding for global variable ‘freq’
      (.../revdep/checks/isomiRs/new/isomiRs.Rcheck/00_pkg_src/isomiRs/R/AllMethods.R:102-105)
    Undefined global functions or variables:
      Count DB X1 X2 add af ambiguity average change condition current
      enrich enrichGO error freq gene go group id mir mir_f mir_n mism
      mism_f mism_n ngene pct_abundance reference rowMax rowMin sel_genes
      t3 t5 term term_short type value y
    ```

# jpmesh

Version: 1.0.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘readr’
      All declared Imports should be used.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 176 marked UTF-8 strings
    ```

# jpndistrict

Version: 0.3.0

## In both

*   checking whether package ‘jpndistrict’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘jpmesh’ was built under R version 3.4.3
    See ‘.../revdep/checks/jpndistrict/new/jpndistrict.Rcheck/00install.out’ for details.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 502 marked UTF-8 strings
    ```

# kokudosuuchi

Version: 0.4.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘stringi’
      All declared Imports should be used.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 52458 marked UTF-8 strings
    ```

# leaflet.esri

Version: 0.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘htmlwidgets’ ‘shiny’
      All declared Imports should be used.
    ```

# leaflet.extras

Version: 0.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘shiny’
      All declared Imports should be used.
    ```

# macleish

Version: 0.3.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘DBI’
      All declared Imports should be used.
    ```

# mosaic

Version: 1.1.1

## In both

*   checking package dependencies ... NOTE
    ```
    Package which this enhances but not available for checking: ‘manipulate’
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  6.1Mb
      sub-directories of 1Mb or more:
        R     3.1Mb
        doc   2.4Mb
    ```

*   checking Rd cross-references ... NOTE
    ```
    Package unavailable to check Rd xrefs: ‘cubature’
    ```

# mudata2

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘hms’ ‘methods’
      All declared Imports should be used.
    ```

# myTAI

Version: 0.6.0

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.8Mb
      sub-directories of 1Mb or more:
        data   2.0Mb
        doc    2.7Mb
    ```

# nesRdata

Version: 0.1.0

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 5 marked UTF-8 strings
    ```

# PKPDmisc

Version: 2.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘purrr’
      All declared Imports should be used.
    ```

# pointblank

Version: 0.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘Hmisc’ ‘digest’ ‘htmltools’ ‘knitr’ ‘lazyWeave’ ‘lubridate’ ‘rJava’
      All declared Imports should be used.
    ```

# prophet

Version: 0.2.1

## In both

*   R CMD check timed out
    

*   checking whether package ‘prophet’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘Rcpp’ was built under R version 3.4.3
    See ‘.../revdep/checks/prophet/new/prophet.Rcheck/00install.out’ for details.
    ```

*   checking installed package size ... NOTE
    ```
      installed size is  7.0Mb
      sub-directories of 1Mb or more:
        libs   5.6Mb
    ```

# PWFSLSmoke

Version: 0.99.9

## In both

*   checking whether package ‘PWFSLSmoke’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘MazamaSpatialUtils’ was built under R version 3.4.3
    See ‘.../revdep/checks/PWFSLSmoke/new/PWFSLSmoke.Rcheck/00install.out’ for details.
    ```

# QuaternaryProd

Version: 1.4.0

## In both

*   checking whether package ‘QuaternaryProd’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘Rcpp’ was built under R version 3.4.3
    See ‘.../revdep/checks/QuaternaryProd/new/QuaternaryProd.Rcheck/00install.out’ for details.
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 10.7Mb
      sub-directories of 1Mb or more:
        extdata   9.7Mb
    ```

# rcv

Version: 0.2.1

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 6543 marked UTF-8 strings
    ```

# readODS

Version: 1.6.4

## Newly broken

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      y[1]: "integer"
      
      
        adding: META-INF/ (stored 0%)
        adding: META-INF/manifest.xml (deflated 61%)
        adding: content.xml (deflated 96%)
        adding: meta.xml (deflated 51%)
        adding: mimetype (deflated 4%)
        adding: styles.xml (deflated 70%)
      testthat results ================================================================
      OK: 20 SKIPPED: 0 FAILED: 1
      1. Failure: col_types ODS (@test_col_types.R#5) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# rmonad

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘R6’
      All declared Imports should be used.
    ```

# rmsfuns

Version: 0.0.0.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Missing or unexported object: ‘base::shell.exec’
    ```

# RQGIS

Version: 1.0.2

## In both

*   checking whether package ‘RQGIS’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘reticulate’ was built under R version 3.4.3
    See ‘.../revdep/checks/RQGIS/new/RQGIS.Rcheck/00install.out’ for details.
    ```

# rrr

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘Rcpp’
      All declared Imports should be used.
    ```

# RSocrata

Version: 1.7.3-2

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Not Found (HTTP 404).
      1: read.socrata("https://data.cityofboston.gov/resource/awu8-dc52.csv?$where=case_enquiry_id< 101000295717") at testthat/test-all.R:239
      2: getResponse(validUrl, email, password) at .../revdep/checks/RSocrata/new/RSocrata.Rcheck/00_pkg_src/RSocrata/R/RSocrata.R:302
      3: httr::stop_for_status(response) at .../revdep/checks/RSocrata/new/RSocrata.Rcheck/00_pkg_src/RSocrata/R/RSocrata.R:185
      
      2017-12-12 14:58:57.816 getResponse: Error in httr GET: 400  https://soda.demo.socrata.com/resource/4334-bgaj.csv?%24app_token=ew2rEMuESuzWPqMkyPfOSGJgE&$order=:id
      2017-12-12 14:58:58.525 getResponse: Error in httr GET: 400  https://soda.demo.socrata.com/resource/4334-bgaj.csv?%24app_token=ew2rEMuESuzWPqMkyPfOSGJgE&$order=:id
      2017-12-12 14:59:00.651 getResponse: Error in httr GET: 403  https://soda.demo.socrata.com/resource/a9g2-feh2.csv?$order=:id
      2017-12-12 14:59:01.319 getResponse: Error in httr GET: 403  https://soda.demo.socrata.com/resource/a9g2-feh2.json?$order=:id
      testthat results ================================================================
      OK: 155 SKIPPED: 0 FAILED: 1
      1. Error: Read data with missing dates (@test-all.R#239) 
      
      Error: testthat unit tests failed
      Execution halted
    ```

# rsoi

Version: 0.3.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘utils’
      All declared Imports should be used.
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

Version: 0.6.0

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 113868 marked UTF-8 strings
    ```

# SanFranBeachWater

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘tibble’
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

Version: 1.6.4

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  5.8Mb
      sub-directories of 1Mb or more:
        R     2.2Mb
        doc   2.8Mb
    ```

# spatialEco

Version: 1.0-0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘rgdal’
      All declared Imports should be used.
    ```

# starmie

Version: 0.1.2

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  7.1Mb
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
      installed size is  8.3Mb
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

# stplanr

Version: 0.2.1

## In both

*   checking examples ... ERROR
    ```
    Running examples in ‘stplanr-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: geo_buffer
    > ### Title: Perform a buffer operation on a temporary projected CRS
    > ### Aliases: geo_buffer
    > 
    > ### ** Examples
    > 
    > buff_sp = geo_buffer(routes_fast, width = 100)
    Transforming to CRS +proj=aeqd +lat_0=53.81895189 +lon_0=-1.52748741 +x_0=0 +y_0=0 +ellps=WGS84
    > class(buff_sp)
    [1] "SpatialPolygons"
    attr(,"package")
    [1] "sp"
    > plot(buff_sp, col = "red")
    > routes_fast_sf = sf::st_as_sf(routes_fast)
    > buff_sf = geo_buffer(routes_fast_sf, dist = 50)
    Assertion failed: (ee0 && ee1), function processIntersections, file ../../../src/geos-3.6.1/src/noding/IntersectionAdder.cpp, line 96.
    ```

*   checking package dependencies ... NOTE
    ```
    Package which this enhances but not available for checking: ‘tmap’
    ```

# survivALL

Version: 0.9.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘Biobase’ ‘broom’ ‘data.table’ ‘magrittr’ ‘pander’ ‘png’ ‘readr’
      ‘survsim’ ‘testthat’
      All declared Imports should be used.
    ```

# sweep

Version: 0.2.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘devtools’ ‘lazyeval’ ‘lubridate’ ‘tidyr’
      All declared Imports should be used.
    ```

# synapter

Version: 2.0.0

## In both

*   checking whether package ‘synapter’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘Rcpp’ was built under R version 3.4.3
    See ‘.../revdep/checks/synapter/new/synapter.Rcheck/00install.out’ for details.
    ```

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
      installed size is  8.7Mb
      sub-directories of 1Mb or more:
        R     1.1Mb
        doc   6.3Mb
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
      ‘MSnbase:::relaxedMatch’ ‘MSnbase:::utils.applyColumnwiseByGroup’
      ‘MSnbase:::utils.list2ssv’ ‘MSnbase:::utils.ssv2list’
      ‘MSnbase:::utils.ssv2vec’ ‘MSnbase:::utils.vec2ssv’
      See the note in ?`:::` about the use of this operator.
    ```

# TCGAbiolinks

Version: 2.5.9

## In both

*   checking examples ... ERROR
    ```
    ...
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    |NA                          |NA                                  |NA                   |NA                           |
    Error in checkProjectInput(project) : 
      Please set a valid project argument from the column id above. Project TCGA-ACC was not found.
    Calls: GDCquery -> checkProjectInput
    Execution halted
    ```

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      testthat results ================================================================
      OK: 97 SKIPPED: 0 FAILED: 16
      1. Error: TCGAanalyze_survival creates pdf (@test-analyse.R#4) 
      2. Error: Results from TCGAanalyze_DEA and DMR in starburst plot are correct (@test-analyse.R#182) 
      3. Error: GDCdownload API method for two files is working  (@test-prepare-download.R#4) 
      4. Error: GDCdownload API method for one files is working  (@test-prepare-download.R#20) 
      5. Error: GDCprepare accepts more than one project (@test-prepare-download.R#50) 
      6. Error: Accecpts more than one platform (@test-prepare-download.R#68) 
      7. Error: GDCquery can filter by data.category (@test-query.R#5) 
      8. Error: GDCquery accepts more than one project (@test-query.R#11) 
      9. Error: GDCquery can filter by sample.type (@test-query.R#23) 
      1. ...
      
      Error: testthat unit tests failed
      Execution halted
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    
    The following objects are masked from 'package:S4Vectors':
    
        first, intersect, rename, setdiff, setequal, union
    
    The following objects are masked from 'package:BiocGenerics':
    
        combine, intersect, setdiff, union
    
    The following objects are masked from 'package:stats':
    
        filter, lag
    
    The following objects are masked from 'package:base':
    
        intersect, setdiff, setequal, union
    
    Quitting from lines 16-20 (clinical.Rmd) 
    Error: processing vignette 'clinical.Rmd' failed with diagnostics:
    there is no package called 'DT'
    Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 61.8Mb
      sub-directories of 1Mb or more:
        R      1.9Mb
        data   2.3Mb
        doc   57.4Mb
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/analyze.R:1131)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘dNetInduce’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:156-157)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘dNetPipeline’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:161-162)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘dCommSignif’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:174)
    TCGAvisualize_SurvivalCoxNET: no visible global function definition for
      ‘visNet’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:184-189)
    TCGAvisualize_oncoprint: no visible binding for global variable ‘value’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/visualize.R:933)
    getTSS: no visible global function definition for ‘promoters’
      (.../revdep/checks/TCGAbiolinks/new/TCGAbiolinks.Rcheck/00_pkg_src/TCGAbiolinks/R/methylation.R:1745-1746)
    Undefined global functions or variables:
      c3net dCommSignif dNetInduce dNetPipeline knnmi.cross
      limmacontrasts.fit limmamakeContrasts minet portions promoters value
      visNet
    ```

*   checking for unstated dependencies in vignettes ... NOTE
    ```
    'library' or 'require' call not declared from: ‘DT’
    ```

# TCGAbiolinksGUI

Version: 1.2.1

## In both

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    
    The following objects are masked from 'package:S4Vectors':
    
        first, intersect, rename, setdiff, setequal, union
    
    The following objects are masked from 'package:BiocGenerics':
    
        combine, intersect, setdiff, union
    
    The following objects are masked from 'package:stats':
    
        filter, lag
    
    The following objects are masked from 'package:base':
    
        intersect, setdiff, setequal, union
    
    Quitting from lines 11-15 (data.Rmd) 
    Error: processing vignette 'data.Rmd' failed with diagnostics:
    there is no package called 'DT'
    Execution halted
    ```

*   checking installed package size ... NOTE
    ```
      installed size is 30.3Mb
      sub-directories of 1Mb or more:
        app   1.0Mb
        doc  28.9Mb
    ```

*   checking DESCRIPTION meta-information ... NOTE
    ```
    Malformed Description field: should contain one or more complete sentences.
    ```

*   checking for unstated dependencies in vignettes ... NOTE
    ```
    'library' or 'require' calls not declared from:
      ‘DT’ ‘dplyr’
    ```

# tidyquant

Version: 0.5.3

## In both

*   checking tests ...
    ```
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      
      
      testthat results ================================================================
      OK: 155 SKIPPED: 2 FAILED: 3
      1. Failure: Test returns tibble with correct rows and columns. (@test_tq_get_key_stats.R#15) 
      2. Failure: Test returns tibble with correct rows and columns. (@test_tq_get_key_stats.R#17) 
      3. Failure: Test returns tibble with correct rows and columns. (@test_tq_get_key_stats.R#19) 
      
      Error: testthat unit tests failed
      In addition: Warning messages:
      1: In download.file(url, destfile = tmp, quiet = TRUE) :
        cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv': HTTP status was '403 Forbidden'
      2: x = 'AAPL', get = 'key.stats': Error in download.file(url, destfile = tmp, quiet = TRUE): cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv'
       
      Execution halted
    ```

*   checking whether package ‘tidyquant’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: package ‘quantmod’ was built under R version 3.4.3
    See ‘.../revdep/checks/tidyquant/new/tidyquant.Rcheck/00install.out’ for details.
    ```

*   checking re-building of vignette outputs ... WARNING
    ```
    ...
    Warning in download.file(url, destfile = tmp, quiet = TRUE) :
      cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv': HTTP status was '403 Forbidden'
    Warning: x = 'AAPL', get = 'key.stats': Error in download.file(url, destfile = tmp, quiet = TRUE): cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv'
    
    Warning in download.file(url, destfile = tmp, quiet = TRUE) :
      cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv': HTTP status was '403 Forbidden'
    Warning: x = 'AAPL', get = 'key.stats': Error in download.file(url, destfile = tmp, quiet = TRUE): cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv'
     Removing AAPL.
    Warning in download.file(url, destfile = tmp, quiet = TRUE) :
      cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=FB&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv': HTTP status was '403 Forbidden'
    Warning: x = 'FB', get = 'key.stats': Error in download.file(url, destfile = tmp, quiet = TRUE): cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=FB&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv'
     Removing FB.
    Warning in download.file(url, destfile = tmp, quiet = TRUE) :
      cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=GOOG&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv': HTTP status was '403 Forbidden'
    Warning: x = 'GOOG', get = 'key.stats': Error in download.file(url, destfile = tmp, quiet = TRUE): cannot open URL 'http://download.finance.yahoo.com/d/quotes.csv?s=GOOG&f=aa2a5bb4b6c1c4dd1ee7e8e9f6ghjj1j2j4j5j6kk3k4k5ll1mm3m4m5m6m7m8nopp2p5p6qrr1r5r6r7s6s7t8vwxy&e=.csv'
     Removing GOOG.
    Warning in value[[3L]](cond) : Returning as nested data frame.
    Quitting from lines 211-214 (TQ01-core-functions-in-tidyquant.Rmd) 
    Error: processing vignette 'TQ01-core-functions-in-tidyquant.Rmd' failed with diagnostics:
    object 'Ask' not found
    Execution halted
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘broom’ ‘curl’ ‘devtools’ ‘rvest’ ‘timeSeries’ ‘tseries’ ‘zoo’
      All declared Imports should be used.
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

Version: 0.1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘devtools’ ‘forecast’
      All declared Imports should be used.
    ```

# ukbtools

Version: 0.10.0

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

# variancePartition

Version: 1.6.0

## In both

*   R CMD check timed out
    

# xpose

Version: 0.4.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘gridExtra’
      All declared Imports should be used.
    ```


# nocov start
.onLoad <- function(libname, pkgname) {
  tzdb::tzdb_initialize()

  register_s3_method("testthat", "compare", "col_spec")
  register_s3_method("testthat", "compare", "tbl_df")
  register_s3_method("waldo", "compare_proxy", "tbl_df")

  opt <- options()
  opt_readr <- list(
    readr.show_progress = TRUE
  )
  to_set <- !(names(opt_readr) %in% names(opt))
  if(any(to_set)) options(opt_readr[to_set])
  invisible()
}

release_questions <- function() {
  c(
    "Have checked with the IDE team?"
  )
}

register_s3_method <- function(pkg, generic, class, fun = NULL) {
  stopifnot(is.character(pkg), length(pkg) == 1)
  stopifnot(is.character(generic), length(generic) == 1)
  stopifnot(is.character(class), length(class) == 1)

  if (is.null(fun)) {
    fun <- get(paste0(generic, ".", class), envir = parent.frame())
  } else {
    stopifnot(is.function(fun))
  }

  if (pkg %in% loadedNamespaces()) {
    registerS3method(generic, class, fun, envir = asNamespace(pkg))
  }

  # Always register hook in case package is later unloaded & reloaded
  setHook(
    packageEvent(pkg, "onLoad"),
    function(...) {
      registerS3method(generic, class, fun, envir = asNamespace(pkg))
    }
  )
}

is_testing <- function() {
  identical(Sys.getenv("TESTTHAT"), "true") &&
    identical(Sys.getenv("TESTTHAT_PKG"), "readr")
}
# nocov end

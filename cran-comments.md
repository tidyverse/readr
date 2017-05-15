This is a minor update that only corrects a test that would fail with the
upcoming update of the tibble package, which this package imports. Therefore
I haven't run any checks on downstream dependencies.

## Test environments
* local OS X install, R 3.3.1.
* Ubuntu 12.04 (on travis-ci), R-oldrel, R-release, R-devel
* Windows Server 2012 R2 (x64), R 3.3.0
* Rhub
  * Windows Server 2008 R2 SP1, R-devel, 32/64 bit
  * Debian Linux, R-devel, GCC ASAN/UBSAN
  * Fedora Linux, R-devel, clang, gfortran
  * Ubuntu Linux 16.04 LTS, R-release, GCC

## R CMD check results

There were no NOTEs, ERRORs or WARNINGs.

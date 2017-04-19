#include <R.h>
#include <R_ext/Rdynload.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL

void R_init_odbc(DllInfo* info) {
  R_registerRoutines(info, NULL, NULL, NULL, NULL);
  R_useDynamicSymbols(info, TRUE);
}

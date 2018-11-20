#ifndef READR_CONNECTION_H_
#define READR_CONNECTION_H_

#include <Rinternals.h>
#include <Rversion.h>

#ifdef __cplusplus
extern "C" {
#endif

#define class class_name
#define private private_ptr
#include <R_ext/Connections.h>
#undef class
#undef private

Rconnection get_connection(SEXP con);
size_t write_connection(Rconnection con, void* data, size_t n);

#ifdef __cplusplus
}
#endif

#endif

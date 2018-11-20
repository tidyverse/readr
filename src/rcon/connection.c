#include "connection.h"

#define class class_name
#define private private_ptr
#include <R_ext/Connections.h>
#undef class
#undef private

#if R_CONNECTIONS_VERSION != 1
#error "Missing or unsupported connection API in R"
#endif

#if defined(R_VERSION) && R_VERSION >= R_Version(3, 3, 0)
Rconnection get_connection(SEXP con) { return R_GetConnection(con); }
size_t write_connection(Rconnection con, void* data, size_t n) {
  return R_WriteConnection(con, data, n);
}
#else
extern Rconnection getConnection(int);
Rconnection get_connection(SEXP con) {
  if (!Rf_inherits(con, "connection"))
    Rf_error("invalid connection");
  return getConnection(Rf_asInteger(con));
}
#endif

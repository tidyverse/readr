#include "write_connection.h"

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
#else
extern "C" {
extern Rconnection getConnection(int);
}
Rconnection get_connection(SEXP con) {
  if (!Rf_inherits(con, "connection"))
    Rcpp::stop("invalid connection");
  return getConnection(Rf_asInteger(con));
}
#endif

// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/tutorial/container_sink.html
//
namespace io = boost::iostreams;

connection_sink::connection_sink(SEXP con) { con_ = get_connection(con); }
std::streamsize connection_sink::write(const char* s, std::streamsize n) {
  size_t write_size;

  if ((write_size = R_WriteConnection(con_, (void*)s, n)) !=
      static_cast<size_t>(n)) {
    Rcpp::stop("write failed, expected %l, got %l", n, write_size);
  }
  return write_size;
}

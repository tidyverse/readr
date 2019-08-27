#include "write_connection.h"

// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/tutorial/container_sink.html
//
namespace io = boost::iostreams;

connection_sink::connection_sink(SEXP con) { con_ = con; }
std::streamsize connection_sink::write(const char* s, std::streamsize n) {
  size_t write_size;

  if ((write_size = R_WriteConnection(con_, (void*)s, n)) !=
      static_cast<size_t>(n)) {
    Rcpp::stop("write failed, expected %l, got %l", n, write_size);
  }
  return write_size;
}

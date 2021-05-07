#include "cpp11/R.hpp"
#include "cpp11/function.hpp"
#include "cpp11/raws.hpp"
#include "cpp11/strings.hpp"

#include <fstream>

// Wrapper around R's read_bin function
SEXP read_bin(const cpp11::sexp& con, int bytes) {
  static auto readBin = cpp11::package("base")["readBin"];

  return readBin(con, "raw", bytes);
}

// Read data from a connection in chunks and then combine into a single
// raw vector.
//
[[cpp11::register]] std::string
read_connection_(const cpp11::sexp& con, std::string filename, int chunk_size) {

  std::ofstream out(filename.c_str(), std::fstream::out | std::fstream::binary);

  SEXP chunk = read_bin(con, chunk_size);
  R_xlen_t chunk_len = Rf_xlength(chunk);

  while (chunk_len > 0) {
    std::copy(
        RAW(chunk),
        RAW(chunk) + Rf_xlength(chunk),
        std::ostream_iterator<char>(out));
    chunk = read_bin(con, chunk_size);
    chunk_len = Rf_xlength(chunk);
  }

  return filename;
}

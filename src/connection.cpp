#include "cpp11/R.hpp"
#include "cpp11/function.hpp"
#include "cpp11/raws.hpp"
#include "cpp11/strings.hpp"

#include <fstream>

// Wrapper around R's read_bin function
cpp11::raws read_bin(cpp11::sexp con, int bytes) {
  auto readBin = cpp11::package("base")["readBin"];

  return cpp11::raws(readBin(con, "raw", bytes));
}

// Read data from a connection in chunks and then combine into a single
// raw vector.
//
[[cpp11::export]] std::string
read_connection_(cpp11::sexp con, std::string filename, int chunk_size) {

  std::ofstream out(filename.c_str(), std::fstream::out | std::fstream::binary);

  cpp11::writable::raws chunk;
  while ((chunk = read_bin(con, chunk_size)).size() > 0) {
    std::copy(chunk.begin(), chunk.end(), std::ostream_iterator<char>(out));
  }

  return filename;
}

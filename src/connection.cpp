#include <Rcpp.h>
#include <fstream>

using namespace Rcpp;

// Wrapper around R's read_bin function
RawVector read_bin(RObject con, int bytes = 64 * 1024) {
  Rcpp::Environment baseEnv = Rcpp::Environment::base_env();
  Rcpp::Function readBin = baseEnv["readBin"];

  RawVector out = Rcpp::as<RawVector>(readBin(con, "raw", bytes));
  return out;
}

// Read data from a connection in chunks and then combine into a single
// raw vector.
//
// [[Rcpp::export]]
CharacterVector read_connection_(
    RObject con, std::string filename, int chunk_size = 64 * 1024) {

  std::ofstream out(filename.c_str(), std::fstream::out | std::fstream::binary);

  RawVector chunk;
  while ((chunk = read_bin(con, chunk_size)).size() > 0) {
    std::copy(chunk.begin(), chunk.end(), std::ostream_iterator<char>(out));
  }

  return filename;
}

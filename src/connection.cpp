#include <Rcpp.h>
using namespace Rcpp;

// Wrapper around R's read_bin function
RawVector read_bin(RObject con, size_t bytes = 64 * 1024) {
  Rcpp::Environment baseEnv = Rcpp::Environment::base_env();
  Rcpp::Function readBin = baseEnv["readBin"];

  RawVector out = Rcpp::as<RawVector>(readBin(con, "raw", bytes));
  return out;
}

// Read data from a connection in chunks and then combine into a single
// raw vector.
//
// [[Rcpp::export]]
RawVector read_connection_(RObject con, int chunk_size = 64 * 1024) {
  std::vector<RawVector> chunks;

  RawVector chunk;
  while((chunk = read_bin(con, chunk_size)).size() > 0)
    chunks.push_back(chunk);

  size_t size = 0;
  for (size_t i = 0; i < chunks.size(); ++i)
    size += chunks[i].size();

  RawVector out(size);
  size_t pos = 0;
  for (size_t i = 0; i < chunks.size(); ++i) {
    memcpy(RAW(out) + pos, RAW(chunks[i]), chunks[i].size());
    pos += chunks[i].size();
  }

  return out;
}


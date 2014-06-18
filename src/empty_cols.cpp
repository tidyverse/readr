#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
std::vector<bool> empty_cols(std::string x) {

  std::vector<bool> out;

  int col = 0;
  std::istringstream stream(x);

  char c;
  while ((c = stream.get()) && stream.good()) {
    if (c == '\n') {
      col = 0;
      continue;
    }
    col++;

    // Make sure there's enough room
    if (col >= out.size()) {
      out.resize(col, true);
    }
    if (!out[col - 1]) continue;

    if (c != ' ') out[col - 1] = false;
  }

  return out;
}

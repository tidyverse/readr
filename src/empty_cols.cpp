#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
std::vector<bool> empty_cols(std::string x) {

  std::vector<bool> is_white;

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
    if (col >= is_white.size()) {
      is_white.resize(col, true);
    }
    if (!is_white[col - 1]) continue;

    if (c != ' ') is_white[col - 1] = false;
  }

  return is_white;
}

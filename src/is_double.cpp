#include <Rcpp.h>
using namespace Rcpp;

bool is_double(std::string x) {
  const char* start = x.c_str();
  char* end;

  strtod(start, &end);
  return (end == start + x.size()) && (errno == 0);
}

// [[Rcpp::export]]
bool is_double(CharacterVector x) {
  int n = x.size();
  for (int i = 0; i < n; ++i) {
    String cur = x[i];
    if (!is_double(cur)) return false;
  }

  return true;
}

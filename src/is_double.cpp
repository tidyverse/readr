#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
bool is_double_one(std::string x) {
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
    if (!is_double_one(cur)) return false;
  }

  return true;
}

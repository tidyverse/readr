#include <Rcpp.h>
using namespace Rcpp;

// Take list of length p with character vectors of length n, and flip it so
// that you get a list of length n with vectors of length p. Assumes that
// all vectors are same length and does no checking.
// [[Rcpp::export]]
List flip(ListOf<CharacterVector> x) {
  int p = x.size();
  int n = x[0].size();

  List out(n);

  for(int i = 0; i < n; ++i) {
    CharacterVector v = CharacterVector(p);
    for(int j = 0; j < p; ++j) {
      v[j] = x[j][i];
    }
    out[i] = v;
  }

  return out;
}

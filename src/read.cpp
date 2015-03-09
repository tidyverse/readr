#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"

// [[Rcpp::export]]
CharacterVector read_file_(List sourceSpec) {
  SourcePtr source = sourceCreate(sourceSpec);

  CharacterVector out(1);
  out[0] = Rf_mkCharLen(source->begin(), source->end() - source->begin());
  return out;
}
,
// [[Rcpp::export]]
CharacterVector read_lines_(List sourceSpec, int n_max = -1) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerLine tokenizer;
  tokenizer.tokenize(source->begin(), source->end());

  int n = (n_max < 0) ? 1000 : n_max;
  CharacterVector out(n);

  int i = 0;
  for (Token t = tokenizer.nextToken(); t.type() != TOKEN_EOF; t = tokenizer.nextToken()) {
    if (i >= n) {
      if (n_max < 0) {
        n = (n * 3)/2 + 1;
        out = Rf_lengthgets(out, n);
      } else {
        break;
      }
    }

    if (t.type() == TOKEN_STRING)
      out[i] = t.asString();

    ++i;
  }

  if (i < n) {
    out = Rf_lengthgets(out, i);
  }

  return out;
}

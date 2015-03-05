#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "Collector.h"

// [[Rcpp::export]]
CharacterVector read_file_(List sourceSpec) {
  SourcePtr source = sourceCreate(sourceSpec);

  CharacterVector out(1);
  out[0] = Rf_mkCharLen(source->begin(), source->end() - source->begin());
  return out;
}

// [[Rcpp::export]]
std::vector<std::vector<std::string> > tokenize_(List sourceSpec, List tokenizerSpec, int n) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerPtr tokenizer = tokenizerCreate(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  std::vector<std::vector<std::string> > rows;

  int i = 0;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (n > 0 && i > n)
      break;

    if (t.row() >= rows.size()) {
      rows.resize(t.row() + 1);
    }

    std::vector<std::string>& row = rows[t.row()];
    if (t.col() >= row.size())
      row.resize(t.col() + 1);
    row[t.col()] = t.asString();

    ++i;
  }

  return rows;
}

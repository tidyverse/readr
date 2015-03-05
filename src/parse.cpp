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

// [[Rcpp::export]]
IntegerVector dim_tokens_(List sourceSpec, List tokenizerSpec) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerPtr tokenizer = tokenizerCreate(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  int rows = -1, cols = -1;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    rows = t.row();
    if (t.col() > cols)
      cols = t.col();
  }

  return IntegerVector::create(rows + 1, cols + 1);
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


// [[Rcpp::export]]
SEXP parse_(List sourceSpec, List tokenizerSpec, List collectorSpec) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerPtr tokenizer = tokenizerCreate(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  boost::shared_ptr<Collector> out = collectorCreate(collectorSpec);
  out->resize(100);

  int i = 0;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (i > out->size())
      out->resize(i * 2);

    out->setValue(i, t);
    ++i;
  }

  if (i != out->size()) {
    out->resize(i);
  }

  return out->vector();
}

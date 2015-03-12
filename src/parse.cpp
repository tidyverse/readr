#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"

// [[Rcpp::export]]
IntegerVector dim_tokens_(List sourceSpec, List tokenizerSpec) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  size_t rows = -1, cols = -1;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    rows = t.row();
    if (t.col() > cols)
      cols = t.col();
  }

  return IntegerVector::create(rows + 1, cols + 1);
}

// [[Rcpp::export]]
std::vector<int> count_fields_(List sourceSpec, List tokenizerSpec) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  std::vector<int> fields;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (t.row() >= fields.size()) {
      fields.resize(t.row() + 1);
    }

    fields[t.row()] = t.col();
  }

  return fields;
}

// [[Rcpp::export]]
std::vector<std::vector<std::string> > tokenize_(List sourceSpec, List tokenizerSpec, int n) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
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
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  boost::shared_ptr<Collector> out = Collector::create(collectorSpec);
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

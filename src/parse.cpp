#include <Rcpp.h>
using namespace Rcpp;

#include "Collector.h"
#include "LocaleInfo.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Warnings.h"

// [[Rcpp::export]]
IntegerVector dim_tokens_(List sourceSpec, List tokenizerSpec) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  int rows = -1, cols = -1;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    rows = t.row();

    if ((int) t.col() > cols)
      cols = t.col();
  }

  return IntegerVector::create(rows + 1, cols + 1);
}

// [[Rcpp::export]]
std::vector<int> count_fields_(List sourceSpec, List tokenizerSpec, int n_max) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  std::vector<int> fields;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t) n_max)
      break;

    if (t.row() >= fields.size()) {
      fields.resize(t.row() + 1);
    }

    fields[t.row()] = t.col() + 1;
  }

  return fields;
}

// [[Rcpp::export]]
RObject tokenize_(List sourceSpec, List tokenizerSpec, int n_max) {
  Warnings warnings;

  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<std::vector<std::string> > rows;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t) n_max)
      break;

    if (t.row() >= rows.size()) {
      rows.resize(t.row() + 1);
    }

    std::vector<std::string>& row = rows[t.row()];
    if (t.col() >= row.size())
      row.resize(t.col() + 1);

    row[t.col()] = t.asString();
  }

  RObject out = wrap(rows);
  return warnings.addAsAttribute(out);
}

// [[Rcpp::export]]
SEXP parse_vector_(CharacterVector x, List collectorSpec,
                   List locale_, const std::vector<std::string>& na) {
  Warnings warnings;
  int n = x.size();

  LocaleInfo locale(locale_);

  boost::shared_ptr<Collector> col = Collector::create(collectorSpec, locale);
  col->setWarnings(&warnings);
  col->resize(n);

  for (int i = 0; i < n; ++i) {
    Token t;
    if (x[i] == NA_STRING) {
      t = Token(TOKEN_MISSING, i, -1);
    } else {
      SEXP string = x[i];
      t = Token(CHAR(string), CHAR(string) + Rf_length(string), i, -1);
      t.flagNA(na);
      t.trim();
    }
    col->setValue(i, t);
  }

  return warnings.addAsAttribute(col->vector());
}

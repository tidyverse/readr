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

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    rows = t.row();

    if ((int)t.col() > cols)
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

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t)n_max)
      break;

    if (t.row() >= fields.size()) {
      fields.resize(t.row() + 1);
    }

    fields[t.row()] = t.col() + 1;
  }

  return fields;
}

// [[Rcpp::export]]
RObject guess_header_(List sourceSpec, List tokenizerSpec, List locale_) {
  Warnings warnings;
  LocaleInfo locale(locale_);
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  CollectorCharacter out(&locale.encoder_);
  out.setWarnings(&warnings);

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (t.row() > (size_t)0) // only read one row
      break;

    if (t.col() >= (size_t)out.size()) {
      out.resize(t.col() + 1);
    }

    if (t.type() == TOKEN_STRING) {
      out.setValue(t.col(), t);
    }
  }

  return out.vector();
}

// [[Rcpp::export]]
RObject tokenize_(List sourceSpec, List tokenizerSpec, int n_max) {
  Warnings warnings;

  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<std::vector<std::string> > rows;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t)n_max)
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
List tokenize_melt_(List sourceSpec, List tokenizerSpec, int n_max, List locale_) {
  Warnings warnings;

  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<int> row;
  std::vector<int> col;
  std::vector<std::string> val;
  std::vector<std::string> type;

  int i(0);
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t)n_max)
      break;

    if (i >= row.size()) {
      row.resize(i + 1);
      col.resize(i + 1);
      val.resize(i + 1);
      type.resize(i + 1);
    }

    row[i] = t.row() + 1;
    col[i] = t.col() + 1;
    val[i] = t.asString();
    type[i] = collectorGuessInternal(t.asString(), locale_);
    ++i;
  }

  List out = List::create(_["row"] = row,
                          _["col"] = col,
                          _["value"] = val,
                          _["data_type"] = type);
  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -i);
  return out;
}

// [[Rcpp::export]]
SEXP parse_vector_(
    CharacterVector x,
    List collectorSpec,
    List locale_,
    const std::vector<std::string>& na,
    const bool trim_ws = true) {
  Warnings warnings;
  int n = x.size();

  LocaleInfo locale(locale_);

  boost::shared_ptr<Collector> col = Collector::create(collectorSpec, &locale);
  col->setWarnings(&warnings);
  col->resize(n);

  for (int i = 0; i < n; ++i) {
    Token t;
    if (x[i] == NA_STRING) {
      t = Token(TOKEN_MISSING, i, -1);
    } else {
      SEXP string = x[i];
      t = Token(CHAR(string), CHAR(string) + Rf_length(string), i, -1, false);
      if (trim_ws) {
        t.trim();
      }
      t.flagNA(na);
    }
    col->setValue(i, t);
  }

  return warnings.addAsAttribute(col->vector());
}

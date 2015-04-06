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
std::vector<std::vector<std::string> > tokenize_(List sourceSpec, List tokenizerSpec, int n_max) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

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

  return rows;
}


//' Parse a character vector.
//'
//' @param x Character vector of elements to parse.
//' @param collector Column specification.
//' @keywords internal
//' @export
//' @examples
//' x <- c("1", "2", "3", NA)
//' parse_vector(x, col_integer())
//' parse_vector(x, col_double())
//' parse_vector(x, col_character())
//' parse_vector(x, col_skip())
//'
//' # Invalid values are replaced with missing values with a warning.
//' x <- c("1", "2", "3", "-")
//' parse_vector(x, col_double())
// [[Rcpp::export]]
SEXP parse_vector(CharacterVector x, List collectorSpec) {
  int n = x.size();

  boost::shared_ptr<Collector> out = Collector::create(collectorSpec);
  out->resize(n);

  for (int i = 0; i < n; ++i) {
    Token t;
    if (x[i] == NA_STRING) {
      t = Token(TOKEN_MISSING, i, -1);
    } else {
      SEXP string = x[i];
      t = Token(CHAR(string), CHAR(string) + Rf_length(string), i, -1);
    }
    out->setValue(i, t);
  }

  return out->vector();
}

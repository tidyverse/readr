#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"
#include "CollectorCharacter.h"

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
List read_tokens(List sourceSpec, List tokenizerSpec, ListOf<List> colSpecs,
                 CharacterVector col_names, int n_max = -1) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerPtr tokenizer = tokenizerCreate(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  std::vector<CollectorPtr> collectors = collectorsCreate(colSpecs);

  int p = collectors.size();
  int n = (n_max < 0) ? 1000 : n_max;
  collectorsResize(collectors, n);

  int i = 0;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (t.col() >= p)
      stop("In row %i, there are %i columns!", t.row() + 1, t.col() + 1);

    if (i >= n) {
      if (n_max >= 0)
        break;

      n = (i / tokenizer->proportionDone()) * 1.2;
      collectorsResize(collectors, n);
    }

    collectors[t.col()]->setValue(t.row(), t);
    i = t.row() + 1;
  }

  if (i < n) {
    collectorsResize(collectors, i);
  }

  // Save individual columns into a data frame
  List out(p);
  for (int j = 0; j < p; ++j) {
    out[j] = collectors[j]->vector();
  }
  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -i);
  out.attr("names") = col_names;

  return out;
}


// [[Rcpp::export]]
std::vector<std::string> collectorsGuess(List sourceSpec, List tokenizerSpec, int n = 100) {
  SourcePtr source = sourceCreate(sourceSpec);
  TokenizerPtr tokenizer = tokenizerCreate(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  std::vector<CollectorCharacter> collectors;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (t.row() >= n)
      break;

    // Add new collectors, if needed
    if (t.col() >= collectors.size()) {
      int old_p = collectors.size();
      collectors.resize(t.col() + 1);
      for (int j = old_p; j < collectors.size(); ++j) {
        collectors[j].resize(n);
      }
    }

    collectors[t.col()].setValue(t.row(), t);
  }

  std::vector<std::string> out;
  for (int j = 0; j < collectors.size(); ++j) {
    CharacterVector col = as<CharacterVector>(collectors[j].vector());
    out.push_back(collectorGuess(col));
  }

  return out;
}



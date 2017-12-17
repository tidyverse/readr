#include <Rcpp.h>
using namespace Rcpp;

#include "Collector.h"
#include "LocaleInfo.h"
#include "Progress.h"
#include "Reader.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Warnings.h"

// [[Rcpp::export]]
CharacterVector read_file_(List sourceSpec, List locale_) {
  SourcePtr source = Source::create(sourceSpec);
  LocaleInfo locale(locale_);

  return CharacterVector::create(
      locale.encoder_.makeSEXP(source->begin(), source->end()));
}

// [[Rcpp::export]]
RawVector read_file_raw_(List sourceSpec) {
  SourcePtr source = Source::create(sourceSpec);

  RawVector res(source->end() - source->begin());
  std::copy(source->begin(), source->end(), res.begin());
  return res;
}

// [[Rcpp::export]]
CharacterVector read_lines_(
    List sourceSpec,
    List locale_,
    std::vector<std::string> na,
    int n_max = -1,
    bool progress = true) {

  LocaleInfo locale(locale_);
  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine(na)),
      CollectorPtr(new CollectorCharacter(&locale.encoder_)),
      progress);

  return r.readToVector<CharacterVector>(n_max);
}

Function R6method(Environment env, const std::string& method) {
  return as<Function>(env[method]);
}
bool isTrue(SEXP x) {
  if (!(TYPEOF(x) == LGLSXP && Rf_length(x) == 1)) {
    stop("`continue()` must return a length 1 logical vector");
  }
  return LOGICAL(x)[0] == TRUE;
}

// [[Rcpp::export]]
void read_lines_chunked_(
    List sourceSpec,
    List locale_,
    std::vector<std::string> na,
    int chunkSize,
    Environment callback,
    bool progress = true) {

  LocaleInfo locale(locale_);
  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine(na)),
      CollectorPtr(new CollectorCharacter(&locale.encoder_)),
      progress);

  CharacterVector out;

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    CharacterVector out = r.readToVector<CharacterVector>(chunkSize);
    if (out.size() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.size();
  }

  return;
}

// [[Rcpp::export]]
List read_lines_raw_(List sourceSpec, int n_max = -1, bool progress = false) {

  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine()),
      CollectorPtr(new CollectorRaw()),
      progress);

  return r.readToVector<List>(n_max);
}

typedef std::vector<CollectorPtr>::iterator CollectorItr;

// [[Rcpp::export]]
RObject read_tokens_(
    List sourceSpec,
    List tokenizerSpec,
    ListOf<List> colSpecs,
    CharacterVector colNames,
    List locale_,
    int n_max = -1,
    bool progress = true) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress,
      colNames);

  return r.readToDataFrame(n_max);
}

// [[Rcpp::export]]
void read_tokens_chunked_(
    List sourceSpec,
    Environment callback,
    int chunkSize,
    List tokenizerSpec,
    ListOf<List> colSpecs,
    CharacterVector colNames,
    List locale_,
    bool progress = true) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress,
      colNames);

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    DataFrame out = r.readToDataFrame(chunkSize);
    if (out.nrows() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.nrows();
  }

  return;
}

// [[Rcpp::export]]
std::vector<std::string> guess_types_(
    List sourceSpec, List tokenizerSpec, Rcpp::List locale_, int n = 100) {
  Warnings warnings;
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source);
  tokenizer->setWarnings(&warnings); // silence warnings

  LocaleInfo locale(locale_);

  std::vector<CollectorPtr> collectors;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (t.row() >= (size_t)n)
      break;

    // Add new collectors, if needed
    if (t.col() >= collectors.size()) {
      int p = collectors.size() - t.col() + 1;
      for (int j = 0; j < p; ++j) {
        CollectorPtr col =
            CollectorPtr(new CollectorCharacter(&locale.encoder_));
        col->setWarnings(&warnings);
        col->resize(n);
        collectors.push_back(col);
      }
    }

    collectors[t.col()]->setValue(t.row(), t);
  }

  std::vector<std::string> out;
  for (size_t j = 0; j < collectors.size(); ++j) {
    CharacterVector col = as<CharacterVector>(collectors[j]->vector());
    out.push_back(collectorGuess(col, locale_));
  }

  return out;
}

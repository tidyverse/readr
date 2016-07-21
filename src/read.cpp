#include <Rcpp.h>
using namespace Rcpp;

#include "LocaleInfo.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"
#include "Progress.h"
#include "Warnings.h"
#include "Reader.h"

// [[Rcpp::export]]
CharacterVector read_file_(List sourceSpec, List locale_) {
  SourcePtr source = Source::create(sourceSpec);
  LocaleInfo locale(locale_);

  return CharacterVector::create(
    locale.encoder_.makeSEXP(source->begin(), source->end())
  );
}

// [[Rcpp::export]]
RawVector read_file_raw_(List sourceSpec) {
  SourcePtr source = Source::create(sourceSpec);

  RawVector res(source->end() - source->begin());
  std::copy(source->begin(), source->end(), res.begin());
  return res;
}

// [[Rcpp::export]]
CharacterVector read_lines_(List sourceSpec, List locale_, std::vector<std::string> na, int n_max = -1,
                            bool progress = true) {

  SourcePtr s = Source::create(sourceSpec);
  TokenizerPtr t(new TokenizerLine(na));
  LocaleInfo l(locale_);
  std::vector<CollectorPtr> c;
  c.push_back(CollectorPtr(new CollectorCharacter(&l.encoder_)));

  Reader r(s, t, c, CharacterVector(), &l, progress ? 25000 : 0);

  return r.readToVector<CharacterVector>(n_max);
}

// [[Rcpp::export]]
List read_lines_raw_(List sourceSpec, int n_max = -1, bool progress = false) {

  SourcePtr s = Source::create(sourceSpec);
  TokenizerPtr t(new TokenizerLine());
  std::vector<CollectorPtr> c;
  c.push_back(CollectorPtr(new CollectorRaw()));

  Reader r(s, t, c, CharacterVector(), NULL, progress ? 25000 : 0);

  return r.readToVector<List>(n_max);
}

typedef std::vector<CollectorPtr>::iterator CollectorItr;

// [[Rcpp::export]]
RObject read_tokens_(List sourceSpec, List tokenizerSpec, ListOf<List> colSpecs,
                    CharacterVector colNames, List locale_, int n_max = -1,
                    bool progress = true) {

  SourcePtr s = Source::create(sourceSpec);
  LocaleInfo l(locale_);
  std::vector<CollectorPtr> c = collectorsCreate(colSpecs, &l);
  TokenizerPtr t = Tokenizer::create(tokenizerSpec);

  Reader r(s, t, c, colNames, &l, progress ? 250000 : 0);

  return r.readToDataFrame(n_max);
}

// [[Rcpp::export]]
std::vector<std::string> guess_types_(List sourceSpec, List tokenizerSpec,
                                      Rcpp::List locale_, int n = 100) {
  Warnings warnings;
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings); // silence warnings

  LocaleInfo locale(locale_);

  std::vector<CollectorPtr> collectors;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (t.row() >= (size_t) n)
      break;

    // Add new collectors, if needed
    if (t.col() >= collectors.size()) {
      int p = collectors.size() - t.col() + 1;
      for (int j = 0; j < p; ++j) {
        CollectorPtr col = CollectorPtr(new CollectorCharacter(&locale.encoder_));
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

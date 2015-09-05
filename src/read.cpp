#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"
#include "Progress.h"
#include "Warnings.h"

// [[Rcpp::export]]
CharacterVector read_file_(List sourceSpec) {
  SourcePtr source = Source::create(sourceSpec);

  CharacterVector out(1);
  out[0] = Rf_mkCharLenCE(source->begin(), source->end() - source->begin(), CE_UTF8);
  return out;
}

// [[Rcpp::export]]
CharacterVector read_lines_(List sourceSpec, int n_max = -1, bool progress = true) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerLine tokenizer;
  tokenizer.tokenize(source->begin(), source->end());
  Progress progressBar;

  int n = (n_max < 0) ? 10000 : n_max;
  CharacterVector out(n);

  int i = 0;
  for (Token t = tokenizer.nextToken(); t.type() != TOKEN_EOF; t = tokenizer.nextToken()) {
    if (progress && (i + 1) % 25000 == 0)
      progressBar.show(tokenizer.progress());

    if (i >= n) {
      if (n_max < 0) {
        // Estimate rows in full dataset
        n = (i / tokenizer.progress().first) * 1.2;
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

  if (progress)
    progressBar.show(tokenizer.progress());
  progressBar.stop();

  return out;
}

typedef std::vector<CollectorPtr>::iterator CollectorItr;
void checkColumns(Warnings *pWarnings, int i, int j, int n) {
  if (j + 1 == n)
    return;

  pWarnings->addWarning(i, -1,
    tfm::format("%i columns", n),
    tfm::format("%i columns", j + 1)
  );
}

// [[Rcpp::export]]
RObject read_tokens(List sourceSpec, List tokenizerSpec, ListOf<List> colSpecs,
                    CharacterVector colNames, int n_max = -1,
                    bool progress = true) {
  Warnings warnings;

  SourcePtr source = Source::create(sourceSpec);

  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<CollectorPtr> collectors = collectorsCreate(colSpecs, &warnings);

  Progress progressBar;

  size_t p = collectors.size();
  // Work out how many output columns we have
  size_t pOut = 0;
  for(CollectorItr cur = collectors.begin(); cur != collectors.end(); ++cur) {
    if (!(*cur)->skip())
      pOut++;
  }

  // Match colNames to with non-skipped collectors, shrinking or growing
  // as needed
  CharacterVector outNames(pOut);
  int cj = 0;
  for (size_t j = 0; j < p; ++j) {
    if (collectors[j]->skip())
      continue;
    if (cj >= pOut)
      break;
    if (j < colNames.size()) {
      outNames[cj++] = colNames[j];
    } else {
      outNames[cj++] = tfm::format("X%i", j + 1);
    }
  }
  if (colNames.size() != pOut) {
    warnings.addWarning(-1, -1,
      tfm::format("%i col names", pOut),
      tfm::format("%i col names", colNames.size()));
  }

  size_t n = (n_max < 0) ? 1000 : n_max;
  collectorsResize(collectors, n);

  size_t i = 0, j = 0, cells = 0;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (progress && (cells++) % 250000 == 0)
      progressBar.show(tokenizer->progress());

    if (t.col() == 0 && i > 0)
      checkColumns(&warnings, i, j, pOut);

    if (t.row() >= n) {
      if (n_max >= 0)
        break;

      // Estimate rows in full dataset
      n = (i / tokenizer->progress().first) * 1.2;
      collectorsResize(collectors, n);
    }

    if (t.col() < p)
      collectors[t.col()]->setValue(t.row(), t);

    i = t.row();
    j = t.col();
  }
  checkColumns(&warnings, i, j, pOut);

  if (progress)
    progressBar.show(tokenizer->progress());
  progressBar.stop();

  if (i <= n) {
    collectorsResize(collectors, i + 1);
  }


  // Save individual columns into a data frame
  List out(pOut);
  j = 0;
  for(CollectorItr cur = collectors.begin(); cur != collectors.end(); ++cur) {
    if ((*cur)->skip())
      continue;

    out[j] = (*cur)->vector();
    j++;
  }

  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -(i + 1));
  out.attr("names") = outNames;

  return warnings.addAsAttribute(out);
}


// [[Rcpp::export]]
std::vector<std::string> collectorsGuess(List sourceSpec, List tokenizerSpec, int n = 100) {
  Warnings warnings;
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings); // silence warnings

  std::vector<CollectorCharacter> collectors;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (t.row() >= (size_t) n)
      break;

    // Add new collectors, if needed
    if (t.col() >= collectors.size()) {
      int old_p = collectors.size();
      collectors.resize(t.col() + 1);
      for (size_t j = old_p; j < collectors.size(); ++j) {
        collectors[j].resize(n);
      }
    }

    collectors[t.col()].setValue(t.row(), t);
  }

  std::vector<std::string> out;
  for (size_t j = 0; j < collectors.size(); ++j) {
    CharacterVector col = as<CharacterVector>(collectors[j].vector());
    out.push_back(collectorGuess(col));
  }

  return out;
}



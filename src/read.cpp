#include <Rcpp.h>
using namespace Rcpp;

#include "LocaleInfo.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Collector.h"
#include "Progress.h"
#include "Warnings.h"
#include "readr_types.h"

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

Function R6method(Environment env, const std::string& method) {
  return as<Function>(env[method]);
}

CharacterVector toCharacterVector(const std::vector<SEXP>& x) {
  CharacterVector out(x.size());
  std::copy(x.begin(), x.end(), out.begin());
  return(out);
}

// [[Rcpp::export]]
CharacterVector read_lines_(List sourceSpec, List locale_, std::vector<std::string> na, Environment callback, int chunk_size = -1, int n_max = -1,
                            bool progress = true) {

  SourcePtr source = Source::create(sourceSpec);
  TokenizerLine tokenizer(na);
  tokenizer.tokenize(source->begin(), source->end());
  LocaleInfo locale(locale_);
  Progress progressBar;

  bool chunked = chunk_size != -1;

  std::vector<SEXP> out;

  R_len_t pos = 1;
  Token t = tokenizer.nextToken();
  bool moreLines = t.type() != TOKEN_EOF;

  while(moreLines && (!chunked || R6method(callback, "continue")())) {
    if (progress && (out.size() + 1) % 25000 == 0)
      progressBar.show(tokenizer.progress());

    out.push_back(t.asSEXP(&locale.encoder_));

    if (chunked && out.size() == chunk_size) {
      R6method(callback, "receive")(toCharacterVector(out), pos);
      pos += out.size();
      out.clear();
    }

    t = tokenizer.nextToken();
    moreLines = t.type() != TOKEN_EOF && (n_max < 0 || out.size() <= n_max);
  }

  if (progress)
    progressBar.show(tokenizer.progress());
  progressBar.stop();

  if (chunked && out.size() > 0) {
    R6method(callback, "receive")(toCharacterVector(out), pos);
    return "";
  } else {
    return(toCharacterVector(out));
  }
}

// [[Rcpp::export]]
List read_lines_raw_(List sourceSpec, int n_max = -1, bool progress = false) {

  SourcePtr source = Source::create(sourceSpec);
  TokenizerLine tokenizer((std::vector<std::string>()));
  tokenizer.tokenize(source->begin(), source->end());
  Progress progressBar;

  R_len_t n = (n_max < 0) ? 10000 : n_max;
  List out(n);

  R_len_t i = 0;
  for (Token t = tokenizer.nextToken(); t.type() != TOKEN_EOF; t = tokenizer.nextToken()) {
    if (progress && (i + 1) % 25000 == 0)
      progressBar.show(tokenizer.progress());

    if (i >= n) {
      if (n_max < 0) {
        // Estimate rows in full dataset
        n = (i / tokenizer.progress().first) * 1.2;
        out = Rf_xlengthgets(out, n);
      } else {
        break;
      }
    }

    if (t.type() == TOKEN_STRING)
      out[i] = t.asRaw();

    ++i;
  }

  if (i < n) {
    out = Rf_xlengthgets(out, i);
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

// Save individual columns into a data frame
List collectorsToDf(std::vector<CollectorPtr>& collectors, const CharacterVector& outNames, int rows) {
  List out(outNames.length());
  int i = 0;
  for(CollectorItr cur = collectors.begin(); cur != collectors.end(); ++cur) {
    if ((*cur)->skip())
      continue;

    out[i] = (*cur)->vector();
    i++;
  }

  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -rows);
  out.attr("names") = outNames;
  return out;
}

// [[Rcpp::export]]
RObject read_tokens_(List sourceSpec, List tokenizerSpec, ListOf<List> colSpecs,
                    CharacterVector colNames, List locale_,
                    Environment callback, int chunk_size = -1, int n_max = -1,
                    bool progress = true) {

  Warnings warnings;
  LocaleInfo locale(locale_);

  SourcePtr source = Source::create(sourceSpec);

  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<CollectorPtr> collectors = collectorsCreate(colSpecs, &locale, &warnings);

  Progress progressBar;

  bool chunked = chunk_size != -1;

  // Work out how many output columns we have
  size_t p = collectors.size();
  size_t pOut = 0;
  for (size_t j = 0; j < p; ++j) {
    if (collectors[j]->skip())
      continue;
    pOut++;
  }

  // Match colNames to with non-skipped collectors
  if (p != (size_t) colNames.size())
    stop("colSpec and colNames must be same size");

  CharacterVector outNames(pOut);
  int cj = 0;
  for (size_t j = 0; j < p; ++j) {
    if (collectors[j]->skip())
      continue;

    outNames[cj] = colNames[j];
    cj++;
  }

  R_len_t n =
    chunked ? chunk_size :
    (n_max < 0) ? 10000 : n_max;

  collectorsResize(collectors, n);

  int i = -1, j = -1, cells = 0;
  int pos = i + 1;
  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF; t = tokenizer->nextToken()) {
    if (progress && (cells++) % 250000 == 0)
      progressBar.show(tokenizer->progress());

    if (t.col() == 0 && i != -1)
      checkColumns(&warnings, i, j, p);

    if (t.row() >= n) {
      if (!chunked) {
        if (n_max >= 0)
          break;

        // Estimate rows in full dataset
        n = (i / tokenizer->progress().first) * 1.2;
        collectorsResize(collectors, n);
      } else {
        if (!R6method(callback, "continue")()) {
          break;
        }
        List out = collectorsToDf(collectors, outNames, i + 1);
        R6method(callback, "receive")(out, pos);
        pos = i + 1;
        i = 0;
      }
    }

    if (t.col() < p)
      collectors[t.col()]->setValue(t.row(), t);

    i = t.row();
    j = t.col();
  }

  if (i != -1)
    checkColumns(&warnings, i, j, p);

  if (progress)
    progressBar.show(tokenizer->progress());
  progressBar.stop();

  if (chunked) {
    if (i != chunk_size) {
      collectorsResize(collectors, i + 1);
    }
    List out = collectorsToDf(collectors, outNames, i + 1);
    as<Function>(callback["receive"])(out, pos);
    return warnings.addAsAttribute(out);
  } else {
    if (i != (int) n - 1) {
      collectorsResize(collectors, i + 1);
    }
  }

  List out = collectorsToDf(collectors, outNames, i + 1);
  return warnings.addAsAttribute(out);
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



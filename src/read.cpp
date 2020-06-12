#include "cpp11/environment.hpp"
#include "cpp11/function.hpp"
#include "cpp11/list.hpp"
#include "cpp11/strings.hpp"

#include "Collector.h"
#include "LocaleInfo.h"
#include "Progress.h"
#include "Reader.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Warnings.h"

[[cpp11::export]] cpp11::strings
read_file_(cpp11::list sourceSpec, cpp11::list locale_) {
  SourcePtr source = Source::create(sourceSpec);
  LocaleInfo locale(locale_);

  return cpp11::writable::strings(
      locale.encoder_.makeSEXP(source->begin(), source->end()));
}

[[cpp11::export]] cpp11::raws read_file_raw_(cpp11::list sourceSpec) {
  SourcePtr source = Source::create(sourceSpec);

  cpp11::writable::raws res(
      static_cast<R_xlen_t>(source->end() - source->begin()));
  std::copy(source->begin(), source->end(), RAW(res));
  return SEXP(res);
}

[[cpp11::export]] cpp11::writable::strings read_lines_(
    cpp11::list sourceSpec,
    cpp11::list locale_,
    std::vector<std::string> na,
    int n_max,
    bool skip_empty_rows,
    bool progress) {

  LocaleInfo locale(locale_);
  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine(na, skip_empty_rows)),
      CollectorPtr(new CollectorCharacter(&locale.encoder_)),
      progress);

  return SEXP(r.readToVector<cpp11::writable::strings>(n_max));
}

cpp11::function
R6method(const cpp11::environment& env, const std::string& method) {
  return static_cast<SEXP>(env[method.c_str()]);
}
bool isTrue(SEXP x) {
  if (!(TYPEOF(x) == LGLSXP && Rf_length(x) == 1)) {
    cpp11::stop("`continue()` must return a length 1 logical vector");
  }
  return LOGICAL(x)[0] == TRUE;
}

[[cpp11::export]] void read_lines_chunked_(
    cpp11::list sourceSpec,
    cpp11::list locale_,
    std::vector<std::string> na,
    int chunkSize,
    cpp11::environment callback,
    bool skip_empty_rows,
    bool progress) {

  LocaleInfo locale(locale_);
  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine(na, skip_empty_rows)),
      CollectorPtr(new CollectorCharacter(&locale.encoder_)),
      progress);

  cpp11::strings out;

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    cpp11::strings out = r.readToVector<cpp11::strings>(chunkSize);
    if (out.size() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.size();
  }

  return;
}

[[cpp11::export]] cpp11::list
read_lines_raw_(cpp11::list sourceSpec, int n_max = -1, bool progress = false) {

  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine()),
      CollectorPtr(new CollectorRaw()),
      progress);

  return r.readToVector<cpp11::list>(n_max);
}

[[cpp11::export]] void read_lines_raw_chunked_(
    cpp11::list sourceSpec,
    int chunkSize,
    cpp11::environment callback,
    bool progress) {

  Reader r(
      Source::create(sourceSpec),
      TokenizerPtr(new TokenizerLine()),
      CollectorPtr(new CollectorRaw()),
      progress);

  cpp11::list out;

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    cpp11::list out = r.readToVector<cpp11::list>(chunkSize);
    if (out.size() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.size();
  }

  return;
}

typedef std::vector<CollectorPtr>::iterator CollectorItr;

[[cpp11::export]] cpp11::sexp read_tokens_(
    cpp11::list sourceSpec,
    cpp11::list tokenizerSpec,
    cpp11::list colSpecs,
    cpp11::strings colNames,
    cpp11::list locale_,
    int n_max,
    bool progress) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress,
      colNames);

  return r.readToDataFrame(n_max);
}

[[cpp11::export]] void read_tokens_chunked_(
    cpp11::list sourceSpec,
    cpp11::environment callback,
    int chunkSize,
    cpp11::list tokenizerSpec,
    cpp11::list colSpecs,
    cpp11::strings colNames,
    cpp11::list locale_,
    bool progress) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress,
      colNames);

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    cpp11::data_frame out(r.readToDataFrame(chunkSize));
    if (out.nrow() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.nrow();
  }

  return;
}

[[cpp11::export]] cpp11::sexp melt_tokens_(
    cpp11::list sourceSpec,
    cpp11::list tokenizerSpec,
    cpp11::list colSpecs,
    cpp11::list locale_,
    int n_max,
    bool progress) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress);

  return r.meltToDataFrame(cpp11::list(locale_), n_max);
}

[[cpp11::export]] void melt_tokens_chunked_(
    cpp11::list sourceSpec,
    cpp11::environment callback,
    int chunkSize,
    cpp11::list tokenizerSpec,
    cpp11::list colSpecs,
    cpp11::list locale_,
    bool progress) {

  LocaleInfo l(locale_);
  Reader r(
      Source::create(sourceSpec),
      Tokenizer::create(tokenizerSpec),
      collectorsCreate(colSpecs, &l),
      progress);

  int pos = 1;
  while (isTrue(R6method(callback, "continue")())) {
    cpp11::data_frame out(
        r.meltToDataFrame(static_cast<SEXP>(locale_), chunkSize));
    if (out.nrow() == 0) {
      return;
    }
    R6method(callback, "receive")(out, pos);
    pos += out.nrow();
  }

  return;
}

[[cpp11::export]] std::vector<std::string> guess_types_(
    cpp11::list sourceSpec,
    cpp11::list tokenizerSpec,
    cpp11::list locale_,
    int n) {
  Warnings warnings;
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
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
    cpp11::strings col(collectors[j]->vector());
    out.push_back(collectorGuess(SEXP(col), cpp11::list(locale_)));
  }

  return out;
}

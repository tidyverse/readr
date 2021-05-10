#include "cpp11/R.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"
#include "cpp11/sexp.hpp"
#include <memory>

#include "Collector.h"
#include "LocaleInfo.h"
#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerLine.h"
#include "Warnings.h"

[[cpp11::register]] cpp11::integers
dim_tokens_(const cpp11::list& sourceSpec, const cpp11::list& tokenizerSpec) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  int rows = -1;

  int cols = -1;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    rows = t.row();

    if ((int)t.col() > cols) {
      cols = t.col();
    }
  }

  cpp11::writable::integers out(rows + 1);
  for (auto&& x : out) {
    x = cols + 1;
  }
  return out;
}

[[cpp11::register]] std::vector<int> count_fields_(
    const cpp11::list& sourceSpec,
    const cpp11::list& tokenizerSpec,
    int n_max) {
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());

  std::vector<int> fields;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t)n_max) {
      break;
    }

    if (t.row() >= fields.size()) {
      fields.resize(t.row() + 1);
    }

    fields[t.row()] = t.col() + 1;
  }

  return fields;
}

[[cpp11::register]] cpp11::list guess_header_(
    const cpp11::list& sourceSpec,
    const cpp11::list& tokenizerSpec,
    const cpp11::list& locale_) {
  Warnings warnings;
  LocaleInfo locale(locale_);
  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  CollectorCharacter out(&locale.encoder_);
  out.setWarnings(&warnings);
  Token t = tokenizer->nextToken();
  size_t row_num = t.row();

  size_t max_size = 0;
  size_t capacity = 0;

  for (; t.type() != TOKEN_EOF && t.row() == row_num;
       t = tokenizer->nextToken()) {
    if (t.col() >= max_size) {
      max_size = t.col();
    }

    if (max_size >= capacity) {
      capacity = (max_size + 1) * 2;
      out.resize(capacity);
    }

    if (t.type() == TOKEN_STRING) {
      out.setValue(t.col(), t);
    }
  }

  out.resize(max_size + 1);

  using namespace cpp11::literals;
  return cpp11::writable::list(
      {"header"_nm = out.vector(), "skip"_nm = source->skippedRows() + 1});
}

[[cpp11::register]] SEXP tokenize_(
    const cpp11::list& sourceSpec,
    const cpp11::list& tokenizerSpec,
    int n_max) {
  Warnings warnings;

  SourcePtr source = Source::create(sourceSpec);
  TokenizerPtr tokenizer = Tokenizer::create(tokenizerSpec);
  tokenizer->tokenize(source->begin(), source->end());
  tokenizer->setWarnings(&warnings);

  std::vector<std::vector<std::string>> rows;

  for (Token t = tokenizer->nextToken(); t.type() != TOKEN_EOF;
       t = tokenizer->nextToken()) {
    if (n_max > 0 && t.row() >= (size_t)n_max) {
      break;
    }

    if (t.row() >= rows.size()) {
      rows.resize(t.row() + 1);
    }

    std::vector<std::string>& row = rows[t.row()];
    if (t.col() >= row.size()) {
      row.resize(t.col() + 1);
    }

    row[t.col()] = t.asString();
  }

  cpp11::writable::list out;
  out.reserve(rows.size());

  for (auto&& row : rows) {
    cpp11::sexp row_data(cpp11::as_sexp(row));
    out.push_back(row_data);
  }

  return warnings.addAsAttribute(out);
}

[[cpp11::register]] SEXP parse_vector_(
    const cpp11::strings& x,
    const cpp11::list& collectorSpec,
    const cpp11::list& locale_,
    const std::vector<std::string>& na,
    bool trim_ws) {
  Warnings warnings;
  int n = x.size();

  LocaleInfo locale(locale_);

  std::shared_ptr<Collector> col(Collector::create(collectorSpec, &locale));
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

  return warnings.addAsAttribute(static_cast<SEXP>(col->vector()));
}

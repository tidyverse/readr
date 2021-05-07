#include "Reader.h"

#include "cpp11/function.hpp"
#include "cpp11/list.hpp"

#include <sstream>
#include <utility>

Reader::Reader(
    SourcePtr source,
    TokenizerPtr tokenizer,
    std::vector<CollectorPtr> collectors,
    bool progress,
    const cpp11::strings& colNames)
    : source_(std::move(source)),
      tokenizer_(std::move(tokenizer)),
      collectors_(std::move(collectors)),
      progress_(progress),
      begun_(false) {
  init(colNames);
}

Reader::Reader(
    SourcePtr source,
    TokenizerPtr tokenizer,
    const CollectorPtr& collector,
    bool progress,
    const cpp11::strings& colNames)
    : source_(std::move(source)),
      tokenizer_(std::move(tokenizer)),
      progress_(progress),
      begun_(false) {

  collectors_.push_back(collector);
  init(colNames);
}

void Reader::init(const cpp11::strings& colNames) {
  tokenizer_->tokenize(source_->begin(), source_->end());
  tokenizer_->setWarnings(&warnings_);

  // Work out which output columns we are keeping and set warnings for each
  // collector
  size_t p = collectors_.size();
  for (size_t j = 0; j < p; ++j) {
    if (!collectors_[j]->skip()) {
      keptColumns_.push_back(j);
      collectors_[j]->setWarnings(&warnings_);
    }
  }

  if (colNames.size() > 0) {
    outNames_ = cpp11::writable::strings(keptColumns_.size());
    int i = 0;
    for (std::vector<int>::const_iterator it = keptColumns_.begin();
         it != keptColumns_.end();
         ++it) {
      outNames_[i++] = colNames[*it];
    }
  }
}

cpp11::sexp Reader::readToDataFrame(R_xlen_t lines) {
  R_xlen_t rows = read(lines);

  // Save individual columns into a data frame
  cpp11::writable::list out(outNames_.size());
  R_xlen_t j = 0;
  for (std::vector<int>::const_iterator it = keptColumns_.begin();
       it != keptColumns_.end();
       ++it) {
    out[j++] = collectors_[*it]->vector();
  }

  cpp11::sexp out2(warnings_.addAsAttribute(static_cast<SEXP>(out)));

  out2.attr("names") = outNames_;
  out2.attr("class") = {"spec_tbl_df", "tbl_df", "tbl", "data.frame"};
  out2.attr("row.names") = {NA_REAL, -(static_cast<double>(rows + 1))};

  collectorsClear();
  warnings_.clear();

  // TODO: call tibble name repair function when tibble 1.5.0 is released.

  return out2;
}

R_xlen_t Reader::read(R_xlen_t lines) {

  if (t_.type() == TOKEN_EOF) {
    return (-1);
  }

  R_xlen_t n = (lines < 0) ? 1000 : lines;

  collectorsResize(n);

  R_xlen_t last_row = -1;

  R_xlen_t last_col = -1;

  R_xlen_t cells = 0;
  R_xlen_t first_row;
  if (!begun_) {
    t_ = tokenizer_->nextToken();
    begun_ = true;
    first_row = 0;
  } else {
    first_row = t_.row();
  }

  while (t_.type() != TOKEN_EOF) {

    if (progress_ && (++cells) % progressStep_ == 0) {
      progressBar_.show(tokenizer_->progress());
    }

    if (t_.col() == 0 && static_cast<R_xlen_t>(t_.row()) != first_row) {
      checkColumns(last_row, last_col, collectors_.size());
    }

    if (lines >= 0 && static_cast<R_xlen_t>(t_.row()) - first_row >= lines) {
      break;
    }

    if (static_cast<R_xlen_t>(t_.row()) - first_row >= n) {
      // Estimate rows in full dataset and resize collectors
      n = ((t_.row() - first_row) / tokenizer_->progress().first) * 1.1;
      collectorsResize(n);
    }

    // only set value if within the expected number of columns
    if (t_.col() < collectors_.size()) {
      collectors_[t_.col()]->setValue(t_.row() - first_row, t_);
    }

    last_row = t_.row();
    last_col = t_.col();
    t_ = tokenizer_->nextToken();
  }

  if (last_row != -1) {
    checkColumns(last_row, last_col, collectors_.size());
  }

  if (progress_) {
    progressBar_.show(tokenizer_->progress());
  }

  progressBar_.stop();

  // Resize the collectors to the final size (if it is not already at that
  // size)
  if (last_row == -1) {
    collectorsResize(0);
  } else if ((last_row - first_row) < (n - 1)) {
    collectorsResize((last_row - first_row) + 1);
  }

  return last_row - first_row;
}

void Reader::checkColumns(int i, int j, int n) {
  if (j + 1 == n) {
    return;
  }

  std::stringstream ss1;
  ss1 << n << " columns";

  std::stringstream ss2;
  ss2 << j + 1 << " columns";
  warnings_.addWarning(i, -1, ss1.str(), ss2.str());
}

void Reader::collectorsResize(R_xlen_t n) {
  for (size_t j = 0; j < collectors_.size(); ++j) {
    collectors_[j]->resize(n);
  }
}

void Reader::collectorsClear() {
  for (size_t j = 0; j < collectors_.size(); ++j) {
    collectors_[j]->clear();
  }
}

cpp11::sexp
Reader::meltToDataFrame(const cpp11::list& locale_, R_xlen_t lines) {
  melt(locale_, lines);

  // Save individual columns into a data frame
  cpp11::writable::list out(4);
  out[0] = collectors_[0]->vector();
  out[1] = collectors_[1]->vector();
  out[2] = collectors_[2]->vector();
  out[3] = collectors_[3]->vector();

  out.attr("names") = {"row", "col", "data_type", "value"};
  cpp11::sexp out2(warnings_.addAsAttribute(static_cast<SEXP>(out)));

  collectorsClear();
  warnings_.clear();

  out.attr("names") = {"row", "col", "data_type", "value"};

  static cpp11::function as_tibble = cpp11::package("tibble")["as_tibble"];
  return as_tibble(out);
}

R_xlen_t Reader::melt(const cpp11::list& locale_, R_xlen_t lines) {

  if (t_.type() == TOKEN_EOF) {
    return (-1);
  }

  R_xlen_t n = (lines < 0) ? 10000 : lines * 10; // Start with 10 cells per line

  collectorsResize(n);

  R_xlen_t last_row = -1;

  R_xlen_t cells = 0;
  R_xlen_t first_row;
  if (!begun_) {
    t_ = tokenizer_->nextToken();
    begun_ = true;
    first_row = 0;
  } else {
    first_row = t_.row();
  }

  while (t_.type() != TOKEN_EOF) {
    ++cells;

    if (progress_ && cells % progressStep_ == 0) {
      progressBar_.show(tokenizer_->progress());
    }

    if (lines >= 0 && static_cast<R_xlen_t>(t_.row()) - first_row >= lines) {
      --cells;
      break;
    }

    if (cells >= n) {
      // Estimate rows in full dataset and resize collectors
      n = (cells / tokenizer_->progress().first) * 1.1;
      collectorsResize(n);
    }

    collectors_[0]->setValue(cells - 1, t_.row() + 1);
    collectors_[1]->setValue(cells - 1, t_.col() + 1);
    collectors_[3]->setValue(cells - 1, t_);

    switch (t_.type()) {
    case TOKEN_STRING: {
      cpp11::sexp str(cpp11::as_sexp(t_.asString()));
      collectors_[2]->setValue(
          cells - 1, collectorGuess(SEXP(str), locale_, true));
      break;
    };
    case TOKEN_MISSING:
      collectors_[2]->setValue(cells - 1, "missing");
      break;
    case TOKEN_EMPTY:
      collectors_[2]->setValue(cells - 1, "empty");
      break;
    case TOKEN_EOF:
      cpp11::stop("Invalid token");
    }

    last_row = t_.row();
    t_ = tokenizer_->nextToken();
  }

  if (progress_) {
    progressBar_.show(tokenizer_->progress());
  }

  progressBar_.stop();

  // Resize the collectors to the final size (if it is not already at that
  // size)
  if (last_row == -1) {
    collectorsResize(0);
  } else if (cells < (n - 1)) {
    collectorsResize(cells);
  }

  return cells - 1;
}

#include "Reader.h"

Reader::Reader(SourcePtr source, TokenizerPtr tokenizer, std::vector<CollectorPtr> collectors,
        bool progress, LocaleInfo* locale, CharacterVector colNames) :
  source_(source),
  tokenizer_(tokenizer),
  collectors_(collectors),
  progress_(progress),
  locale_(locale) {
    init(colNames);
}

Reader::Reader(SourcePtr source, TokenizerPtr tokenizer,
    CollectorPtr collector, bool progress, LocaleInfo* locale, CharacterVector colNames) :
  source_(source),
  tokenizer_(tokenizer),
  progress_(progress),
  locale_(locale) {

  collectors_.push_back(collector);
  init(colNames);
}

void Reader::init(CharacterVector colNames) {
  tokenizer_->tokenize(source_->begin(), source_->end());
  tokenizer_->setWarnings(&warnings_);

  // Work out which output columns we are keeping and set the locale for each collectors
  size_t p = collectors_.size();
  for (size_t j = 0; j < p; ++j) {
    if (!collectors_[j]->skip()) {
      keptColumns_.push_back(j);
      collectors_[j]->setWarnings(&warnings_);
    }
  }

  if (colNames.size() > 0) {
    outNames_ = CharacterVector(keptColumns_.size());
    int i = 0;
    for (std::vector<int>::const_iterator it = keptColumns_.begin(); it != keptColumns_.end(); ++it) {
      outNames_[i++] = colNames[*it];
    }
  }
}

RObject Reader::readToDataFrame(int lines) {
  int rows = read(lines);

  // Save individual columns into a data frame
  List out(outNames_.size());
  int j = 0;
  for (std::vector<int>::const_iterator it = keptColumns_.begin(); it != keptColumns_.end(); ++it) {
    out[j++] = collectors_[*it]->vector();
  }

  out.attr("class") = CharacterVector::create("tbl_df", "tbl", "data.frame");
  out.attr("row.names") = IntegerVector::create(NA_INTEGER, -(rows + 1));
  out.attr("names") = outNames_;

  return warnings_.addAsAttribute(out);
}

int Reader::read(int lines) {

  int n = (lines < 0) ? 1000 : lines;

  collectorsResize(collectors_, n);

  int last_row = -1, last_col = -1, cells = 0;
  for (Token t = tokenizer_->nextToken(); t.type() != TOKEN_EOF; t = tokenizer_->nextToken()) {
    if (progress_ && (++cells) % progressStep_ == 0) {
      progressBar_.show(tokenizer_->progress());
    }

    if (t.col() == 0 && last_row > -1) {
      checkColumns(last_row, last_col, collectors_.size());
    }

    if (lines >= 0 && t.row() >= lines) {
      break;
    }

    if (t.row() >= n) {
      // Estimate rows in full dataset and resize collectors
      n = (last_row / tokenizer_->progress().first) * 1.1;
      collectorsResize(collectors_, n);
    }

    // only set value if within the expected number of columns
    if (t.col() < collectors_.size()) {
      collectors_[t.col()]->setValue(t.row(), t);
    }

    last_row = t.row();
    last_col = t.col();
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
  if (last_row < n - 1) {
    collectorsResize(collectors_, last_row + 1);
  }

  return last_row;
}

void Reader::checkColumns(int i, int j, int n) {
  if (j + 1 == n)
    return;

  warnings_.addWarning(i, -1,
      tfm::format("%i columns", n),
      tfm::format("%i columns", j + 1)
      );
}

#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerFwf.h"
#include "utils.h"

struct skip_t {
  SourceIterator begin;
  int lines;
};

skip_t skipComments(SourcePtr source) {
  skip_t out;
  if (!source->has_comments()) {
    out.begin = source->begin();
    out.lines = 0;
    return out;
  }

  SourceIterator cur = source->begin();
  size_t skip = source->skipComments(&cur);
  out.begin = cur;
  out.lines = skip;
  return out;
}

std::vector<bool> emptyCols_(SourcePtr source, int n, SourceIterator begin) {
  SourceIterator end = source->end();
  std::vector<bool> is_white;

  size_t row = 0, col = 0;
  for (SourceIterator cur = begin; cur != end; ++cur) {
    if (row > n)
      break;

    if (col == 0) {
      source->skipComments(&cur);
    }
    if (cur == end) {
      break;
    }

    switch (*cur) {
    case '\n':
    case '\r':
      advanceForLF(&cur, end);
      col = 0;
      row++;
      break;
    case ' ':
      col++;
      break;
    default:
      // Make sure there's enough room
      if (col >= is_white.size())
        is_white.resize(col + 1, true);
      is_white[col] = false;
      col++;
    }
  }

  return is_white;
}

// [[Rcpp::export]]
List whitespaceColumns(List sourceSpec, int n = 100) {
  SourcePtr source = Source::create(sourceSpec);

  skip_t s = skipComments(source);

  std::vector<bool> empty = emptyCols_(source, n, s.begin);
  std::vector<int> begin, end;

  bool in_col = false;

  for (size_t i = 0; i < empty.size(); ++i) {
    if (in_col && empty[i]) {
      end.push_back(i);
      in_col = false;
    } else if (!in_col && !empty[i]) {
      begin.push_back(i);
      in_col = true;
    }
  }

  if (in_col)
    end.push_back(empty.size());

  return List::create(_["begin"] = begin, _["end"] = end);
}

  // TokenizerFwf
  // ---------------------------------------------------------------

#include "TokenizerFwf.h"
#include <Rcpp.h>

TokenizerFwf::TokenizerFwf(
    const std::vector<int>& beginOffset,
    const std::vector<int>& endOffset,
    std::vector<std::string> NA,
    bool trimWS)
    : beginOffset_(beginOffset),
      endOffset_(endOffset),
      NA_(NA),
      cols_(beginOffset.size()),
      moreTokens_(false),
      trimWS_(trimWS) {
  if (beginOffset_.size() != endOffset_.size())
    Rcpp::stop(
        "Begin (%i) and end (%i) specifications must have equal length",
        beginOffset_.size(),
        endOffset_.size());

  if (beginOffset_.size() == 0)
    Rcpp::stop("Zero-length begin and end specifications not supported");

  // File is assumed to be ragged (last column can have variable width)
  // when the last element of endOffset_ is NA
  isRagged_ = endOffset_[endOffset_.size() - 1L] == NA_INTEGER;

  max_ = 0;
  for (int j = 0; j < (cols_ - isRagged_); ++j) {
    if (endOffset_[j] <= beginOffset_[j])
      Rcpp::stop(
          "Begin offset (%i) must be smaller than end offset (%i)",
          beginOffset_[j],
          endOffset_[j]);

    if (beginOffset_[j] < max_) {
      Rcpp::stop(
          "Overlapping specification not supported. "
          "Begin offset (%i) must be greater than or equal to previous "
          "end offset (%i)",
          beginOffset_[j],
          max_);
    }

    if (endOffset_[j] > max_) {
      max_ = endOffset_[j];
    }
  }
}

void TokenizerFwf::tokenize(SourcePtr source) {
  cur_ = source->begin();
  curLine_ = source->begin();

  begin_ = source->begin();
  end_ = source->end();
  source_ = source;

  row_ = 0;
  col_ = 0;
  moreTokens_ = true;
}

std::pair<double, size_t> TokenizerFwf::progress() {
  size_t bytes = cur_ - begin_;
  return std::make_pair(bytes / (double)(end_ - begin_), bytes);
}

Token TokenizerFwf::nextToken() {
  if (!moreTokens_)
    return Token(TOKEN_EOF, 0, 0);

  // Check for comments and empty lines (only at start of line)
  if (col_ == 0) {
    source_->skipCommentAndEmptyLines(&cur_);
    curLine_ = cur_;
  }

  // Find start of field
  SourceIterator fieldBegin = cur_;
findBeginning:
  int skip = beginOffset_[col_] - (cur_ - curLine_);
  for (int i = 0; i < skip; ++i) {
    if (fieldBegin == end_)
      break;

    if (*fieldBegin == '\n' || *fieldBegin == '\r') {
      warn(
          row_,
          col_,
          tfm::format("%i chars between fields", skip),
          tfm::format("%i chars until end of line", i));

      row_++;
      col_ = 0;

      advanceForLF(&fieldBegin, end_);
      if (fieldBegin != end_)
        fieldBegin++;
      cur_ = curLine_ = fieldBegin;
      goto findBeginning;
    }
    fieldBegin++;
  }

  if (fieldBegin == end_) {
    // need to warn here if col != 0/cols - 1
    moreTokens_ = false;
    return Token(TOKEN_EOF, 0, 0);
  }

  // Find end of field
  SourceIterator fieldEnd = fieldBegin;
  bool lastCol = (col_ == cols_ - 1), tooShort = false, hasNull = false;

  if (lastCol && isRagged_) {
    // Last column is ragged, so read until end of line (ignoring width)
    while (fieldEnd != end_ && *fieldEnd != '\r' && *fieldEnd != '\n') {
      if (*fieldEnd == '\0')
        hasNull = true;
      fieldEnd++;
    }
  } else {
    int width = endOffset_[col_] - beginOffset_[col_];
    // Find the end of the field, stopping for newlines
    for (int i = 0; i < width; ++i) {
      if (fieldEnd == end_ || *fieldEnd == '\n' || *fieldEnd == '\r') {
        warn(row_, col_, tfm::format("%i chars", width), tfm::format("%i", i));

        tooShort = true;
        break;
      }
      if (*fieldEnd == '\0')
        hasNull = true;

      fieldEnd++;
    }
  }

  Token t = fieldToken(fieldBegin, fieldEnd, hasNull);

  if (lastCol || tooShort) {
    row_++;
    col_ = 0;

    if (!(tooShort || isRagged_)) {
      // Proceed to the end of the line when you are possibly not there.
      // This is needed in case the last column in the file is not being read.
      while (fieldEnd != end_ && *fieldEnd != '\r' && *fieldEnd != '\n') {
        if (*fieldEnd == '\0')
          hasNull = true;
        fieldEnd++;
      }
    }

    curLine_ = fieldEnd;
    advanceForLF(&curLine_, end_);
    if (curLine_ != end_)
      curLine_++;
    cur_ = curLine_;
  } else {
    col_++;
    cur_ = fieldEnd;
  }

  return t;
}

Token TokenizerFwf::fieldToken(
    SourceIterator begin, SourceIterator end, bool hasNull) {
  if (begin == end)
    return Token(TOKEN_MISSING, row_, col_);

  Token t = Token(begin, end, row_, col_, hasNull);
  if (trimWS_) {
    t.trim();
  }
  t.flagNA(NA_);

  return t;
}

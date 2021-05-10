#include "cpp11/list.hpp"
#include "cpp11/protect.hpp"

#include "Tokenizer.h"
#include "TokenizerFwf.h"
#include "utils.h"

#include "Source.h"

#include <sstream>
#include <utility>

struct skip_t {
  SourceIterator begin;
  int lines;
};

skip_t skip_comments(
    SourceIterator begin, SourceIterator end, const std::string& comment = "") {
  skip_t out;
  if (comment.length() == 0) {
    out.begin = begin;
    out.lines = 0;
    return out;
  }

  SourceIterator cur = begin;
  int skip = 0;
  while (starts_with_comment(cur, end, comment)) {
    // Skip rest of line
    while (cur != end && *cur != '\n' && *cur != '\r') {
      ++cur;
    }

    advanceForLF(&cur, end);
    ++cur;
    ++skip;
  }

  out.begin = cur;
  out.lines = skip;
  return out;
}

std::vector<bool>
emptyCols_(SourceIterator begin, SourceIterator end, size_t n = 100) {

  std::vector<bool> is_white;

  size_t row = 0;

  size_t col = 0;
  for (SourceIterator cur = begin; cur != end; ++cur) {
    if (row > n) {
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
      if (col >= is_white.size()) {
        is_white.resize(col + 1, true);
      }
      is_white[col] = false;
      col++;
    }
  }

  return is_white;
}

[[cpp11::register]] cpp11::list
whitespaceColumns(const cpp11::list& sourceSpec, int n, std::string comment) {
  SourcePtr source = Source::create(sourceSpec);

  skip_t s = skip_comments(source->begin(), source->end(), std::move(comment));

  std::vector<bool> empty = emptyCols_(s.begin, source->end(), n);
  std::vector<int> begin;

  std::vector<int> end;

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

  if (in_col) {
    end.push_back(empty.size());
  }

  using namespace cpp11::literals;
  return cpp11::writable::list(
      {"begin"_nm = begin, "end"_nm = end, "skip"_nm = s.lines});
}

// TokenizerFwf --------------------------------------------------------------

#include "TokenizerFwf.h"

TokenizerFwf::TokenizerFwf(
    const std::vector<int>& beginOffset,
    const std::vector<int>& endOffset,
    std::vector<std::string> NA,
    const std::string& comment,
    bool trimWS,
    bool skipEmptyRows)
    : beginOffset_(beginOffset),
      endOffset_(endOffset),
      NA_(std::move(NA)),
      cols_(beginOffset.size()),
      comment_(comment),
      moreTokens_(false),
      hasComment_(!comment.empty()),
      trimWS_(trimWS),
      skipEmptyRows_(skipEmptyRows) {
  if (beginOffset_.size() != endOffset_.size()) {
    cpp11::stop(
        "Begin (%i) and end (%i) specifications must have equal length",
        beginOffset_.size(),
        endOffset_.size());
  }

  if (beginOffset_.empty()) {
    cpp11::stop("Zero-length begin and end specifications not supported");
  }

  // File is assumed to be ragged (last column can have variable width)
  // when the last element of endOffset_ is NA
  isRagged_ = endOffset_[endOffset_.size() - 1L] == NA_INTEGER;

  max_ = 0;
  for (int j = 0; j < (cols_ - static_cast<int>(isRagged_)); ++j) {
    if (endOffset_[j] <= beginOffset_[j]) {
      cpp11::stop(
          "Begin offset (%i) must be smaller than end offset (%i)",
          beginOffset_[j],
          endOffset_[j]);
    }

    if (beginOffset_[j] < 0) {
      cpp11::stop("Begin offset (%i) must be greater than 0", beginOffset_[j]);
    }

    if (endOffset_[j] < 0) {
      cpp11::stop("End offset (%i) must be greater than 0", endOffset_[j]);
    }

    if (endOffset_[j] > max_) {
      max_ = endOffset_[j];
    }
  }
}

void TokenizerFwf::tokenize(SourceIterator begin, SourceIterator end) {
  cur_ = begin;
  curLine_ = begin;

  begin_ = begin;
  end_ = end;

  row_ = 0;
  col_ = 0;
  moreTokens_ = true;
}

std::pair<double, size_t> TokenizerFwf::progress() {
  size_t bytes = cur_ - begin_;
  return std::make_pair(bytes / (double)(end_ - begin_), bytes);
}

Token TokenizerFwf::nextToken() {
  if (!moreTokens_) {
    return {TOKEN_EOF, 0, 0};
  }

  // Check for comments only at start of line
  while (cur_ != end_ && col_ == 0 &&
         (isComment(cur_) || (isEmpty() && skipEmptyRows_))) {
    // Skip rest of line
    while (cur_ != end_ && *cur_ != '\n' && *cur_ != '\r') {
      ++cur_;
    }
    advanceForLF(&cur_, end_);
    if (cur_ != end_) {
      ++cur_;
    }
    curLine_ = cur_;
  }

  // Find start of field
  SourceIterator fieldBegin = cur_;
findBeginning:
  int skip = beginOffset_[col_] - (cur_ - curLine_);
  if (skip < 0) { // overlapping case
    fieldBegin += skip;
  } else if (skip > 0) { // skipped columns case
    for (int i = 0; i < skip; ++i) {
      if (fieldBegin == end_) {
        break;
      }

      if (*fieldBegin == '\n' || *fieldBegin == '\r') {
        std::stringstream ss1;
        ss1 << skip << " chars betwen fields";
        std::stringstream ss2;
        ss2 << skip << " chars until end of line";
        warn(row_, col_, ss1.str(), ss2.str());

        row_++;
        col_ = 0;

        advanceForLF(&fieldBegin, end_);
        if (fieldBegin != end_) {
          fieldBegin++;
        }
        cur_ = curLine_ = fieldBegin;
        goto findBeginning;
      }
      fieldBegin++;
    }
  }

  if (fieldBegin == end_) {
    // need to warn here if col != 0/cols - 1
    moreTokens_ = false;
    return {TOKEN_EOF, 0, 0};
  }

  // Find end of field
  SourceIterator fieldEnd = fieldBegin;
  bool lastCol = (col_ == cols_ - 1);

  bool tooShort = false;

  bool hasNull = false;

  if (lastCol && isRagged_) {
    // Last column is ragged, so read until end of line (ignoring width)
    while (fieldEnd != end_ && *fieldEnd != '\r' && *fieldEnd != '\n') {
      if (*fieldEnd == '\0') {
        hasNull = true;
      }
      fieldEnd++;
    }
  } else {
    int width = endOffset_[col_] - beginOffset_[col_];
    // Find the end of the field, stopping for newlines
    for (int i = 0; i < width; ++i) {
      if (fieldEnd == end_ || *fieldEnd == '\n' || *fieldEnd == '\r') {
        if (!(col_ == 0 && !skipEmptyRows_)) {
          std::stringstream ss1;
          ss1 << i << " chars";
          std::stringstream ss2;
          ss2 << i;
          warn(row_, col_, ss1.str(), ss2.str());
        }

        tooShort = true;
        break;
      }
      if (*fieldEnd == '\0') {
        hasNull = true;
      }

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
        fieldEnd++;
      }
    }

    curLine_ = fieldEnd;
    advanceForLF(&curLine_, end_);
    if (curLine_ != end_) {
      curLine_++;
    }
    cur_ = curLine_;
  } else {
    col_++;
    cur_ = fieldEnd;
  }

  return t;
}

Token TokenizerFwf::fieldToken(
    SourceIterator begin, SourceIterator end, bool hasNull) {
  if (begin == end) {
    return {TOKEN_MISSING, row_, col_};
  }

  Token t = Token(begin, end, row_, col_, hasNull);
  if (trimWS_) {
    t.trim();
  }
  t.flagNA(NA_);

  return t;
}

bool TokenizerFwf::isComment(const char* cur) const {
  if (!hasComment_) {
    return false;
  }

  return starts_with_comment(cur, end_, comment_);
}

bool TokenizerFwf::isEmpty() const {
  return cur_ == end_ || *cur_ == '\r' || *cur_ == '\n';
}

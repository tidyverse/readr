#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerFwf.h"
#include "utils.h"

std::vector<bool> emptyCols_(SourceIterator begin, SourceIterator end, size_t n = 100) {

  std::vector<bool> is_white;

  size_t row = 0, col = 0;
  for (SourceIterator cur = begin; cur != end; ++cur) {
    if (row > n)
      break;

    switch(*cur) {
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

  std::vector<bool> empty = emptyCols_(source->begin(), source->end(), n);
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

  return List::create(
    _["begin"] = begin,
    _["end"] = end
  );
}

// TokenizerFwf ---------------------------------------------------------------

#include <Rcpp.h>
#include "TokenizerFwf.h"

TokenizerFwf::TokenizerFwf(const std::vector<int>& beginOffset, const std::vector<int>& endOffset,
                           std::vector<std::string> NA):
  beginOffset_(beginOffset),
  endOffset_(endOffset),
  NA_(NA),
  cols_(beginOffset.size()),
  moreTokens_(false)
{
  // File is assumed to be ragged (last column can have variable width)
  // when length of end vector is one shorter then begin vector.
  isRagged_ = beginOffset_.size()==(endOffset_.size()+1L);

  if (!isRagged_ && (beginOffset_.size() != endOffset_.size()))
    Rcpp::stop("Begin (%i) and end (%i) specifications must have equal length",
      beginOffset_.size(), endOffset_.size());

  max_ = 0;
  for (int j = 0; j < (cols_-isRagged_); ++j) {
    if (endOffset_[j] <= beginOffset_[j])
      Rcpp::stop("Begin offset (%i) must be smaller than end offset (%i)",
        beginOffset_[j], endOffset_[j]);

    if (endOffset_[j] > max_)
      max_ = endOffset_[j];
  }
}

void TokenizerFwf::tokenize(SourceIterator begin, SourceIterator end) {
  curLine_ = begin;
  begin_ = begin;
  end_ = end;

  row_ = 0;
  col_ = 0;
  moreTokens_ = true;
}

std::pair<double,size_t> TokenizerFwf::progress() {
  size_t bytes = curLine_ - begin_;
  return std::make_pair(bytes / (double) (end_ - begin_), bytes);
}

// bool advance(SourceIterator start, SourceIterator end, int n) {
//   for(int i = 0; i < n; ++i) {
//     start++;
//     if (start == end)
//       return false;
//
//     if (*start == '\r' || *start == '\n')
//       return false;
//   }
//
//   return true;
// }

Token TokenizerFwf::nextToken() {
  if (!moreTokens_)
    return Token(TOKEN_EOF, 0, 0);

  SourceIterator fieldBegin = curLine_ + beginOffset_[col_];
  if (fieldBegin >= end_) {
    moreTokens_ = false;
    return Token(TOKEN_EOF, 0, 0);
  }

  SourceIterator fieldEnd = fieldBegin;
  bool lastCol = (col_ == cols_ - 1), tooShort = false, hasNull = false;

  if (lastCol && isRagged_) {
    // Last column is ragged, so read until end of line (ignoring width)
    if (lastCol) {
      while(fieldEnd != end_ && *fieldEnd != '\r' && *fieldEnd != '\n') {
        if (*fieldEnd == '\0')
          hasNull = true;
        fieldEnd++;
      }
    }
  } else {
    int width = endOffset_[col_] - beginOffset_[col_];
    // Find the end of the field, stopping for newlines
    for(int i = 0; i < width; ++i) {
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

    // Proceed to the end of the line. This is needed in case the last column
    // in the file is not being read.
    while(fieldEnd != end_ && *fieldEnd != '\r' && *fieldEnd != '\n') {
      if (*fieldEnd == '\0')
        hasNull = true;
      fieldEnd++;
    }

    curLine_ = fieldEnd;
    advanceForLF(&curLine_, end_);
    if (curLine_ != end_)
      curLine_++;
  } else {
    col_++;
  }

  return t;
}

Token TokenizerFwf::fieldToken(SourceIterator begin, SourceIterator end, bool hasNull) {
  if (begin == end)
    return Token(TOKEN_MISSING, row_, col_);

  Token t = Token(begin, end, row_, col_, hasNull);
  t.trim();
  t.flagNA(NA_);

  return t;
}


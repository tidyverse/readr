#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

class TokenizerFwf : public Tokenizer {
  // Begin and end offsets are inclusive to match R conventions
  std::vector<int> beginOffset_, endOffset_;
  std::vector<std::string> NA_;

  SourceIterator begin_, curLine_, end_;
  int row_, col_, cols_, max_;
  bool moreTokens_;

public:

  TokenizerFwf(const std::vector<int>& beginOffset, const std::vector<int>& endOffset,
               std::vector<std::string> NA = std::vector<std::string>(1, "NA")):
    beginOffset_(beginOffset),
    endOffset_(endOffset),
    NA_(NA),
    cols_(beginOffset.size()),
    moreTokens_(false)
  {
    if (beginOffset_.size() != endOffset_.size())
      Rcpp::stop("Begin (%i) and end (%i) specifications must have equal length",
        beginOffset_.size(), endOffset_.size());

    max_ = 0;
    for (int j = 0; j < cols_; ++j) {
      if (endOffset_[j] <= beginOffset_[j])
        Rcpp::stop("Begin offset (%i) must be smaller than end offset (%i)",
          beginOffset_[j], endOffset_[j]);

      if (endOffset_[j] > max_)
        max_ = endOffset_[j];
    }
  }

  void tokenize(SourceIterator begin, SourceIterator end) {
    curLine_ = begin;
    begin_ = begin;
    end_ = end;

    row_ = 0;
    col_ = 0;
    moreTokens_ = true;
  }

  std::pair<double,size_t> progress() {
    size_t bytes = curLine_ - begin_;
    return std::make_pair(bytes / (double) (end_ - begin_), bytes);
  }

  Token nextToken() {
    if (!moreTokens_)
      return Token(TOKEN_EOF, 0, 0);

    SourceIterator
      fieldBegin = curLine_ + beginOffset_[col_],
      fieldEnd = curLine_ + endOffset_[col_];

    if (fieldBegin >= end_) {
      moreTokens_ = false;
      return Token(TOKEN_EOF, 0, 0);
    }
    if (fieldEnd >= end_) {
      moreTokens_ = false;
      if (col_ + 1 != cols_) {
        warn(row_, -1,
          tfm::format("%i cols on last line", cols_),
          tfm::format("%i cols", col_ + 1)
        );
      }
      return fieldToken(fieldBegin, end_);
    }

    Token t = fieldToken(fieldBegin, fieldEnd);

    col_++;
    if (col_  >= cols_)
      newLine(fieldEnd);

    return t;
  }

private:

  Token fieldToken(SourceIterator begin, SourceIterator end) {
    Token t = Token(begin, end, row_, col_);
    t.trim();
    t.flagNA(NA_);

    return t;
  }

  void newLine(SourceIterator cur) {
    row_++;
    col_ = 0;

    curLine_ = cur;

    // Find EOL - last columns may be whitespace, and some fwf files have
    // ragged line lengths, so need to scan
    while(curLine_ != end_ && !(*curLine_ == '\r' || *curLine_ == '\n'))
      curLine_++;
    advanceForLF(&curLine_, end_);
    if (curLine_ != end_)
      curLine_++;
  }

};

#endif

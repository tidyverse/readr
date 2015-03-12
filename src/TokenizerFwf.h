#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"

class TokenizerFwf : public Tokenizer {
  std::vector<int> beginOffset_, endOffset_;
  int lineWidth_;
  std::string NA_;

  SourceIterator begin_, curLine_, end_;
  int row_, col_, cols_, max_;
  bool moreTokens_;

public:

  TokenizerFwf(std::vector<int> beginOffset, std::vector<int> endOffset, std::string NA = "NA"):
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

    cacheLineWidth();
    if (max_ >= lineWidth_)
      Rcpp::stop("Line width (%i) smaller than last field (%i)",
        lineWidth_, max_);

    row_ = 0;
    col_ = 0;
    moreTokens_ = true;
  }

  double proportionDone() {
    return (curLine_ - begin_) / (double) (end_ - begin_);
  }

  Token nextToken() {
    if (!moreTokens_)
      return Token(TOKEN_EOF, 0, 0);

    // NA handling
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
        Rcpp::warning("Final line is incomplete");
      }
      return fieldToken(fieldBegin, end_);
    }

    Token t = fieldToken(fieldBegin, fieldEnd);

    col_++;
    if (col_  >= cols_) {
      row_++;
      col_ = 0;
      curLine_ += lineWidth_;
    }

    return t;
  }

private:

  Token fieldToken(SourceIterator begin, SourceIterator end) {
    Token t = Token(begin, end, row_, col_);
    t.trim();
    t.flagNA(NA_);

    return t;
  }

  void cacheLineWidth() {
    SourceIterator cur = begin_;
    while(*cur != '\n' && cur != end_)
      cur++;

    lineWidth_ = cur - begin_ + 1;
  }

};

#endif

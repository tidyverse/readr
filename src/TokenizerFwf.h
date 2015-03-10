#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"

class TokenizerFwf : public Tokenizer {
  std::vector<int> beginOffset_, endOffset_;
  int lineWidth_;
  std::string NA_;
  int NA_size_;

  SourceIterator begin_, curLine_, end_;
  int row_, col_, cols_;
  bool moreTokens_;

public:

  TokenizerFwf(std::vector<int> beginOffset, std::vector<int> endOffset, std::string NA = "NA"):
    beginOffset_(beginOffset),
    endOffset_(endOffset),
    NA_(NA),
    NA_size_(NA.size()),
    cols_(beginOffset.size()),
    moreTokens_(false)
  {
  }

  void tokenize(SourceIterator begin, SourceIterator end) {
    curLine_ = begin;
    begin_ = begin;
    end_ = end;

    cacheLineWidth();

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
      return Token(fieldBegin, end_, row_, col_);
    }

    Token t = Token(fieldBegin, fieldEnd, row_, col_);

    col_++;
    if (col_  >= cols_) {
      row_++;
      col_ = 0;
      curLine_ += lineWidth_;
    }

    return t;
  }

private:

  void cacheLineWidth() {
    SourceIterator cur = begin_;
    while(*cur != '\n')
      cur++;

    lineWidth_ = cur - begin_ + 1;
  }

};

#endif

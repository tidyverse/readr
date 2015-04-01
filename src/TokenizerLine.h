#ifndef FASTREAD_TOKENIZERLINE_H_
#define FASTREAD_TOKENIZERLINE_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

class TokenizerLine : public Tokenizer {
  SourceIterator begin_, cur_, end_;
  bool moreTokens_;
  int line_;

public:

  TokenizerLine(): moreTokens_(false) {}

  void tokenize(SourceIterator begin, SourceIterator end) {
    cur_ = begin;
    end_ = end;
    line_ = 0;
    moreTokens_ = true;
  }

  double proportionDone() {
    return (cur_ - begin_) / (end_ - begin_);
  }

  Token nextToken() {
    SourceIterator token_begin = cur_;
    int line = line_;

    if (!moreTokens_)
      return Token(TOKEN_EOF, line, 0);

    while (cur_ != end_) {
      Advance advance(&cur_);
      if ((line_ + 1) % 100000 == 0)
        Rcpp::checkUserInterrupt();

      switch(*cur_) {
      case '\r':
      case '\n':
        return Token(token_begin, advanceForLF(&cur_, end_), line, 0);
      default:
        break;
      }
    }

    // Reached end of Source: cur_ == end_
    moreTokens_ = false;
    if (token_begin == end_) {
      return Token(TOKEN_EOF, line, 0);
    } else {
      return Token(token_begin, end_, line, 0);
    }
  }

};

#endif

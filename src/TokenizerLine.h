#ifndef FASTREAD_TOKENIZERLINE_H_
#define FASTREAD_TOKENIZERLINE_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"

class TokenizerLine : public Tokenizer {
  SourceIterator cur_, end_;
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
      case '\n':
        line_++;
        return Token(token_begin, cur_, line, 0);
      default:
        break;
      }
    }

    // Reached end of Source: cur_ == end_
    moreTokens_ = false;
    return Token(token_begin, end_, line, 0);
  }

};

#endif

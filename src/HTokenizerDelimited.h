#ifndef FASTREAD_PARSERDELIMITED_H
#define FASTREAD_PARSERDELIMITED_H

#include "HToken.h"
#include <Rcpp.h>
#include <boost/noncopyable.hpp>

enum CsvState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE
};

class Advance : boost::noncopyable  {
  StreamIterator* pIter_;
public:
  Advance(StreamIterator* pIter): pIter_(pIter) {}
  ~Advance() {
    (*pIter_)++;
  }
};

class TokenizerDelimited {
  char delim_;
  StreamIterator cur_, end_;
  int row_, col_;
  bool moreTokens_;

  CsvState state_;

public:

  TokenizerDelimited(char delim = ','): delim_(delim), moreTokens_(false) {}

  void tokenize(StreamIterator begin, StreamIterator end) {
    cur_ = begin;
    end_ = end;

    row_ = 0;
    col_ = 0;
    state_ = STATE_DELIM;
    moreTokens_ = true;
  }

  Token nextToken() {
    if (!moreTokens_)
      return Token(TOKEN_EOF);

    StreamIterator token_begin = cur_;

    while (cur_ != end_) {
      // Increments cur on destruct, ensuring that we always move on to the
      // next character
      Advance advance(&cur_);

      if (row_ % 1000 == 0 || col_ % 1000 == 0)
        Rcpp::checkUserInterrupt();

      switch(state_) {
      case STATE_DELIM:
        if (*cur_ == '\r') {
          // Ignore \r, expect will be followed by \n
        } else if (*cur_ == '\n') {
          row_++;
          col_ = 0;
          return Token(TOKEN_EMPTY);
        } else if (*cur_ == delim_) {
          col_++;
          return Token(TOKEN_EMPTY);
        } else if (*cur_ == '"') {
          col_++;
          state_ = STATE_STRING;
        } else {
          col_++;
          state_ = STATE_FIELD;
        }
        break;

      case STATE_FIELD:
        if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          row_++;
          col_ = 0;
          state_ = STATE_DELIM;
          return Token(TOKEN_POINTER, token_begin, cur_);
        } else if (*cur_ == delim_) {
          col_++;
          state_ = STATE_DELIM;
          return Token(TOKEN_POINTER, token_begin, cur_);
        }
        break;

      case STATE_QUOTE:
        if (*cur_ == '"') {
          // Construct a string in temporary buffer and return it
          state_ = STATE_STRING;
        } else if (*cur_ == delim_) {
          state_ = STATE_DELIM;
          return Token(TOKEN_POINTER, token_begin + 1, cur_ - 1);
        } else {
          Rcpp::stop("Expecting delimiter or quote at (%i, %i) but found '%s'",
                      row_, col_, *cur_);
        }
        break;

      case STATE_STRING:
        if (*cur_ == '"')
          state_ = STATE_QUOTE;
        break;
      }
    }

    // Reached end of stream: cur_ == end_
    moreTokens_ = false;

    switch (state_) {
    case STATE_DELIM:
      if (col_ == 0) {
        return Token(TOKEN_EOF);
      } else {
        return Token(TOKEN_EMPTY);
      }

    case STATE_QUOTE:
      return Token(TOKEN_POINTER, token_begin + 1, end_ - 1);

    case STATE_STRING:
      Rf_warning("Unterminated string at end of file");
      return Token(TOKEN_POINTER, token_begin + 1, end_);

    case STATE_FIELD:
      return Token(TOKEN_POINTER, token_begin, end_);
    }

    return Token(TOKEN_EOF);
  }
};

#endif

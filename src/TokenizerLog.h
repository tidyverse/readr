#ifndef FASTREAD_TOKENIZER_LOG_H_
#define FASTREAD_TOKENIZER_LOG_H_

#include "cpp11/protect.hpp"

#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

enum LogState {
  LOG_DELIM,
  LOG_FIELD,
  LOG_STRING,
  LOG_ESCAPE,
  LOG_QUOTE,
  LOG_DATE
};

class TokenizerLog : public Tokenizer {
  SourceIterator begin_, cur_, end_;
  LogState state_;
  int row_, col_;
  bool moreTokens_;
  bool trimWS_;

public:
  TokenizerLog(bool trimWS) : trimWS_(trimWS) {}

  void tokenize(SourceIterator begin, SourceIterator end) {
    cur_ = begin;
    begin_ = begin;
    end_ = end;

    row_ = 0;
    col_ = 0;
    state_ = LOG_DELIM;
    moreTokens_ = true;
  }

  std::pair<double, size_t> progress() {
    size_t bytes = cur_ - begin_;
    return std::make_pair(bytes / (double)(end_ - begin_), bytes);
  }

  Token nextToken() {
    // Capture current position
    int row = row_, col = col_;

    if (!moreTokens_)
      return Token(TOKEN_EOF, row, col);

    SourceIterator token_begin = cur_;

    while (cur_ != end_) {
      Advance advance(&cur_);

      if ((row_ + 1) % 100000 == 0 || (col_ + 1) % 100000 == 0)
        cpp11::check_user_interrupt();

      switch (state_) {
      case LOG_DELIM:
        if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          advanceForLF(&cur_, end_);
          return Token(TOKEN_EMPTY, row, col);
        } else if (*cur_ == ' ') {
          break;
        } else if (*cur_ == '"') {
          state_ = LOG_STRING;
        } else if (*cur_ == '[') {
          state_ = LOG_DATE;
        } else {
          state_ = LOG_FIELD;
        }
        break;

      case LOG_FIELD:
        if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          return fieldToken(token_begin, advanceForLF(&cur_, end_), row, col);
        } else if (*cur_ == ' ') {
          newField();
          return fieldToken(token_begin, cur_, row, col);
        }
        break;

      case LOG_QUOTE:
        if (*cur_ == ' ') {
          newField();
          return fieldToken(token_begin + 1, cur_ - 1, row, col);
        } else if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          return fieldToken(
              token_begin + 1, advanceForLF(&cur_, end_) - 1, row, col);
        } else {
          state_ = LOG_STRING;
        }
        break;

      case LOG_STRING:
        if (*cur_ == '"') {
          state_ = LOG_QUOTE;
        } else if (*cur_ == '\\') {
          state_ = LOG_ESCAPE;
        }
        break;

      case LOG_ESCAPE:
        state_ = LOG_STRING;
        break;

      case LOG_DATE:
        if (*cur_ == ']') {
          newField();
          if (cur_ + 1 != end_)
            cur_++;
          return fieldToken(token_begin + 1, cur_ - 1, row, col);
        }
        break;
      }
    }

    // Reached end of Source: cur_ == end_
    moreTokens_ = false;

    switch (state_) {
    case LOG_DELIM:
      if (col_ == 0) {
        return Token(TOKEN_EOF, row, col);
      } else {
        return Token(TOKEN_EMPTY, row, col);
      }

    case LOG_QUOTE:
      return fieldToken(token_begin + 1, end_ - 1, row, col);

    case LOG_STRING:
      return fieldToken(token_begin + 1, end_, row, col);

    case LOG_ESCAPE:
      warn(row, col, "closing escape at end of file");
      return fieldToken(token_begin + 1, end_, row, col);

    case LOG_DATE:
      warn(row, col, "closing ] at end of file");
      return fieldToken(token_begin + 1, end_, row, col);

    case LOG_FIELD:
      return fieldToken(token_begin, end_, row, col);
    }

    return Token(TOKEN_EOF, row, col);
  }

private:
  void newField() {
    col_++;
    state_ = LOG_DELIM;
  }

  void newRecord() {
    row_++;
    col_ = 0;
    state_ = LOG_DELIM;
  }

  Token fieldToken(SourceIterator begin, SourceIterator end, int row, int col) {
    Token t(begin, end, row, col, false);
    if (trimWS_) {
      t.trim();
    }

    t.flagNA(std::vector<std::string>(1, "-"));

    return t;
  }
};

#endif

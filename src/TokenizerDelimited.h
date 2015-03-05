#ifndef FASTREAD_TOKENIZERDELIMITED_H_
#define FASTREAD_TOKENIZERDELIMITED_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"

enum CsvState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE
};

class TokenizerDelimited : public Tokenizer {
  char delim_;
  SourceIterator cur_, end_;
  std::string NA_;
  int NA_size_;
  int row_, col_;
  bool moreTokens_;

  CsvState state_;

public:

  TokenizerDelimited(char delim = ','):
    delim_(delim),
    NA_("NA"),
    NA_size_(2),
    moreTokens_(false)
  {
  }

  void tokenize(SourceIterator begin, SourceIterator end) {
    cur_ = begin;
    end_ = end;

    row_ = 0;
    col_ = 0;
    state_ = STATE_DELIM;
    moreTokens_ = true;
  }

  Token nextToken() {
    // Capture current position
    int row = row_, col = col_;

    if (!moreTokens_)
      return Token(TOKEN_EOF, row, col);

    SourceIterator token_begin = cur_;
    bool hasEscape = false;

    while (cur_ != end_) {
      // Increments cur on destruct, ensuring that we always move on to the
      // next character
      Advance advance(&cur_);

      if ((row_ + 1) % 100000 == 0 || (col_ + 1) % 100000 == 0)
        Rcpp::checkUserInterrupt();

      switch(state_) {
      case STATE_DELIM:
        if (*cur_ == '\r') {
          // Ignore \r, expect will be followed by \n
        } else if (*cur_ == '\n') {
          newRecord();
          return Token(TOKEN_EMPTY, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return Token(TOKEN_EMPTY, row, col);
        } else if (*cur_ == '"') {
          state_ = STATE_STRING;
        } else {
          state_ = STATE_FIELD;
        }
        break;

      case STATE_FIELD:
        if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          newRecord();
          return fieldToken(token_begin, cur_, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return fieldToken(token_begin, cur_, row, col);
        }
        break;

      case STATE_QUOTE:
        if (*cur_ == '"') {
          hasEscape = true;
          state_ = STATE_STRING;
        } else if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          newRecord();
          return stringToken(token_begin + 1, cur_ - 1, hasEscape, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return stringToken(token_begin + 1, cur_ - 1, hasEscape, row, col);
        } else {
          Rcpp::stop("Expecting delimiter or quote at (%i, %i) but found '%s'",
            row, col, *cur_);
        }
        break;

      case STATE_STRING:
        if (*cur_ == '"')
          state_ = STATE_QUOTE;
        break;
      }
    }

    // Reached end of Source: cur_ == end_
    moreTokens_ = false;

    switch (state_) {
    case STATE_DELIM:
      if (col_ == 0) {
        return Token(TOKEN_EOF, row, col);
      } else {
        return Token(TOKEN_EMPTY, row, col);
      }

    case STATE_QUOTE:
      return stringToken(token_begin + 1, end_ - 1, hasEscape, row, col);

    case STATE_STRING:
      Rf_warning("Unterminated string at end of file");
      return stringToken(token_begin + 1, end_, hasEscape, row, col);

    case STATE_FIELD:
      return fieldToken(token_begin, end_, row, col);
    }

    return Token(TOKEN_EOF, row, col);
  }

private:

  void newField() {
    col_++;
    state_ = STATE_DELIM;
  }

  void newRecord() {
    row_++;
    col_ = 0;
    state_ = STATE_DELIM;
  }

  Token fieldToken(SourceIterator begin, SourceIterator end, int row, int col) {
    if ((end - begin) == NA_size_ && strncmp(begin, &NA_[0], NA_size_) == 0)
      return Token(TOKEN_MISSING, row, col);

    return Token(begin, end, row, col);
  }

  Token stringToken(SourceIterator begin, SourceIterator end, bool hasEscape,
                    int row, int col) {
    if (begin == end)
      return Token(TOKEN_EMPTY, row, col);

    if (hasEscape)
      return Token(begin, end, TokenizerDelimited::unescapeDoubleQuote, row, col);

    return Token(begin, end, row, col);
  }

public:

  static void unescapeDoubleQuote(SourceIterator begin, SourceIterator end,
                                  boost::container::string* pOut) {
    pOut->reserve(end - begin);

    bool inEscape = false;
    for (SourceIterator cur = begin; cur != end; ++cur) {
      if (*cur == '"') {
        if (inEscape) {
          pOut->push_back(*cur);
          inEscape = false;
        } else {
          inEscape = true;
        }
      } else {
        pOut->push_back(*cur);
      }
    }
  }


};

#endif

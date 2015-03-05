#ifndef FASTREAD_TOKENIZERDELIMITED_H_
#define FASTREAD_TOKENIZERDELIMITED_H_

#include <Rcpp.h>
#include <boost/noncopyable.hpp>
#include "Token.h"

enum CsvState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE
};

class Advance : boost::noncopyable  {
  SourceIterator* pIter_;
public:
  Advance(SourceIterator* pIter): pIter_(pIter) {}
  ~Advance() {
    (*pIter_)++;
  }
};

class TokenizerDelimited {
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
    if (!moreTokens_)
      return Token(TOKEN_EOF);

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
          return Token(TOKEN_EMPTY);
        } else if (*cur_ == delim_) {
          newField();
          return Token(TOKEN_EMPTY);
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
          return fieldToken(token_begin, cur_);
        } else if (*cur_ == delim_) {
          newField();
          return fieldToken(token_begin, cur_);
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
          return stringToken(token_begin + 1, cur_ - 1, hasEscape);
        } else if (*cur_ == delim_) {
          newField();
          return stringToken(token_begin + 1, cur_ - 1, hasEscape);
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

    // Reached end of Source: cur_ == end_
    moreTokens_ = false;

    switch (state_) {
    case STATE_DELIM:
      if (col_ == 0) {
        return Token(TOKEN_EOF);
      } else {
        return Token(TOKEN_EMPTY);
      }

    case STATE_QUOTE:
      return stringToken(token_begin + 1, end_ - 1, hasEscape);

    case STATE_STRING:
      Rf_warning("Unterminated string at end of file");
      return stringToken(token_begin + 1, end_, hasEscape);

    case STATE_FIELD:
      return fieldToken(token_begin, end_);
    }

    return Token(TOKEN_EOF);
  }

  int row() {
    return row_;
  }
  int col() {
    return col_;
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

  Token fieldToken(SourceIterator begin, SourceIterator end) {
    if ((end - begin) == NA_size_ && strncmp(begin, &NA_[0], NA_size_) == 0)
      return Token(TOKEN_MISSING);

    return Token(begin, end);
  }

  Token stringToken(SourceIterator begin, SourceIterator end, bool hasEscape) {
    if (begin == end)
      return Token(TOKEN_EMPTY);

    if (hasEscape)
      return Token(begin, end, TokenizerDelimited::unescapeDoubleQuote);

    return Token(begin, end);
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

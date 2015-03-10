#ifndef FASTREAD_TOKENIZECSV_H_
#define FASTREAD_TOKENIZECSV_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"

enum CsvState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE,
  STATE_ESCAPE_S,
  STATE_ESCAPE_F,
  STATE_STRING_END
};

class TokenizerCsv : public Tokenizer {
  char delim_;
  std::string NA_;
  int NA_size_;

  bool escapeBackslash_, escapeDouble_;

  SourceIterator begin_, cur_, end_;
  CsvState state_;
  int row_, col_;
  bool moreTokens_;

public:

  TokenizerCsv(char delim = ',', std::string NA = "NA",
               bool escapeBackslash = false, bool escapeDouble = true):
    delim_(delim),
    NA_(NA),
    NA_size_(NA.size()),
    escapeBackslash_(escapeBackslash),
    escapeDouble_(escapeDouble),
    moreTokens_(false)
  {
  }

  void tokenize(SourceIterator begin, SourceIterator end) {
    cur_ = begin;
    begin_ = begin;
    end_ = end;

    row_ = 0;
    col_ = 0;
    state_ = STATE_DELIM;
    moreTokens_ = true;
  }

  double proportionDone() {
    return (cur_ - begin_) / (double) (end_ - begin_);
  }

  Token nextToken() {
    // Capture current position
    int row = row_, col = col_;

    if (!moreTokens_)
      return Token(TOKEN_EOF, row, col);

    SourceIterator token_begin = cur_;
    bool hasEscapeD = false, hasEscapeB = false;

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
        } else if (escapeBackslash_ && *cur_ == '\\') {
          state_ = STATE_ESCAPE_F;
        } else {
          state_ = STATE_FIELD;
        }
        break;

      case STATE_FIELD:
        if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          newRecord();
          return fieldToken(token_begin, cur_, hasEscapeB, row, col);
        } else if (escapeBackslash_ && *cur_ == '\\') {
          state_ = STATE_ESCAPE_F;
        } else if (*cur_ == delim_) {
          newField();
          return fieldToken(token_begin, cur_, hasEscapeB, row, col);
        }
        break;

      case STATE_ESCAPE_F:
        hasEscapeB = true;
        state_ = STATE_FIELD;
        break;

      case STATE_QUOTE:
        if (*cur_ == '"') {
          hasEscapeD = true;
          state_ = STATE_STRING;
        } else if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          newRecord();
          return stringToken(token_begin + 1, cur_ - 1, hasEscapeB, hasEscapeD, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return stringToken(token_begin + 1, cur_ - 1, hasEscapeB, hasEscapeD, row, col);
        } else {
          Rcpp::stop("Expecting delimiter or quote at (%i, %i) but found '%s'",
            row, col, *cur_);
        }
        break;

      case STATE_STRING:
        if (*cur_ == '"') {
          if (escapeDouble_) {
            state_ = STATE_QUOTE;
          } else {
            state_ = STATE_STRING_END;
          }
        } else if (escapeBackslash_ && *cur_ == '\\') {
          state_ = STATE_ESCAPE_S;
        }
        break;

      case STATE_STRING_END:
        if (*cur_ == '\r') {
          // ignore
        } else if (*cur_ == '\n') {
          newRecord();
          return stringToken(token_begin + 1, cur_ - 1, hasEscapeB, hasEscapeD, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return stringToken(token_begin + 1, cur_ - 1, hasEscapeB, hasEscapeD, row, col);
        } else {
          state_ = STATE_FIELD;
        }
        break;

      case STATE_ESCAPE_S:
        hasEscapeB = true;
        state_ = STATE_STRING;
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

    case STATE_STRING_END:
    case STATE_QUOTE:
      return stringToken(token_begin + 1, end_ - 1, hasEscapeB, hasEscapeD, row, col);

    case STATE_STRING:
      Rf_warning("Unterminated string at end of file");
      return stringToken(token_begin + 1, end_, hasEscapeB, hasEscapeD, row, col);

    case STATE_ESCAPE_S:
    case STATE_ESCAPE_F:
      Rf_warning("Unterminated escape at end of file");
      return stringToken(token_begin, end_ - 1, hasEscapeB, hasEscapeD, row, col);

    case STATE_FIELD:
      return fieldToken(token_begin, end_, hasEscapeB, row, col);
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

  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasEscapeB,
                   int row, int col) {
    if ((end - begin) == NA_size_ && strncmp(begin, &NA_[0], NA_size_) == 0)
      return Token(TOKEN_MISSING, row, col);

    UnescapeFun unescaper = hasEscapeB ? TokenizerCsv::unescapeBackslash : NULL;

    return Token(begin, end, unescaper, row, col);
  }

  Token stringToken(SourceIterator begin, SourceIterator end, bool hasEscapeB,
                    bool hasEscapeD, int row, int col) {
    if (begin == end)
      return Token(TOKEN_EMPTY, row, col);

    UnescapeFun unescaper = NULL;
    if (hasEscapeD && !hasEscapeB) {
      unescaper = TokenizerCsv::unescapeDouble;
    } else if (hasEscapeB && !hasEscapeD) {
      unescaper = TokenizerCsv::unescapeBackslash;
    } else if (hasEscapeB && hasEscapeD) {
      Rcpp::stop("Not supported");
    }
    return Token(begin, end, unescaper, row, col);
  }

public:

  static void unescapeDouble(SourceIterator begin, SourceIterator end,
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

  static void unescapeBackslash(SourceIterator begin, SourceIterator end,
                                boost::container::string* pOut) {
    pOut->reserve(end - begin);

    bool inEscape = false;
    for (SourceIterator cur = begin; cur != end; ++cur) {
      if (inEscape) {
        switch(*cur) {
        case '\'':  pOut->push_back('\''); break;
        case '"':   pOut->push_back('"');  break;
        case '\\':  pOut->push_back('\\'); break;
        case 'a':   pOut->push_back('\a'); break;
        case 'b':   pOut->push_back('\b'); break;
        case 'f':   pOut->push_back('\f'); break;
        case 'n':   pOut->push_back('\n'); break;
        case 'r':   pOut->push_back('\r'); break;
        case 't':   pOut->push_back('\t'); break;
        case 'v':   pOut->push_back('\v'); break;
        default:    pOut->push_back(*cur); break;
        }
        inEscape = false;
      } else {
        if (*cur == '\\') {
          inEscape = true;
        } else {
          pOut->push_back(*cur);
        }
      }
    }
  }

};

#endif

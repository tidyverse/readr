#ifndef FASTREAD_TOKENIZEDELIM_H_
#define FASTREAD_TOKENIZEDELIM_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

enum DelimState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE,
  STATE_ESCAPE_S,
  STATE_ESCAPE_F,
  STATE_STRING_END
};

class TokenizerDelim : public Tokenizer {
  char delim_, quote_;
  std::vector<std::string> NA_;

  bool trimWS_, escapeBackslash_, escapeDouble_;

  SourceIterator begin_, cur_, end_;
  DelimState state_;
  int row_, col_;
  bool moreTokens_;

public:

  TokenizerDelim(char delim = ',', char quote = '"',
               std::vector<std::string> NA = std::vector<std::string>(1, "NA"),
               bool trimWS = true, bool escapeBackslash = false,
               bool escapeDouble = true):
    delim_(delim),
    quote_(quote),
    NA_(NA),
    trimWS_(trimWS),
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

  std::pair<double,size_t> progress() {
    size_t bytes = cur_ - begin_;
    return std::make_pair(bytes / (double) (end_ - begin_), bytes);
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
        if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          advanceForLF(&cur_, end_);
          return emptyToken(row, col);
        } else if (*cur_ == delim_) {
          newField();
          return emptyToken(row, col);
        } else if (*cur_ == quote_) {
          state_ = STATE_STRING;
        } else if (escapeBackslash_ && *cur_ == '\\') {
          state_ = STATE_ESCAPE_F;
        } else {
          state_ = STATE_FIELD;
        }
        break;

      case STATE_FIELD:
        if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          return fieldToken(token_begin, advanceForLF(&cur_, end_), hasEscapeB, row, col);
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
        if (*cur_ == quote_) {
          hasEscapeD = true;
          state_ = STATE_STRING;
        } else if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          return stringToken(token_begin + 1, advanceForLF(&cur_, end_) - 1,
            hasEscapeB, hasEscapeD, row, col);
        } else if (*cur_ == delim_) {
          newField();
          return stringToken(token_begin + 1, cur_ - 1,
            hasEscapeB, hasEscapeD, row, col);
        } else {
          warn(row, col, "delimiter or quote", std::string(cur_, cur_ + 1));
          state_ = STATE_STRING;
        }
        break;

      case STATE_STRING:
        if (*cur_ == quote_) {
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
        if (*cur_ == '\r' || *cur_ == '\n') {
          newRecord();
          return stringToken(token_begin + 1, advanceForLF(&cur_, end_) - 1,
            hasEscapeB, hasEscapeD, row, col);
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
        return emptyToken(row, col);
      }

    case STATE_STRING_END:
    case STATE_QUOTE:
      return stringToken(token_begin + 1, end_ - 1, hasEscapeB, hasEscapeD, row, col);

    case STATE_STRING:
      warn(row, col, "closing quote at end of file");
      return stringToken(token_begin + 1, end_, hasEscapeB, hasEscapeD, row, col);

    case STATE_ESCAPE_S:
    case STATE_ESCAPE_F:
      warn(row, col, "closing escape at end of file");
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

  Token emptyToken(int row, int col) {
    return Token(TOKEN_EMPTY, row, col).flagNA(NA_);
  }

  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasEscapeB,
                   int row, int col) {
    Token t(begin, end, row, col, (hasEscapeB) ? this : NULL);
    if (trimWS_)
      t.trim();
    t.flagNA(NA_);
    return t;
  }

  Token stringToken(SourceIterator begin, SourceIterator end, bool hasEscapeB,
                    bool hasEscapeD, int row, int col) {
    Token t(begin, end, row, col, (hasEscapeD || hasEscapeB) ? this : NULL);
    if (trimWS_)
      t.trim();
    return t;
  }


public:

  void unescape(SourceIterator begin, SourceIterator end,
                boost::container::string* pOut) {
    if (escapeDouble_ && !escapeBackslash_) {
      unescapeDouble(begin, end, pOut);
    } else if (escapeBackslash_ && !escapeDouble_) {
      unescapeBackslash(begin, end, pOut);
    } else if (escapeBackslash_ && escapeDouble_) {
      Rcpp::stop("Backslash & double escapes not supported at this time");
    }
  }

  void unescapeDouble(SourceIterator begin, SourceIterator end,
                      boost::container::string* pOut) {
    pOut->reserve(end - begin);

    bool inEscape = false;
    for (SourceIterator cur = begin; cur != end; ++cur) {
      if (*cur == quote_) {
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

  void unescapeBackslash(SourceIterator begin, SourceIterator end,
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
        default:
          if (*cur == delim_ || *cur == quote_) {
            pOut->push_back(*cur);
          } else {
            pOut->push_back('\\');
            pOut->push_back(*cur);
            warn(row_, col_, "standard escape", "\\" + std::string(*cur, *cur + 1));
          }
          break;
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

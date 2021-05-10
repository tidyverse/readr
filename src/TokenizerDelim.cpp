#include "TokenizerDelim.h"

#include <utility>

#include "cpp11/protect.hpp"

TokenizerDelim::TokenizerDelim(
    char delim,
    char quote,
    std::vector<std::string> NA,
    const std::string& comment,
    bool trimWS,
    bool escapeBackslash,
    bool escapeDouble,
    bool quotedNA,
    bool skipEmptyRows)
    : delim_(delim),
      quote_(quote),
      NA_(std::move(NA)),
      comment_(comment),
      hasComment_(!comment.empty()),
      trimWS_(trimWS),
      escapeBackslash_(escapeBackslash),
      escapeDouble_(escapeDouble),
      quotedNA_(quotedNA),
      hasEmptyNA_(false),
      moreTokens_(false),
      skipEmptyRows_(skipEmptyRows) {
  for (auto& i : NA_) {
    if (i.empty()) {
      hasEmptyNA_ = true;
      break;
    }
  }
}

void TokenizerDelim::tokenize(SourceIterator begin, SourceIterator end) {
  cur_ = begin;

  end_ = end;
  begin_ = begin;

  row_ = 0;
  col_ = 0;
  state_ = STATE_DELIM;
  moreTokens_ = true;
}

std::pair<double, size_t> TokenizerDelim::progress() {
  size_t bytes = cur_ - begin_;
  return std::make_pair(bytes / (double)(end_ - begin_), bytes);
}

Token TokenizerDelim::nextToken() {
  // Capture current position
  int row = row_;

  int col = col_;

  if (!moreTokens_) {
    return {TOKEN_EOF, row, col};
  }

  SourceIterator token_begin = cur_;
  bool hasEscapeD = false;

  bool hasEscapeB = false;

  bool hasNull = false;

  while (cur_ < end_) {
    // Increments cur on destruct, ensuring that we always move on to the
    // next character
    Advance advance(&cur_);

    if (*cur_ == '\0') {
      hasNull = true;
    }

    if ((end_ - cur_) % 131072 == 0) {
      cpp11::check_user_interrupt();
    }

    switch (state_) {
    case STATE_DELIM: {
      while (cur_ != end_ && *cur_ == ' ') {
        ++cur_;
      }
      if (*cur_ == '\r' || *cur_ == '\n') {
        if (col_ == 0 && skipEmptyRows_) {
          advanceForLF(&cur_, end_);
          token_begin = cur_ + 1;
          break;
        }
        newRecord();
        return emptyToken(row, col);
      }
      if (isComment(cur_)) {

        state_ = STATE_COMMENT;

      } else if (*cur_ == delim_) {

        newField();

        return emptyToken(row, col);

      } else if (*cur_ == quote_) {

        token_begin = cur_;

        state_ = STATE_STRING;

      } else if (escapeBackslash_ && *cur_ == '\\') {

        state_ = STATE_ESCAPE_F;

      } else {

        state_ = STATE_FIELD;
      }
      break;
    }

    case STATE_FIELD:
      if (*cur_ == '\r' || *cur_ == '\n') {
        newRecord();
        return fieldToken(
            token_begin,
            advanceForLF(&cur_, end_),
            hasEscapeB,
            hasNull,
            row,
            col);
      } else if (isComment(cur_)) {
        newField();
        state_ = STATE_COMMENT;
        return fieldToken(token_begin, cur_, hasEscapeB, hasNull, row, col);
      } else if (escapeBackslash_ && *cur_ == '\\') {
        state_ = STATE_ESCAPE_F;
      } else if (*cur_ == delim_) {
        newField();
        return fieldToken(token_begin, cur_, hasEscapeB, hasNull, row, col);
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
        return stringToken(
            token_begin + 1,
            advanceForLF(&cur_, end_) - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
      } else if (isComment(cur_)) {
        state_ = STATE_COMMENT;
        return stringToken(
            token_begin + 1,
            cur_ - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
      } else if (*cur_ == delim_) {
        newField();
        return stringToken(
            token_begin + 1,
            cur_ - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
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
        return stringToken(
            token_begin + 1,
            advanceForLF(&cur_, end_) - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
      } else if (isComment(cur_)) {
        state_ = STATE_COMMENT;
        return stringToken(
            token_begin + 1,
            cur_ - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
      } else if (*cur_ == delim_) {
        newField();
        return stringToken(
            token_begin + 1,
            cur_ - 1,
            hasEscapeB,
            hasEscapeD,
            hasNull,
            row,
            col);
      } else {
        state_ = STATE_FIELD;
      }
      break;

    case STATE_ESCAPE_S:
      hasEscapeB = true;
      state_ = STATE_STRING;
      break;

    case STATE_COMMENT:
      if (*cur_ == '\r' || *cur_ == '\n') {

        // If we have read at least one record on the current row go to the
        // next row, line, otherwise just ignore the line.
        if (col_ > 0) {
          row_++;
          row++;
          col_ = 0;
        }
        col = 0;
        advanceForLF(&cur_, end_);
        token_begin = cur_ + 1;
        state_ = STATE_DELIM;
      }

      break;
    }
  }

  // Reached end of Source: cur_ == end_
  moreTokens_ = false;

  switch (state_) {
  case STATE_DELIM:
    if (col_ == 0) {
      return {TOKEN_EOF, row, col};
    } else {
      return emptyToken(row, col);
    }

  case STATE_STRING_END:
  case STATE_QUOTE:
    return stringToken(
        token_begin + 1, end_ - 1, hasEscapeB, hasEscapeD, hasNull, row, col);

  case STATE_STRING:
    warn(row, col, "closing quote at end of file");
    return stringToken(
        token_begin + 1, end_, hasEscapeB, hasEscapeD, hasNull, row, col);

  case STATE_ESCAPE_S:
  case STATE_ESCAPE_F:
    warn(row, col, "closing escape at end of file");
    return stringToken(
        token_begin, end_ - 1, hasEscapeB, hasEscapeD, hasNull, row, col);

  case STATE_FIELD:
    return fieldToken(token_begin, end_, hasEscapeB, hasNull, row, col);

  case STATE_COMMENT:
    return {TOKEN_EOF, row, col};
  }

  return {TOKEN_EOF, row, col};
}

bool TokenizerDelim::isComment(const char* cur) const {
  if (!hasComment_) {
    return false;
  }

  return starts_with_comment(cur, end_, comment_);
}

void TokenizerDelim::newField() {
  col_++;
  state_ = STATE_DELIM;
}

void TokenizerDelim::newRecord() {
  row_++;
  col_ = 0;
  state_ = STATE_DELIM;
}

Token TokenizerDelim::emptyToken(int row, int col) const {
  return {hasEmptyNA_ ? TOKEN_MISSING : TOKEN_EMPTY, row, col};
}

Token TokenizerDelim::fieldToken(
    SourceIterator begin,
    SourceIterator end,
    bool hasEscapeB,
    bool hasNull,
    int row,
    int col) {
  Token t(begin, end, row, col, hasNull, (hasEscapeB) ? this : nullptr);
  if (trimWS_) {
    t.trim();
  }
  t.flagNA(NA_);
  return t;
}

Token TokenizerDelim::stringToken(
    SourceIterator begin,
    SourceIterator end,
    bool hasEscapeB,
    bool hasEscapeD,
    bool hasNull,
    int row,
    int col) {
  Token t(
      begin,
      end,
      row,
      col,
      hasNull,
      (hasEscapeD || hasEscapeB) ? this : nullptr);
  if (trimWS_) {
    t.trim();
  }
  if (quotedNA_) {
    t.flagNA(NA_);
  }
  return t;
}

void TokenizerDelim::unescape(
    SourceIterator begin, SourceIterator end, std::string* pOut) {
  if (escapeDouble_ && !escapeBackslash_) {
    unescapeDouble(begin, end, pOut);
  } else if (escapeBackslash_ && !escapeDouble_) {
    unescapeBackslash(begin, end, pOut);
  } else if (escapeBackslash_ && escapeDouble_) {
    cpp11::stop("Backslash & double escapes not supported at this time");
  }
}

void TokenizerDelim::unescapeDouble(
    SourceIterator begin, SourceIterator end, std::string* pOut) const {
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

void TokenizerDelim::unescapeBackslash(
    SourceIterator begin, SourceIterator end, std::string* pOut) {
  pOut->reserve(end - begin);

  bool inEscape = false;
  for (SourceIterator cur = begin; cur != end; ++cur) {
    if (inEscape) {
      switch (*cur) {
      case '\'':
        pOut->push_back('\'');
        break;
      case '"':
        pOut->push_back('"');
        break;
      case '\\':
        pOut->push_back('\\');
        break;
      case 'a':
        pOut->push_back('\a');
        break;
      case 'b':
        pOut->push_back('\b');
        break;
      case 'f':
        pOut->push_back('\f');
        break;
      case 'n':
        pOut->push_back('\n');
        break;
      case 'r':
        pOut->push_back('\r');
        break;
      case 't':
        pOut->push_back('\t');
        break;
      case 'v':
        pOut->push_back('\v');
        break;
      default:
        if (*cur == delim_ || *cur == quote_ || isComment(cur)) {
          pOut->push_back(*cur);
        } else {
          pOut->push_back('\\');
          pOut->push_back(*cur);
          warn(row_, col_, "standard escape", "\\" + std::string(cur, 1));
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

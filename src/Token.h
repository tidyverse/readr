#ifndef FASTREAD_TOKEN_H_
#define FASTREAD_TOKEN_H_

#include "cpp11/raws.hpp"

#include "Iconv.h"
#include "Source.h"
#include "Tokenizer.h"
#include <string>

enum TokenType {
  TOKEN_STRING,  // a sequence of characters
  TOKEN_MISSING, // an missing value
  TOKEN_EMPTY,   // an empty value
  TOKEN_EOF      // end of file
};

class Token {
  TokenType type_;
  SourceIterator begin_, end_;
  size_t row_, col_;
  bool hasNull_;

  Tokenizer* pTokenizer_;

public:
  Token()
      : type_(TOKEN_EMPTY),
        begin_(0),
        end_(0),
        row_(0),
        col_(0),
        hasNull_(false),
        pTokenizer_(nullptr) {}
  Token(TokenType type, int row, int col)
      : type_(type),
        begin_(0),
        end_(0),
        row_(row),
        col_(col),
        hasNull_(false),
        pTokenizer_(nullptr) {}
  Token(
      SourceIterator begin,
      SourceIterator end,
      int row,
      int col,
      bool hasNull,
      Tokenizer* pTokenizer = NULL)
      : type_(TOKEN_STRING),
        begin_(begin),
        end_(end),
        row_(row),
        col_(col),
        hasNull_(hasNull),
        pTokenizer_(pTokenizer) {
    if (begin_ == end_)
      type_ = TOKEN_EMPTY;
  }

  std::string asString() const {
    switch (type_) {
    case TOKEN_STRING: {
      std::string buffer;
      SourceIterators string = getString(&buffer);

      return std::string(string.first, string.second);
    }
    case TOKEN_MISSING:
      return "[MISSING]";
    case TOKEN_EMPTY:
      return "[EMPTY]";
    case TOKEN_EOF:
      return "[EOF]";
    }

    return "";
  }

  SEXP asRaw() const {
    size_t n = (type_ == TOKEN_STRING) ? end_ - begin_ : 0;
    cpp11::writable::raws out(n);

    if (n > 0)
      memcpy(RAW(out), begin_, n);

    return out;
  }

  SEXP asSEXP(Iconv* pEncoder) const {
    switch (type_) {
    case TOKEN_STRING: {
      std::string buffer;
      SourceIterators string = getString(&buffer);

      return pEncoder->makeSEXP(string.first, string.second, hasNull_);
    }
    default:
      return NA_STRING;
    }
  }

  TokenType type() const { return type_; }

  SourceIterators getString(std::string* pOut) const {
    if (pTokenizer_ == NULL)
      return std::make_pair(begin_, end_);

    pTokenizer_->unescape(begin_, end_, pOut);
    return std::make_pair(pOut->data(), pOut->data() + pOut->size());
  }

  size_t row() const { return row_; }
  size_t col() const { return col_; }

  bool hasNull() const { return hasNull_; }

  Token& trim() {
    while (begin_ != end_ && (*begin_ == ' ' || *begin_ == '\t'))
      begin_++;
    while (end_ != begin_ && (*(end_ - 1) == ' ' || *(end_ - 1) == '\t'))
      end_--;

    if (begin_ == end_)
      type_ = TOKEN_EMPTY;

    return *this;
  }

  Token& flagNA(const std::vector<std::string>& NA) {

    std::vector<std::string>::const_iterator it;
    for (it = NA.begin(); it != NA.end(); ++it) {
      if ((size_t)(end_ - begin_) != it->size())
        continue;

      if (strncmp(begin_, it->data(), it->size()) == 0) {
        type_ = TOKEN_MISSING;
        break;
      }
    }

    return *this;
  }
};

#endif

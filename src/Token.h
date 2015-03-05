#ifndef FASTREAD_TOKEN_H_
#define FASTREAD_TOKEN_H_

#include <string>
#include "Source.h"

enum TokenType {
  TOKEN_STRING,   // a sequence of characters
  TOKEN_MISSING,  // an missing value
  TOKEN_EMPTY,    // an empty value
  TOKEN_EOF       // end of file
};

class Token {
  TokenType type_;
  SourceIterator begin_, end_;
  int row_, col_;

  UnescapeFun pUnescaper_;

public:

  Token(): type_(TOKEN_EMPTY), row_(0), col_(0) {}
  Token(TokenType type, int row, int col): type_(type), row_(row), col_(col) {}
  Token(SourceIterator begin, SourceIterator end, UnescapeFun pUnescaper, int row, int col):
    type_(TOKEN_STRING),
    begin_(begin),
    end_(end),
    row_(row),
    col_(col),
    pUnescaper_(pUnescaper)
  {}
  Token(SourceIterator begin, SourceIterator end, int row, int col):
    type_(TOKEN_STRING),
    begin_(begin),
    end_(end),
    row_(row),
    col_(col),
    pUnescaper_(NULL)
  {}

  std::string asString() const {
    switch(type_) {
    case TOKEN_STRING:  return std::string(begin_, end_);
    case TOKEN_MISSING:  return "[MISSING]";
    case TOKEN_EMPTY:    return "[EMPTY]";
    case TOKEN_EOF:      return "[EOF]";
    }
  }

  TokenType type() const {
    return type_;
  }

  SourceIterators getString(boost::container::string *pOut) const {
    if (pUnescaper_ == NULL)
      return std::make_pair(begin_, end_);

    pUnescaper_(begin_, end_, pOut);
    return std::make_pair(pOut->data(), pOut->data() + pOut->size());
  }

  int row() const {
    return row_;
  }
  int col() const {
    return col_;
  }

};

#endif

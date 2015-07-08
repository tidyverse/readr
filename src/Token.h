#ifndef FASTREAD_TOKEN_H_
#define FASTREAD_TOKEN_H_

#include <string>
#include "Source.h"
#include "Tokenizer.h"

enum TokenType {
  TOKEN_STRING,   // a sequence of characters
  TOKEN_MISSING,  // an missing value
  TOKEN_EMPTY,    // an empty value
  TOKEN_EOF       // end of file
};

class Token {
  TokenType type_;
  SourceIterator begin_, end_;
  size_t row_, col_;

  Tokenizer* pTokenizer_;

public:

  Token(): type_(TOKEN_EMPTY), row_(0), col_(0) {}
  Token(TokenType type, int row, int col): type_(type), row_(row), col_(col) {}
  Token(SourceIterator begin, SourceIterator end, int row, int col, Tokenizer* pTokenizer = NULL):
    type_(TOKEN_STRING),
    begin_(begin),
    end_(end),
    row_(row),
    col_(col),
    pTokenizer_(pTokenizer)
  {
    if (begin_ == end_)
      type_ = TOKEN_EMPTY;
  }

  std::string asString() const {
    switch(type_) {
    case TOKEN_STRING:   {
      boost::container::string buffer;
      SourceIterators string = getString(&buffer);

      return std::string(string.first, string.second);
    }
    case TOKEN_MISSING:  return "[MISSING]";
    case TOKEN_EMPTY:    return "[EMPTY]";
    case TOKEN_EOF:      return "[EOF]";
    }

    return "";
  }

  TokenType type() const {
    return type_;
  }

  SourceIterators getString(boost::container::string *pOut) const {
    if (pTokenizer_ == NULL)
      return std::make_pair(begin_, end_);

    pTokenizer_->unescape(begin_, end_, pOut);
    return std::make_pair(pOut->data(), pOut->data() + pOut->size());
  }

  size_t row() const {
    return row_;
  }
  size_t col() const {
    return col_;
  }

  Token& trim() {
    while (*begin_ == ' ' && begin_ != end_)
      begin_++;
    while (*(end_ - 1) == ' ' && end_ != begin_)
      end_--;

    if (begin_ == end_)
      type_ = TOKEN_EMPTY;

    return *this;
  }

  Token& flagNA(std::vector<std::string> NA) {

    std::vector<std::string>::iterator it;
    for (it = NA.begin(); it != NA.end(); ++it) {
      if ((size_t) (end_ - begin_) != it->size())
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

#ifndef FASTREAD_TOKEN_H
#define FASTREAD_TOKEN_H

typedef const char* StreamIterator;
#include <string>

enum TokenType {
  TOKEN_POINTER,  // a pointer to existing memory
  TOKEN_MISSING,  // an missing value
  TOKEN_EMPTY,    // an empty value
  TOKEN_EOF       // end of file
};

class Token {
  TokenType type_;
  StreamIterator begin_, end_;  // indexes to start and end of string (for TOKEN_POINTER)

public:

  Token(): type_(TOKEN_EMPTY) {}
  Token(TokenType type): type_(type) {}
  Token(StreamIterator begin, StreamIterator end):
    type_(TOKEN_POINTER), begin_(begin), end_(end) {
  }

  std::string asString() const {
    switch(type_) {
    case TOKEN_POINTER:  return std::string(begin_, end_);
    case TOKEN_MISSING:  return "[MISSING]";
    case TOKEN_EMPTY:    return "[EMPTY]";
    case TOKEN_EOF:      return "[EOF]";
    }
  }

  TokenType type() const {
    return type_;
  }
  StreamIterator begin() const {
    return begin_;
  }
  StreamIterator end() const {
    return end_;
  }

};


#endif

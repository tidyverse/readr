#ifndef FASTREAD_TOKEN_H
#define FASTREAD_TOKEN_H

typedef const char* StreamIterator;
#include <string>

enum TokenType {
  TOKEN_POINTER,  // a pointer to existing memory
  TOKEN_INLINE,   // a new std::string
  TOKEN_MISSING,  // an missing value
  TOKEN_EMPTY,    // an empty value
  TOKEN_EOL,      // end of record
  TOKEN_EOF       // end of file
};

class Token {
  TokenType type_;
  StreamIterator begin_, end_;  // indexes to start and end of string (for TOKEN_POINTER)
  std::string text_; // string itself (for TOKEN_RAW)

public:

  Token(TokenType type): type_(type) {}
  Token(TokenType type, std::string text): type_(type), text_(text) {}
  Token(TokenType type, StreamIterator begin, StreamIterator end):
    type_(type), begin_(begin), end_(end) {
  }

  template <class Stream>
  std::string asString(Stream s) const {
    switch(type_) {
    case TOKEN_POINTER:  return std::string(begin_, end_);
    case TOKEN_INLINE:   return text_;
    case TOKEN_MISSING:  return "[MISSING]";
    case TOKEN_EMPTY:    return "[EMPTY]";
    case TOKEN_EOL:      return "[EOL]";
    case TOKEN_EOF:      return "[EOF]";
    }
  }

  TokenType type() const {
    return type_;
  }
  std::string text() const {
    return text_;
  }
  StreamIterator begin() const {
    return begin_;
  }
  StreamIterator end() const {
    return end_;
  }

};


#endif

#ifndef FASTREAD_TOKEN_H
#define FASTREAD_TOKEN_H

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
  int start_, end_;  // indexes to start and end of string (for TOKEN_POINTER)
  std::string text_; // string itself (for TOKEN_RAW)

public:

  Token(TokenType type): type_(type) {}
  Token(TokenType type, std::string text): type_(type), text_(text) {}
  Token(TokenType type, int start, int end): type_(type), start_(start), end_(end) {}

  template <class Stream>
  std::string asString(Stream s) {
    switch(type_) {
    case TOKEN_POINTER:  return s.getString(start_, end_);
    case TOKEN_INLINE:   return text_;
    case TOKEN_MISSING:  return "[MISSING]";
    case TOKEN_EMPTY:  return "[EMPTY]";
    case TOKEN_EOL:      return "[EOL]";
    case TOKEN_EOF:      return "[EOF]";
    }
  }

};


#endif

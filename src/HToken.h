#ifndef FASTREAD_TOKEN_H
#define FASTREAD_TOKEN_H

typedef const char* StreamIterator;
typedef std::pair<StreamIterator,StreamIterator> StreamIterators;
#include <string>

#include <boost/container/string.hpp>
typedef void (*UnescapeFun)(StreamIterator, StreamIterator, boost::container::string*);

enum TokenType {
  TOKEN_STRING,   // a sequence of characters
  TOKEN_MISSING,  // an missing value
  TOKEN_EMPTY,    // an empty value
  TOKEN_EOF       // end of file
};

class Token {
  TokenType type_;
  StreamIterator begin_, end_;  // indexes to start and end of string (for TOKEN_POINTER)

  UnescapeFun pUnescaper_;

public:

  Token(): type_(TOKEN_EMPTY) {}
  Token(TokenType type): type_(type) {}
  Token(StreamIterator begin, StreamIterator end):
    type_(TOKEN_STRING), begin_(begin), end_(end), pUnescaper_(NULL) {
  }

  Token(StreamIterator begin, StreamIterator end, UnescapeFun pUnescaper):
    type_(TOKEN_STRING),
    begin_(begin),
    end_(end),
    pUnescaper_(pUnescaper)
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

  StreamIterators getString(boost::container::string *pOut) const {
    if (pUnescaper_ == NULL)
      return std::make_pair(begin_, end_);

    pUnescaper_(begin_, end_, pOut);
    return std::make_pair(pOut->data(), pOut->data() + pOut->size());
  }

};


#endif

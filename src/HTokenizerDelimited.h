#ifndef FASTREAD_PARSERDELIMITED_H
#define FASTREAD_PARSERDELIMITED_H

#include "HToken.h"
#include <Rcpp.h>

class TokenizerDelimited {
  char delim_, quote_;
  bool backslashEscape_;

public:

  TokenizerDelimited(
    char delim = ',',
    char quote = '"',
    bool backslashEscape = false
  ):
    delim_(delim),
    quote_(quote),
    backslashEscape_(backslashEscape)
  {}

  Token nextToken(StreamFile s) {
    int start = s.pos();

    // Could be delimiter, new line or EOF
    char first = s.get();
    switch(first) {
    case EOF:
      return Token(TOKEN_EOF);
    case '\n':
      return Token(TOKEN_EOL);
    case '\r':
      if (s.peek() == '\n')
        s.get();
      return Token(TOKEN_EOL);
    default:
      if (first != delim_)
        Rcpp::stop("Invalid value");
    }

    std::string string;
    bool hasQuotes = false;
    char c;
    while((c = s.peek()) != EOF) {
      if (!hasQuotes) {
        if (c == delim_)
          break;

        if (c == quote_)
          hasQuotes = true;

      } else {
        // In a string
        if (c == quote_) {
          s.get();
          break;
        } else if (backslashEscape_ && c == '\\') {
          s.get(); // skip escape
          string.push_back(s.peek()); // Needs escaping processing
        } else {
          string.push_back(c);
        }

      }
      s.get();
    }

    if (hasQuotes) {
      return Token(TOKEN_INLINE, string);
    } else {
      return Token(TOKEN_POINTER, start, s.pos());
    }
  }

};

#endif

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

  template <class Stream>
  Token nextToken(Stream* pStream) {

    char first = pStream->get();
    switch(first) {
    case EOF:
      return Token(TOKEN_EOF);
    case '\n':
      pStream->nextRow();
      return Token(TOKEN_EOL);
    case '\r':
      if (pStream->peek() == '\n')
        pStream->get();
      pStream->nextRow();
      return Token(TOKEN_EOL);
    default:
      if (pStream->col() != 0 && first != delim_) {
        Rcpp::stop("Expecting delimiter at (%i, %i) but found '%s'",
          pStream->row(), pStream->col(), first);
      }

      break;
    }

    StreamIterator start = pStream->pos();

    std::string string;
    bool isQuoted = false;
    char c;
    while((c = pStream->peek()) != EOF) {
      if (!isQuoted) {
        if (c == delim_ || c == '\n' || c == '\r')
          break;

        if (c == quote_) {
          isQuoted = true;
        }
      } else {
        // In a string
        if (c == quote_) {
          pStream->get(); // eat quote
          break;
        } else if (backslashEscape_ && c == '\\') {
          pStream->get(); // skip escape
          string.push_back(pStream->peek()); // Needs escaping processing
        } else {
          string.push_back(c);
        }
      }
      pStream->get();
    }

    pStream->nextCol();
    if (isQuoted) {
      return Token(TOKEN_INLINE, string);
    } else {
      StreamIterator end = pStream->pos();
      if (start == end) {
        return Token(TOKEN_EMPTY);
      } else {
        return Token(TOKEN_POINTER, start, end);
      }
    }
  }

};

#endif

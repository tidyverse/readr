#ifndef FASTREAD_SOURCESTRING_H_
#define FASTREAD_SOURCESTRING_H_

#include "Source.h"
#include <Rcpp.h>

class SourceString : public Source {
  Rcpp::RObject string_;

  const char* begin_;
  const char* end_;

public:
  SourceString(
      Rcpp::CharacterVector x,
      int skip,
      const std::string& comment,
      const std::string encoding)
      : Source(encoding) {
    string_ = x[0];

    begin_ = CHAR(string_);
    end_ = begin_ + Rf_xlength(string_);

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip, comment);
  }

  const char* begin() { return begin_; }

  const char* end() { return end_; }
};

#endif

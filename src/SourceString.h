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
      const std::vector<std::string>& comments,
      const std::string encoding)
      : Source(comments, encoding) {
    string_ = x[0];

    begin_ = CHAR(string_);
    end_ = begin_ + Rf_xlength(string_);

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(skip);
  }

  const char* begin() const { return begin_; }

  const char* end() const { return end_; }
};

#endif

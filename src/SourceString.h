#ifndef FASTREAD_SOURCESTRING_H_
#define FASTREAD_SOURCESTRING_H_

#include <Rcpp.h>
#include "Source.h"

class SourceString : public Source {
  Rcpp::RObject string_;
  size_t size_;

  const char* begin_;
  const char* end_;
public:
  SourceString(Rcpp::CharacterVector x, int skip = 0) {
    string_ = x[0];

    begin_ = CHAR(string_);
    end_ = begin_ + Rf_length(string_);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip);
  }

  const char* begin() {
    return begin_;
  }

  const char* end() {
    return end_;
  }
};

#endif

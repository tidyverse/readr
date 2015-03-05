#ifndef FASTREAD_SOURCESTRING_H_
#define FASTREAD_SOURCESTRING_H_

#include <Rcpp.h>
#include "Source.h"

class SourceString : public Source {
  Rcpp::RObject string_;
  size_t size_;
public:
  SourceString(Rcpp::CharacterVector x) {
    string_ = x[0];
    size_ = Rf_length(string_);
  }

  const char* begin() {
    return CHAR(string_);
  }

  const char* end() {
    return begin() + size_;
  }
};

#endif

#ifndef FASTREAD_STREAMSTRING_H_
#define FASTREAD_STREAMSTRING_H_

#include <Rcpp.h>

class StreamString {
  Rcpp::RObject string_;
  size_t size_;
public:
  StreamString(Rcpp::CharacterVector x) {
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

#ifndef FASTREAD_SOURCERAW_H_
#define FASTREAD_SOURCERAW_H_

#include <Rcpp.h>
#include "Source.h"

class SourceRaw : public Source {
  Rcpp::RawVector x_; // Make sure it doesn't get GC'd
  const char* begin_;
  const char* end_;

public:
  SourceRaw(Rcpp::RawVector x, int skip = 0, const std::string& comment = ""):
      x_(x)
  {
    begin_ = (const char*) RAW(x);
    end_ = (const char*) RAW(x) + Rf_length(x);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip, comment);
  }

  const char* begin() {
    return begin_;
  }

  const char* end() {
    return end_;
  }
};

#endif

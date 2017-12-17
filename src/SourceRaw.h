#ifndef FASTREAD_SOURCERAW_H_
#define FASTREAD_SOURCERAW_H_

#include "Source.h"
#include <Rcpp.h>

class SourceRaw : public Source {
  Rcpp::RawVector x_; // Make sure it doesn't get GC'd
  const char* begin_;
  const char* end_;

public:
  SourceRaw(
      Rcpp::RawVector x,
      int skip,
      const std::string& comment,
      const std::string encoding)
      : Source(encoding), x_(x) {
    begin_ = (const char*)RAW(x);
    end_ = (const char*)RAW(x) + Rf_xlength(x);

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip, comment);
  }

  const char* begin() { return begin_; }

  const char* end() { return end_; }
};

#endif

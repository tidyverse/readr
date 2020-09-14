#ifndef FASTREAD_SOURCERAW_H_
#define FASTREAD_SOURCERAW_H_

#include "Source.h"
#include "cpp11/raws.hpp"

class SourceRaw : public Source {
  cpp11::raws x_;
  const char* begin_;
  const char* end_;

public:
  SourceRaw(
      cpp11::raws x,
      int skip = 0,
      bool skipEmptyRows = true,
      const std::string& comment = "",
      bool skipQuotes = true)
      : x_(x) {
    begin_ = (const char*)RAW(x);
    end_ = (const char*)RAW(x) + Rf_xlength(x);

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip, skipEmptyRows, comment, skipQuotes);
  }

  const char* begin() { return begin_; }

  const char* end() { return end_; }
};

#endif

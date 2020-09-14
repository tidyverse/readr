#ifndef FASTREAD_SOURCESTRING_H_
#define FASTREAD_SOURCESTRING_H_

#include "cpp11/strings.hpp"

#include "Source.h"

class SourceString : public Source {
  cpp11::sexp string_;

  const char* begin_;
  const char* end_;

public:
  SourceString(
      cpp11::strings x,
      int skip = 0,
      bool skipEmptyRows = true,
      const std::string& comment = "",
      bool skipQuotes = true)
      : string_(static_cast<SEXP>(x[0])) {

    begin_ = CHAR(string_);
    end_ = begin_ + Rf_xlength(string_);

    // Skip byte order mark, if needed
    begin_ = skipBom(begin_, end_);

    // Skip lines, if needed
    begin_ = skipLines(begin_, end_, skip, skipEmptyRows, comment, skipQuotes);
  }

  const char* begin() { return begin_; }

  const char* end() { return end_; }
};

#endif

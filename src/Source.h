#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include "cpp11/list.hpp"
#include "utils.h"

#include <memory>

class Source;
typedef std::shared_ptr<Source> SourcePtr;

class Source {
public:
  Source() : skippedRows_(0) {}
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

  const char* skipLines(
      const char* begin,
      const char* end,
      int n,
      bool skipEmptyRows = true,
      const std::string& comment = "",
      bool skipQuote = true);

  static const char*
  skipLine(const char* begin, const char* end, bool isComment, bool skipQuote);

  static const char* skipDoubleQuoted(const char* begin, const char* end);

  size_t skippedRows() { return skippedRows_; }

  static const char* skipBom(const char* begin, const char* end);

  static SourcePtr create(const cpp11::list& spec);

private:
  static bool
  inComment(const char* cur, const char* end, const std::string& comment) {
    return starts_with_comment(cur, end, comment);
  }

  size_t skippedRows_;
};

#endif

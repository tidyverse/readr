#include "cpp11/list.hpp"

#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "SourceFile.h"
#include "SourceRaw.h"
#include "SourceString.h"

SourcePtr Source::create(cpp11::list spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  int skip = as<int>(spec["skip"]);
  bool skipEmptyRows = as<int>(spec["skip_empty_rows"]);
  std::string comment = as<std::string>(spec["comment"]);

  if (subclass == "source_raw") {
    return SourcePtr(new SourceRaw(spec[0], skip, skipEmptyRows, comment));
  } else if (subclass == "source_string") {
    return SourcePtr(new SourceString(spec[0], skip, skipEmptyRows, comment));
  } else if (subclass == "source_file") {
    CharacterVector path(spec[0]);
    return SourcePtr(new SourceFile(
        Rf_translateChar(path[0]), skip, skipEmptyRows, comment));
  }

  Rcpp::stop("Unknown source type");
  return SourcePtr();
}

const char* Source::skipLines(
    const char* begin,
    const char* end,
    int n,
    bool skipEmptyRows,
    const std::string& comment) {
  bool hasComment = comment != "";
  bool isComment;

  const char* cur = begin;

  while (cur < end && n > 0) {
    cur = skipLine(cur, end, hasComment && inComment(cur, end, comment));
    --n;
    ++skippedRows_;
  }

  // Skip any more trailing empty rows or comments
  while (cur < end &&
         ((skipEmptyRows && (*cur == '\n' || *cur == '\r')) ||
          (isComment = hasComment && inComment(cur, end, comment)))) {
    cur = skipLine(cur, end, isComment);
    ++skippedRows_;
  }

  return cur;
}

const char*
Source::skipLine(const char* begin, const char* end, bool isComment) {
  const char* cur = begin;
  // skip the rest of the line until the newline
  while (cur < end && !(*cur == '\n' || *cur == '\r')) {
    if (!isComment && *cur == '"') {
      cur = skipDoubleQuoted(cur, end);
    } else {
      advanceForLF(&cur, end);
      ++cur;
    }
  }

  advanceForLF(&cur, end);

  // skip the actual newline char
  if (cur < end) {
    ++cur;
  }

  return cur;
}

const char* Source::skipDoubleQuoted(const char* begin, const char* end) {
  const char* cur = begin;

  // This doesn't handle escaped quotes or more sophisticated things, but
  // will work for simple cases.
  // Opening quote
  ++cur;

  while (cur < end && *cur != '"') {
    ++cur;
  }

  // Closing quote
  if (cur < end) {
    ++cur;
  }

  return cur;
}

const char* Source::skipBom(const char* begin, const char* end) {

  /* Unicode Byte Order Marks
     https://en.wikipedia.org/wiki/Byte_order_mark#Representations_of_byte_order_marks_by_encoding

     00 00 FE FF: UTF-32BE
     FF FE 00 00: UTF-32LE
     FE FF:       UTF-16BE
     FF FE:       UTF-16LE
     EF BB BF:    UTF-8
 */

  switch (begin[0]) {
  // UTF-32BE
  case '\x00':
    if (end - begin >= 4 && begin[1] == '\x00' && begin[2] == '\xFE' &&
        begin[3] == '\xFF') {
      return begin + 4;
    }
    break;

  // UTF-8
  case '\xEF':
    if (end - begin >= 3 && begin[1] == '\xBB' && begin[2] == '\xBF') {
      return begin + 3;
    }
    break;

  // UTF-16BE
  case '\xfe':
    if (end - begin >= 2 && begin[1] == '\xff') {
      return begin + 2;
    }
    break;

  case '\xff':
    if (end - begin >= 2 && begin[1] == '\xfe') {

      // UTF-32 LE
      if (end - begin >= 4 && begin[2] == '\x00' && begin[3] == '\x00') {
        return begin + 4;
      }

      // UTF-16 LE
      return begin + 2;
    }
    break;
  }
  return begin;
}

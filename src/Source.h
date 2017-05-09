#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include "boost.h"
#include <Rcpp.h>
#include "CodePointIterator.h"

class Source;
typedef boost::shared_ptr<Source> SourcePtr;

class Source {
public:
  Source(const std::string& comment, const std::string& encoding) : pComment(comment), pEncoding(encoding) {}
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;
  inline std::string encoding() { return pEncoding;}
  inline std::string comment() { return pComment;}

  const char *skipLines(int skip) {
    bool hasComment = pComment != "";
    bool isComment = false, lineStart = true;

    CodePointIterator cur(begin(), end(), encoding());
    uint32_t cp_lf = cur.cp_lf();
    uint32_t cp_cr = cur.cp_cr();
    uint32_t unit;

    while (skip > 0 && !cur.is_end()) {
      if (lineStart) {
        isComment = hasComment && inComment(cur);
        lineStart = false;
      }

      unit = *cur;

      if (unit == cp_lf) {
        cur.advance_if_crlf();
        if (!isComment)
          skip--;
        lineStart = true;
      } else if (unit == cp_cr) {
        if (!isComment)
          skip--;
        lineStart = true;
      }
      ++cur;
    }

    return cur.get_pos();
  }

  const char* skipBom(const char* begin, const char* end) {

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
        if (pEncoding == "UTF-32" || pEncoding == "UTF32") {
          pEncoding = "UTF-32BE";
        } else if (pEncoding == "UCS-4" || pEncoding == "UCS4") {
          pEncoding = "UCS-4BE";
        }
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
        if (pEncoding == "UTF-16" || pEncoding == "UTF16") {
          pEncoding = "UTF-16BE";
        } else if (pEncoding == "UCS2" || pEncoding == "UCS-2") {
          pEncoding = "UCS2-BE";
        }
        return begin + 2;
      }
      break;

    case '\xff':
      if (end - begin >= 2 && begin[1] == '\xfe') {

        // UTF-32 LE
        if (end - begin >= 4 && begin[2] == '\x00' && begin[3] == '\x00') {
          if (pEncoding == "UTF-32" || pEncoding == "UTF32") {
            pEncoding = "UTF-32LE";
          } else if (pEncoding == "UCS-4" || pEncoding == "UCS4") {
            pEncoding = "UCS-4LE";
          }
          return begin + 4;
        }

        // UTF-16 LE
        if (pEncoding == "UTF-16" || pEncoding == "UTF16") {
          pEncoding = "UTF-16LE";
        } else if (pEncoding == "UCS2" || pEncoding == "UCS-2") {
          pEncoding = "UCS2-LE";
        }
        return begin + 2;
      }
      break;
    }
    return begin;
  }

  static SourcePtr create(Rcpp::List spec);

private:
  std::string pEncoding;
  std::string pComment;
  bool
  inComment(CodePointIterator& cur) {
    boost::iterator_range<const char*> haystack = cur.get_iterator_range();
    return boost::starts_with(haystack, pComment);
  }
};

#endif

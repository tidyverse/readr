#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include <Rcpp.h>
#include "boost.h"

class Source;
typedef boost::shared_ptr<Source> SourcePtr;

class Source {
public:
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

  static const char* skipLines(const char* begin, const char* end, int n,
                               const std::string& comment = "") {
    bool hasComment = comment != "";
    bool isComment = false, lineStart = true;

    const char* cur = begin;

    while(n > 0 && cur != end) {
      if (lineStart) {
        isComment = hasComment && inComment(cur, end, comment);
        lineStart = false;
      }

      if (*cur == '\r') {
        if (cur + 1 != end && *(cur + 1) == '\n') {
          cur++;
        }
        if (!isComment)
          n--;
        lineStart = true;
      } else if (*cur == '\n') {
        if (!isComment)
          n--;
        lineStart = true;
      }


      cur++;
    }

    return cur;
  }

  static const char* skipBom(const char* begin, const char* end) {

    /* Unicode Byte Order Marks
       https://en.wikipedia.org/wiki/Byte_order_mark#Representations_of_byte_order_marks_by_encoding

       00 00 FE FF: UTF-32BE
       FF FE 00 00: UTF-32LE
       FE FF:       UTF-16BE
       FF FE:       UTF-16LE
       EF BB BF:    UTF-8
   */

    switch(begin[0]) {
      // UTF-32BE
      case '\x00':
        if (end - begin >= 4 && begin[1] == '\x00' && begin[2] == '\xFE' && begin[3] == '\xFF') {
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

  static SourcePtr create(Rcpp::List spec);

private:

  static bool inComment(const char* cur, const char* end, const std::string& comment) {
    boost::iterator_range<const char*> haystack(cur, end);
    return boost::starts_with(haystack, comment);
  }

};

#endif

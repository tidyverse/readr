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

       EF BB BF:    UTF-8
       FF FE 00 00: UTF-32LE
       FF FE:       UTF-16LE
       FE FF:       UTF-16BE
       00 00 FE FF: UTF-32BE
   */
    boost::iterator_range<const char*> haystack(begin, end);

    if (boost::starts_with(haystack, "\xEF\xBB\xBF")) {
      return begin + 3;
    }
    if (boost::starts_with(haystack, "\xFF\xFE\x00\x00")) {
      return begin + 4;
    }
    if (boost::starts_with(haystack, "\xFF\xFE")) {
      return begin + 2;
    }
    if (boost::starts_with(haystack, "\xFE\xFF")) {
      return begin + 2;
    }
    if (boost::starts_with(haystack, "\x00\x00\xFE\xFF")) {
      return begin + 4;
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

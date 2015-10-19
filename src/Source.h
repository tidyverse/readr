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

  static SourcePtr create(Rcpp::List spec);

private:

  static bool inComment(const char* cur, const char* end, const std::string& comment) {
    boost::iterator_range<const char*> haystack(cur, end);
    return boost::starts_with(haystack, comment);
  }

};

#endif



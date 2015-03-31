#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include <Rcpp.h>

#include <boost/shared_ptr.hpp>

class Source;
typedef boost::shared_ptr<Source> SourcePtr;

class Source {
public:
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

  static const char* skipLines(const char* begin, const char* end, int n) {
    const char* cur = begin;

    while(n > 0 && cur != end) {
      if (*cur == '\r') {
        if (cur + 1 != end && *(cur + 1) == '\n') {
          cur++;
        }
        n--;
      } else if (*cur == '\n') {
        n--;
      }


      cur++;
    }

    return cur;
  }

  static SourcePtr create(Rcpp::List spec);

};

#endif



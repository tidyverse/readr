#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include <Rcpp.h>

#include <boost/container/string.hpp>
#include <boost/shared_ptr.hpp>

typedef const char* SourceIterator;
typedef std::pair<SourceIterator,SourceIterator> SourceIterators;
typedef void (*UnescapeFun)(SourceIterator, SourceIterator, boost::container::string*);

typedef const char* SourceIterator;

class Source {
public:
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

  static const char* skipLines(const char* begin, const char* end, int n) {
    const char* cur = begin;

    while(n > 0 && cur != end) {
      if (*cur == '\n')
        n--;

      ++cur;
    }

    return cur;
  }

};

typedef boost::shared_ptr<Source> SourcePtr;
SourcePtr sourceCreate(Rcpp::List spec);

#endif



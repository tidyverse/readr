#ifndef FASTREAD_SOURCE_H_
#define FASTREAD_SOURCE_H_

#include <boost/container/string.hpp>
#include <boost/shared_ptr.hpp>

class Source;
typedef boost::shared_ptr<Source> SourcePtr;

typedef const char* SourceIterator;
typedef std::pair<SourceIterator,SourceIterator> SourceIterators;
typedef void (*UnescapeFun)(SourceIterator, SourceIterator, boost::container::string*);

typedef const char* SourceIterator;

class Source {
public:
  virtual ~Source() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

};

#endif

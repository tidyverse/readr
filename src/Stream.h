#ifndef FASTREAD_STREAM_H_
#define FASTREAD_STREAM_H_

#include <boost/container/string.hpp>

typedef const char* StreamIterator;
typedef std::pair<StreamIterator,StreamIterator> StreamIterators;
typedef void (*UnescapeFun)(StreamIterator, StreamIterator, boost::container::string*);

typedef const char* StreamIterator;

class Stream {
public:
  virtual ~Stream() {}

  virtual const char* begin() = 0;
  virtual const char* end() = 0;

};

#endif

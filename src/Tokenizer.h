#ifndef FASTREAD_TOKENIZER_H_
#define FASTREAD_TOKENIZER_H_

#include <boost/noncopyable.hpp>

class Advance : boost::noncopyable  {
  SourceIterator* pIter_;
public:
  Advance(SourceIterator* pIter): pIter_(pIter) {}
  ~Advance() {
    (*pIter_)++;
  }
};

class Tokenizer {
public:
  virtual ~Tokenizer() {}

  virtual void tokenize(SourceIterator begin, SourceIterator end) = 0;
  virtual Token nextToken() = 0;
};

#endif

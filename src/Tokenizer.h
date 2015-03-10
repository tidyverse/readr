#ifndef FASTREAD_TOKENIZER_H_
#define FASTREAD_TOKENIZER_H_

#include <Rcpp.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "Token.h"

class Tokenizer;
typedef boost::shared_ptr<Tokenizer> TokenizerPtr;

class Tokenizer {
public:
  virtual ~Tokenizer() {}

  virtual void tokenize(SourceIterator begin, SourceIterator end) = 0;
  virtual Token nextToken() = 0;
  virtual double proportionDone() = 0;

  static TokenizerPtr create(Rcpp::List spec);
};

// -----------------------------------------------------------------------------
// Helper class for parsers - ensures iterator always advanced no matter
// how loop is exited

class Advance : boost::noncopyable  {
  SourceIterator* pIter_;
public:
  Advance(SourceIterator* pIter): pIter_(pIter) {}
  ~Advance() {
    (*pIter_)++;
  }
};


#endif

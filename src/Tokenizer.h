#ifndef FASTREAD_TOKENIZER_H_
#define FASTREAD_TOKENIZER_H_

#include <Rcpp.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class Tokenizer {
public:
  virtual ~Tokenizer() {}

  virtual void tokenize(SourceIterator begin, SourceIterator end) = 0;
  virtual Token nextToken() = 0;
};

typedef boost::shared_ptr<Tokenizer> TokenizerPtr;
TokenizerPtr tokenizerCreate(Rcpp::List spec);

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

#ifndef FASTREAD_TOKENIZER_H_
#define FASTREAD_TOKENIZER_H_

#include <Rcpp.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/container/string.hpp>
class Token;

typedef const char* SourceIterator;
typedef std::pair<SourceIterator,SourceIterator> SourceIterators;
typedef void (*UnescapeFun)(SourceIterator, SourceIterator, boost::container::string*);

class Tokenizer;
typedef boost::shared_ptr<Tokenizer> TokenizerPtr;

class Tokenizer {
public:
  virtual ~Tokenizer() {}

  virtual void tokenize(SourceIterator begin, SourceIterator end) = 0;
  virtual Token nextToken() = 0;
  virtual double proportionDone() = 0;

  virtual void unescape(SourceIterator begin, SourceIterator end,
                        boost::container::string* pOut) {
    pOut->reserve(end - begin);
    for (SourceIterator cur = begin; cur != end; ++cur)
      pOut->push_back(*cur);
  }

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

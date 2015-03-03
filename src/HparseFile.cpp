#include "HStreamString.h"
#include "HTokenizerDelimited.h"
#include "HCollectorDouble.h"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
void readString(CharacterVector x) {
  StreamString source(x);

  char c;
  while((c = source.get()) != EOF)
    Rcout << c;
}

// [[Rcpp::export]]
std::vector<std::string> tokenizeString(CharacterVector x) {
  StreamString source(x);
  TokenizerDelimited csv(',');

  std::vector<std::string> out;

  while(source.peek() != EOF) {
    Token t = csv.nextToken(&source);
    out.push_back(t.asString(source));
  }

  return out;
}

// [[Rcpp::export]]
SEXP parseString(CharacterVector x, List spec, int n = 100) {
  StreamString source(x);
  TokenizerDelimited csv(',');

  boost::shared_ptr<Collector> out = collectorCreate(spec);
  out->resize(n);

  int i = 0;
  while(source.peek() != EOF && i < n) {
    Token t = csv.nextToken(&source);
    out->setValue(i++, t);
  }
  if (i != n)
    out->resize(i);

  return out->vector();
}


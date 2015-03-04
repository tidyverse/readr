#include "HStreamString.h"
#include "HTokenizerDelimited.h"
#include "HCollectorDouble.h"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::vector<std::string> tokenizeString(CharacterVector x) {
  StreamString source(x);
  TokenizerDelimited csv(',');
  std::string buffer;
  csv.tokenize(source.begin(), source.end(), &buffer);

  std::vector<std::string> out;

  for (Token t = csv.nextToken(); t.type() != TOKEN_EOF; t = csv.nextToken()) {
    out.push_back(t.asString());
  }

  return out;
}

// [[Rcpp::export]]
SEXP parseString(CharacterVector x, List spec, int n = 100) {
  StreamString source(x);
  TokenizerDelimited csv(',');
  std::string buffer;

  csv.tokenize(source.begin(), source.end(), &buffer);

  boost::shared_ptr<Collector> out = collectorCreate(spec);
  out->resize(n);

  int i = 0;
  for (Token t = csv.nextToken(); t.type() != TOKEN_EOF; t = csv.nextToken()) {
    out->setValue(i++, t);
  }
  if (i != n)
    out->resize(i);

  return out->vector();
}


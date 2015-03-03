#include "HSourceFile.h"
#include "HStreamString.h"
#include "HTokenizerDelimited.h"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
void readFile(std::string path) {
  StreamFile source(path);

  char c;
  while((c = source.get()) != EOF)
    Rcout << c;
}

// [[Rcpp::export]]
void readString(CharacterVector x) {
  StreamString source(x);

  char c;
  while((c = source.get()) != EOF)
    Rcout << c;
}

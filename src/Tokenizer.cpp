#include "Tokenizer.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "TokenizerDelimited.h"
#include "TokenizerLine.h"

TokenizerPtr tokenizerCreate(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "tokenizer_delimited") {
    char delim = as<char>(spec["delim"]);
    std::string na = as<std::string>(spec["na"]);

    return TokenizerPtr(new TokenizerDelimited(delim, na));
  } else if (subclass == "tokenizer_line") {
    return TokenizerPtr(new TokenizerLine());
  }

  Rcpp::stop("Unknown tokenizer type");
  return TokenizerPtr();
}

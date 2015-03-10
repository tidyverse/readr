#include "Tokenizer.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "TokenizerCsv.h"
#include "TokenizerLine.h"

TokenizerPtr Tokenizer::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "tokenizer_csv") {
    char delim = as<char>(spec["delim"]);
    std::string na = as<std::string>(spec["na"]);

    return TokenizerPtr(new TokenizerCsv(delim, na));
  } else if (subclass == "tokenizer_line") {
    return TokenizerPtr(new TokenizerLine());
  }

  Rcpp::stop("Unknown tokenizer type");
  return TokenizerPtr();
}

#include "Tokenizer.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "TokenizerDelim.h"
#include "TokenizerFwf.h"
#include "TokenizerLine.h"
#include "TokenizerLog.h"

TokenizerPtr Tokenizer::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "tokenizer_delim") {
    char delim = as<char>(spec["delim"]);
    char quote = as<char>(spec["quote"]);
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);
    bool escapeDouble = as<bool>(spec["escape_double"]);
    bool escapeBackslash = as<bool>(spec["escape_backslash"]);

    return TokenizerPtr(new
      TokenizerDelim(delim, quote, na, escapeBackslash, escapeDouble)
    );
  } else if (subclass == "tokenizer_fwf") {
    std::vector<int>
      begin = as<std::vector<int> >(spec["begin"]),
      end = as<std::vector<int> >(spec["end"]);
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);

    return TokenizerPtr(new TokenizerFwf(begin, end, na));
  } else if (subclass == "tokenizer_line") {
    return TokenizerPtr(new TokenizerLine());
  } else if (subclass == "tokenizer_log") {
    return TokenizerPtr(new TokenizerLog());
  }

  Rcpp::stop("Unknown tokenizer type");
  return TokenizerPtr();
}

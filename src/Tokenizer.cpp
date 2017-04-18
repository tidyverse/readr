#include <Rcpp.h>
using namespace Rcpp;

#include "Tokenizer.h"
#include "TokenizerDelim.h"
#include "TokenizerFwf.h"
#include "TokenizerLine.h"
#include "TokenizerLog.h"
#include "TokenizerWs.h"

TokenizerPtr Tokenizer::create(List spec) {
  std::string subclass(as<CharacterVector>(spec.attr("class"))[0]);

  if (subclass == "tokenizer_delim") {
    char delim = as<char>(spec["delim"]);
    char quote = as<char>(spec["quote"]);
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);
    std::string comment = as<std::string>(spec["comment"]);
    bool trimWs = as<bool>(spec["trim_ws"]);
    bool escapeDouble = as<bool>(spec["escape_double"]);
    bool escapeBackslash = as<bool>(spec["escape_backslash"]);
    bool quotedNA = as<bool>(spec["quoted_na"]);

    return TokenizerPtr(new TokenizerDelim(delim, quote, na, comment, trimWs,
                                           escapeBackslash, escapeDouble,
                                           quotedNA));
  } else if (subclass == "tokenizer_fwf") {
    std::vector<int> begin = as<std::vector<int> >(spec["begin"]),
                     end = as<std::vector<int> >(spec["end"]);
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);
    std::string comment = as<std::string>(spec["comment"]);

    return TokenizerPtr(new TokenizerFwf(begin, end, na, comment));
  } else if (subclass == "tokenizer_line") {
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);
    return TokenizerPtr(new TokenizerLine(na));
  } else if (subclass == "tokenizer_log") {
    return TokenizerPtr(new TokenizerLog());
  } else if (subclass == "tokenizer_ws") {
    std::vector<std::string> na = as<std::vector<std::string> >(spec["na"]);
    std::string comment = as<std::string>(spec["comment"]);
    return TokenizerPtr(new TokenizerWs(na, comment));
  }

  Rcpp::stop("Unknown tokenizer type");
  return TokenizerPtr();
}

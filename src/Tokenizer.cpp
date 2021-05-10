#include "cpp11/as.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/list.hpp"

#include "Tokenizer.h"
#include "TokenizerDelim.h"
#include "TokenizerFwf.h"
#include "TokenizerLine.h"
#include "TokenizerLog.h"
#include "TokenizerWs.h"

TokenizerPtr Tokenizer::create(const cpp11::list& spec) {
  std::string subclass(cpp11::strings(spec.attr("class"))[0]);

  if (subclass == "tokenizer_delim") {
    char delim = cpp11::as_cpp<char>(spec["delim"]);
    char quote = cpp11::as_cpp<char>(spec["quote"]);
    std::vector<std::string> na =
        cpp11::as_cpp<std::vector<std::string>>(spec["na"]);
    std::string comment = cpp11::as_cpp<std::string>(spec["comment"]);
    bool trimWs = cpp11::as_cpp<bool>(spec["trim_ws"]);
    bool escapeDouble = cpp11::as_cpp<bool>(spec["escape_double"]);
    bool escapeBackslash = cpp11::as_cpp<bool>(spec["escape_backslash"]);
    bool quotedNA = cpp11::as_cpp<bool>(spec["quoted_na"]);
    bool skipEmptyRows = cpp11::as_cpp<bool>(spec["skip_empty_rows"]);

    return TokenizerPtr(new TokenizerDelim(
        delim,
        quote,
        na,
        comment,
        trimWs,
        escapeBackslash,
        escapeDouble,
        quotedNA,
        skipEmptyRows));
  }

  if (subclass == "tokenizer_fwf") {
    std::vector<int> begin = cpp11::as_cpp<std::vector<int>>(spec["begin"]);
    std::vector<int> end = cpp11::as_cpp<std::vector<int>>(spec["end"]);
    std::vector<std::string> na =
        cpp11::as_cpp<std::vector<std::string>>(spec["na"]);
    std::string comment = cpp11::as_cpp<std::string>(spec["comment"]);
    bool trimWs = cpp11::as_cpp<bool>(spec["trim_ws"]);
    bool skipEmptyRows = cpp11::as_cpp<bool>(spec["skip_empty_rows"]);
    return TokenizerPtr(
        new TokenizerFwf(begin, end, na, comment, trimWs, skipEmptyRows));
  }

  if (subclass == "tokenizer_line") {
    std::vector<std::string> na =
        cpp11::as_cpp<std::vector<std::string>>(spec["na"]);
    bool skipEmptyRows = cpp11::as_cpp<bool>(spec["skip_empty_rows"]);
    return TokenizerPtr(new TokenizerLine(na, skipEmptyRows));
  }

  if (subclass == "tokenizer_log") {
    bool trimWs = cpp11::as_cpp<bool>(spec["trim_ws"]);

    return TokenizerPtr(new TokenizerLog(trimWs));
  }

  if (subclass == "tokenizer_ws") {
    std::vector<std::string> na =
        cpp11::as_cpp<std::vector<std::string>>(spec["na"]);
    std::string comment = cpp11::as_cpp<std::string>(spec["comment"]);
    bool skipEmptyRows = cpp11::as_cpp<bool>(spec["skip_empty_rows"]);
    return TokenizerPtr(new TokenizerWs(na, comment, skipEmptyRows));
  }

  cpp11::stop("Unknown tokenizer type");
  return TokenizerPtr();
}

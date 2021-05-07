#ifndef READR_TOKENIZERWS_H_
#define READR_TOKENIZERWS_H_

#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

class TokenizerWs : public Tokenizer {
  std::vector<std::string> NA_;

  SourceIterator begin_, cur_, curLine_, end_;
  int row_, col_;
  std::string comment_;
  bool moreTokens_, hasComment_;
  bool skipEmptyRows_;

public:
  TokenizerWs(
      std::vector<std::string> NA = std::vector<std::string>(1, "NA"),
      const std::string& comment = "",
      bool skipEmptyRows = true);

  void tokenize(SourceIterator begin, SourceIterator end);

  std::pair<double, size_t> progress();

  Token nextToken();

private:
  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasNull);

  bool isComment(const char* cur) const;
  bool isEmpty() const;
  void ignoreLine();
};

#endif

#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

class TokenizerFwf : public Tokenizer {
  std::vector<int> beginOffset_;
  std::vector<int> endOffset_;
  std::vector<std::string> NA_;

  SourceIterator begin_, cur_, curLine_, end_;
  int row_, col_, cols_, max_;
  std::string comment_;
  bool moreTokens_, isRagged_, hasComment_, trimWS_;
  bool skipEmptyRows_;

public:
  TokenizerFwf(
      const std::vector<int>& beginOffset,
      const std::vector<int>& endOffset,
      std::vector<std::string> NA = std::vector<std::string>(1, "NA"),
      const std::string& comment = "",
      bool trimWS = true,
      bool skipEmptyRows = true);

  void tokenize(SourceIterator begin, SourceIterator end);

  std::pair<double, size_t> progress();

  Token nextToken();

private:
  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasNull);

  bool isComment(const char* cur) const;
  bool isEmpty() const;
};

#endif

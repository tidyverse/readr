#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"
#include <Rcpp.h>

class TokenizerFwf : public Tokenizer {
  std::vector<int> beginOffset_, endOffset_;
  std::vector<std::string> NA_;

  SourceIterator begin_, cur_, curLine_, end_;
  SourcePtr source_;
  int row_, col_, cols_, max_;
  bool moreTokens_, isRagged_, trimWS_;

public:
  TokenizerFwf(
      const std::vector<int>& beginOffset,
      const std::vector<int>& endOffset,
      std::vector<std::string> NA = std::vector<std::string>(1, "NA"),
      bool trimWS = true);

  void tokenize(SourcePtr source);

  std::pair<double, size_t> progress();

  Token nextToken();

private:
  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasNull);
};

#endif

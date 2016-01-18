#ifndef FASTREAD_TOKENIZERFWF_H_
#define FASTREAD_TOKENIZERFWF_H_

#include <Rcpp.h>
#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

class TokenizerFwf : public Tokenizer {
  std::vector<int> beginOffset_, endOffset_;
  std::vector<std::string> NA_;

  SourceIterator begin_, curLine_, end_;
  int row_, col_, cols_, max_;
  bool moreTokens_,isRagged_;

public:

  TokenizerFwf(const std::vector<int>& beginOffset, const std::vector<int>& endOffset,
               std::vector<std::string> NA = std::vector<std::string>(1, "NA"));

  void tokenize(SourceIterator begin, SourceIterator end);

  std::pair<double,size_t> progress();

  Token nextToken();

private:

  Token fieldToken(SourceIterator begin, SourceIterator end, bool hasNull);
};

#endif

#include <Rcpp.h>
using namespace Rcpp;

#include "Source.h"
#include "Tokenizer.h"
#include "TokenizerFwf.h"
#include "utils.h"

// TokenizerWs
// --------------------------------------------------------------------

#include "TokenizerWs.h"
#include <Rcpp.h>
#include <cctype>

TokenizerWs::TokenizerWs(std::vector<std::string> NA, std::string comment)
    : NA_(NA),
      comment_(comment),
      moreTokens_(false),
      hasComment_(comment.size() > 0) {}

void TokenizerWs::tokenize(SourcePtr source) {
  cur_ = source->begin();
  curLine_ = source->begin();

  begin_ = source->begin();
  end_ = source->end();
  source_ = source;

  row_ = 0;
  col_ = 0;
  moreTokens_ = true;
}

std::pair<double, size_t> TokenizerWs::progress() {
  size_t bytes = cur_ - begin_;
  return std::make_pair(bytes / (double)(end_ - begin_), bytes);
}

Token TokenizerWs::nextToken() {
  // Check for comments and empty lines only at start of line
  if (col_ == 0) {
    source_->skipCommentAndEmptyLines(&cur_);
  }

  if (cur_ == end_)
    return Token(TOKEN_EOF, 0, 0);

  // Find start of field
  SourceIterator fieldBegin = cur_;
  while (fieldBegin != end_ && isblank(*fieldBegin)) {
    ++fieldBegin;
  }
  SourceIterator fieldEnd = fieldBegin;
  while (fieldEnd != end_ && !isspace(*fieldEnd)) {
    ++fieldEnd;
  }
  bool hasNull = *fieldEnd == '\0';
  Token t = fieldToken(fieldBegin, fieldEnd, hasNull);
  cur_ = fieldEnd;
  ++col_;
  if (cur_ != end_ && (*cur_ == '\r' || *cur_ == '\n')) {
    advanceForLF(&cur_, end_);
    ++cur_;
    row_++;
    col_ = 0;
  }
  return t;
}

Token TokenizerWs::fieldToken(
    SourceIterator begin, SourceIterator end, bool hasNull) {
  if (begin == end)
    return Token(TOKEN_MISSING, row_, col_);

  Token t = Token(begin, end, row_, col_, hasNull);
  t.trim();
  t.flagNA(NA_);

  return t;
}

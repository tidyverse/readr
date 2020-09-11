#include "cpp11/R.hpp"

#include "Tokenizer.h"
#include "TokenizerFwf.h"
#include "TokenizerWs.h"
#include "utils.h"

#include "Source.h"

// TokenizerWs
// --------------------------------------------------------------------

#include <cctype>

TokenizerWs::TokenizerWs(
    std::vector<std::string> NA, std::string comment, bool skipEmptyRows)
    : NA_(NA),
      comment_(comment),
      moreTokens_(false),
      hasComment_(comment.size() > 0),
      skipEmptyRows_(skipEmptyRows) {}

void TokenizerWs::tokenize(SourceIterator begin, SourceIterator end) {
  cur_ = begin;
  curLine_ = begin;

  begin_ = begin;
  end_ = end;

  row_ = 0;
  col_ = 0;
  moreTokens_ = true;
}

std::pair<double, size_t> TokenizerWs::progress() {
  size_t bytes = cur_ - begin_;
  return std::make_pair(bytes / (double)(end_ - begin_), bytes);
}

Token TokenizerWs::nextToken() {
  // Check for comments and empty lines at the start of a line
  while (cur_ != end_ && col_ == 0 &&
         (isComment(cur_) || (skipEmptyRows_ && isEmpty()))) {
    ignoreLine();
  }

  if (cur_ == end_)
    return Token(TOKEN_EOF, 0, 0);

  // Find start of field
  SourceIterator fieldBegin = cur_;
  while (fieldBegin != end_ && isblank(*fieldBegin)) {
    ++fieldBegin;
  }

  // Make sure we are not at the start of a comment
  if (isComment(fieldBegin)) {
    ignoreLine();
    row_++;
    col_ = 0;
    return nextToken();
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
bool TokenizerWs::isComment(const char* cur) const {
  if (!hasComment_)
    return false;

  boost::iterator_range<const char*> haystack(cur, end_);
  return boost::starts_with(haystack, comment_);
}

bool TokenizerWs::isEmpty() const {
  return cur_ == end_ || *cur_ == '\r' || *cur_ == '\n';
}

void TokenizerWs::ignoreLine() {
  // Skip rest of line
  while (cur_ != end_ && *cur_ != '\n' && *cur_ != '\r') {
    ++cur_;
  }
  advanceForLF(&cur_, end_);
  if (cur_ != end_) {
    ++cur_;
  }
  curLine_ = cur_;
}

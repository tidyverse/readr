#ifndef FASTREAD_TOKENIZEDELIM_H_
#define FASTREAD_TOKENIZEDELIM_H_
#include "cpp11/R.hpp"

#include "Token.h"
#include "Tokenizer.h"
#include "utils.h"

enum DelimState {
  STATE_DELIM,
  STATE_FIELD,
  STATE_STRING,
  STATE_QUOTE,
  STATE_ESCAPE_S,
  STATE_ESCAPE_F,
  STATE_STRING_END,
  STATE_COMMENT
};

class TokenizerDelim : public Tokenizer {
  char delim_, quote_;
  std::vector<std::string> NA_;
  std::string comment_;

  bool hasComment_, trimWS_, escapeBackslash_, escapeDouble_, quotedNA_,
      hasEmptyNA_;

  SourceIterator begin_, cur_, end_;
  DelimState state_;
  int row_, col_;
  bool moreTokens_;
  bool skipEmptyRows_;

public:
  TokenizerDelim(
      char delim = ',',
      char quote = '"',
      std::vector<std::string> NA = std::vector<std::string>(1, "NA"),
      const std::string& comment = "",
      bool trimWS = true,
      bool escapeBackslash = false,
      bool escapeDouble = true,
      bool quotedNA = true,
      bool skipEmptyRows = true);

  void tokenize(SourceIterator begin, SourceIterator end);

  std::pair<double, size_t> progress();

  Token nextToken();

  void unescape(SourceIterator begin, SourceIterator end, std::string* pOut);

private:
  bool isComment(const char* cur) const;

  void newField();

  void newRecord();

  Token emptyToken(int row, int col) const;

  Token fieldToken(
      SourceIterator begin,
      SourceIterator end,
      bool hasEscapeB,
      bool hasNull,
      int row,
      int col);

  Token stringToken(
      SourceIterator begin,
      SourceIterator end,
      bool hasEscapeB,
      bool hasEscapeD,
      bool hasNull,
      int row,
      int col);

  void unescapeBackslash(
      SourceIterator begin, SourceIterator end, std::string* pOut);

  void
  unescapeDouble(SourceIterator begin, SourceIterator end, std::string* pOut) const;
};
#endif
